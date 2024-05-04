#include "config.h"
#include "display.h"
#include "music_control.h"
#include <HomeSpan.h>
struct MusicControl : Service::Switch {
    SpanCharacteristic *power;  // Characteristic to control the music

    // Constructor
    MusicControl() : Service::Switch() {
        power = new Characteristic::On();
    }

    boolean update() override {
        if (power->getNewVal()) {                                           // Correctly use getNewVal() to check the characteristic's new value
            Serial.println("Action: Play Next Song or Toggle Pause/Play");  // Debug print
            // Logic to control music goes here
            myDFPlayer.play();
            updateDisplay(0);
        }
        power->setVal(false);  // Automatically reset the characteristic to OFF after action
        return true;           // Indicate that the update was successful
    }
};

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

    initMusicControl();
    initDisplay();

    homeSpan.begin(Category::Bridges, "MP3 music player");
    homeSpan.setWifiCallback([]() { homeSpan.setPairingCode("31212321"); });
    homeSpan.setQRID("321-12-321");

    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Name("Music Player");
    new MusicControl();
    // updateDisplay(0);  // Initial display update with the first song
}

void loop() {
    handleMusicControl();
    animateWaveform();  // Update the waveform animation on each loop iteration
    homeSpan.poll();
    delay(50);  // Adjust delay for animation performance and responsiveness
}
