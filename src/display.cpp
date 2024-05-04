#include "config.h"
#include "display.h"
#include "songs.h"

// Array of song names
const char *songNames[] = {
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
    "7. Russian 2",
    "",
};
const int numberOfSongs = sizeof(songNames) / sizeof(songNames[0]);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

int frame = 0;
void initDisplay() {
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextWrap(true);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
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
