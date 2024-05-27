#include "config.h"
#include "display.h"
#include "songs.h"

const char *songNames[] = {
    "1. Perfectly Wrong",
    "",
    "",
    "2. Gabrielle Aplin - Home (Lyrics)",
    "",
    "",
    "3. James Arthur - Christmas Bells (Official Lyric Video)",
    "",
    "",
    "4. Chance Pena - i am not who i was (Official Audio)",
    "",
    "",
    "5. Russian 1",
    "",
    "",
    "6. Russian 2",
    "",
    "",
    "7. Prefer - Guz  Official Video",
    "",
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

// void animateWaveform() {
//     int startY = 50;                                                            // Start Y-coordinate of the waveform animation
//     tft.fillRect(0, startY, tft.width(), tft.height() - startY, ST77XX_BLACK);  // Clear only the waveform area
//     int centerY = startY + 25;
//     float frequency = 0.5;
//     int amplitude = 10;

//     for (int i = 0; i < tft.width(); i++) {
//         int y = centerY + sin((i + frame) * frequency) * amplitude;
//         tft.drawPixel(i, y, ST77XX_WHITE);
//     }
//     frame += 2;  // Speed of the wave
// }

void updateDisplay(int songIndex) {
    tft.fillScreen(ST77XX_BLACK);
    if (songIndex >= 0 && songIndex < numberOfSongs) {
        tft.setCursor(5, 10);
        tft.print("Playing: ");
        tft.println(songNames[songIndex]);
    }
    // Add a call here to update the sensor readings right after updating the song name
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (!isnan(humidity) && !isnan(temperature)) {
        updateSensorReadings(temperature, humidity);
    }
}

void updateSensorReadings(float temperature, float humidity) {
    int sensorY = 50;                                         // Base Y-coordinate for sensor data
    tft.fillRect(0, sensorY, tft.width(), 40, ST77XX_BLACK);  // Clear the sensor data area
    tft.setCursor(5, sensorY);                                // Set cursor for temperature
    tft.print("Temp: ");
    tft.print(temperature);
    tft.println(" C");

    tft.setCursor(5, sensorY + 20);  // Set cursor for humidity on the next line
    tft.print("Hum: ");
    tft.print(humidity);
    tft.println(" %");
}
