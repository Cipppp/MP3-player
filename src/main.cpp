#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <SPI.h>

#define TFT_CS 5
#define TFT_RST 4
#define TFT_DC 2
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

const int RX_PIN = 16;
const int TX_PIN = 17;
const int BUTTON_NEXT = 27;
const int BUTTON_PREVIOUS = 25;
const int BUTTON_PAUSE_PLAY = 26;
DFRobotDFPlayerMini myDFPlayer;

// Array of song names
const char* songNames[] = {
    "1. Chance Pena - i am not who i was (Official Audio)",
    "",
    "2. Gabrielle Aplin - Home (Lyrics)",
    "",
    "3. James Arthur - Christmas Bells (Official Lyric Video)",
    "",
    "4. Perfectly Wrong",
    "",
    "5. Prefer - Guz  Official Video",
    "",
    "6. Russian 1",
    "",
    "7. Russian 2"
    "",
};
const int numberOfSongs = sizeof(songNames) / sizeof(songNames[0]);

int frame = 0;

void setup() {
    pinMode(BUTTON_NEXT, INPUT_PULLUP);
    pinMode(BUTTON_PREVIOUS, INPUT_PULLUP);
    pinMode(BUTTON_PAUSE_PLAY, INPUT_PULLUP);

    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

    if (!myDFPlayer.begin(Serial2)) {
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        while (true)
            ;  // Stay here forever if the DFPlayer doesn't initialize
    }

    myDFPlayer.volume(20);  // Set initial volume
    myDFPlayer.play(1);     // Start playing the first track

    tft.initR(INITR_BLACKTAB);  // Initialize the display
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextWrap(true);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
    updateDisplay(0);  // Display the first song
}

void loop() {
    static int lastSongNumber = -1;
    int currentSongNumber = myDFPlayer.readCurrentFileNumber() - 1;  // Get current song index, adjusted for zero-based array index

    int buttonStateNext = digitalRead(BUTTON_NEXT);
    int buttonStatePrevious = digitalRead(BUTTON_PREVIOUS);
    int buttonStatePausePlay = digitalRead(BUTTON_PAUSE_PLAY);

    // Handle Next Button Press
    if (buttonStateNext == LOW) {
        delay(300);  // Debounce delay
        if (currentSongNumber >= numberOfSongs - 1) {
            // If it's the last song, loop back to the first song
            myDFPlayer.play(1);     // Start playing the first track
            currentSongNumber = 0;  // Reset song number to the first song
        } else {
            myDFPlayer.next();    // Play the next song
            currentSongNumber++;  // Increment song number
        }
        updateDisplay(currentSongNumber);
        lastSongNumber = currentSongNumber;
    }

    // Handle Previous Button Press
    if (buttonStatePrevious == LOW) {
        delay(300);  // Debounce delay
        if (currentSongNumber <= 0) {
            // If it's the first song, go to the last song
            myDFPlayer.play(numberOfSongs);
            currentSongNumber = numberOfSongs - 1;
        } else {
            myDFPlayer.previous();  // Play the previous song
            currentSongNumber--;    // Decrement song number
        }
        updateDisplay(currentSongNumber);
        lastSongNumber = currentSongNumber;
    }

    // Handle Pause/Play Button Press
    if (buttonStatePausePlay == LOW) {
        delay(300);  // Debounce delay
        static bool playing = true;
        playing = !playing;
        if (playing) {
            myDFPlayer.pause();  // Pause playing
        } else {
            myDFPlayer.start();  // Resume playing
        }
    }

    // Update the display only if the song number changes
    if (currentSongNumber != lastSongNumber) {
        updateDisplay(currentSongNumber);
        lastSongNumber = currentSongNumber;
    }

    animateWaveform();
    delay(50);
}

void updateDisplay(int songIndex) {
    if (songIndex >= 0 && songIndex < numberOfSongs) {
        tft.fillScreen(ST77XX_BLACK);
        int padding = 15;
        tft.setCursor(padding, padding);
        tft.print("Playing: ");
        tft.println(songNames[songIndex]);
    }
}

void animateWaveform() {
    tft.fillRect(0, 40, tft.width(), 30, ST77XX_BLACK);  // Clear the waveform area
    int centerY = 55;                                    // Vertical center of the waveform
    float frequency = 0.5;                               // Wave frequency, adjust for more waves
    int amplitude = 10;                                  // Wave amplitude, adjust for taller waves

    for (int i = 0; i < tft.width(); i++) {
        int y = centerY + sin((i + frame) * frequency) * amplitude;
        tft.drawPixel(i, y, ST77XX_WHITE);
    }
    frame += 2;  // Speed of the wave
}
