#include "config.h"
#include "display.h"
#include "music_control.h"
#include "songs.h"  // Include the header file here

DFRobotDFPlayerMini myDFPlayer;  // Define it here

void initMusicControl() {
    pinMode(BUTTON_NEXT, INPUT_PULLUP);
    pinMode(BUTTON_PREVIOUS, INPUT_PULLUP);
    pinMode(BUTTON_PAUSE_PLAY, INPUT_PULLUP);
    pinMode(BUTTON_START, INPUT_PULLUP);  // Initialize the start button
    pinMode(LED_RESUME_PIN, OUTPUT);
    pinMode(LED_PAUSE_PIN, OUTPUT);  // Initialize the resume LED pin as output
    pinMode(BUTTON_VOL_UP, INPUT_PULLUP);
    pinMode(BUTTON_VOL_DOWN, INPUT_PULLUP);

    digitalWrite(LED_RESUME_PIN, LOW);
    digitalWrite(LED_PAUSE_PIN, HIGH);  // Turn off the resume LED initially
                                        // Turn off the LED initially

    if (!myDFPlayer.begin(Serial2)) {
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1. Please recheck the connection!"));
        Serial.println(F("2. Please insert the SD card!"));
        while (true)
            ;
    }

    myDFPlayer.volume(20);
    myDFPlayer.play();  // Ensures playback is paused at start
    myDFPlayer.enableLoop();
}

void handleMusicControl() {
    int currentSongNumber = myDFPlayer.readCurrentFileNumber() - 1;

    if (digitalRead(BUTTON_START) == LOW) {
        delay(300);
        myDFPlayer.play();
        digitalWrite(LED_RESUME_PIN, HIGH);
        digitalWrite(LED_PAUSE_PIN, LOW);
        updateDisplay(currentSongNumber);
    }

    if (digitalRead(BUTTON_NEXT) == LOW) {
        delay(300);
        myDFPlayer.play(myDFPlayer.readCurrentFileNumber() + 2);
        digitalWrite(LED_RESUME_PIN, HIGH);
        digitalWrite(LED_PAUSE_PIN, LOW);
        currentSongNumber += 2;
        updateDisplay(currentSongNumber);
    }

    if (digitalRead(BUTTON_PREVIOUS) == LOW) {
        delay(300);
        myDFPlayer.play(myDFPlayer.readCurrentFileNumber() - 2);
        digitalWrite(LED_RESUME_PIN, HIGH);
        digitalWrite(LED_PAUSE_PIN, LOW);
        currentSongNumber -= 2;
        updateDisplay(currentSongNumber);
    }

    if (digitalRead(BUTTON_PAUSE_PLAY) == LOW) {
        delay(300);
        static bool playing = true;
        playing = !playing;
        if (playing) {
            myDFPlayer.pause();
            digitalWrite(LED_RESUME_PIN, LOW);
            digitalWrite(LED_PAUSE_PIN, HIGH);
        } else {
            myDFPlayer.start();
            digitalWrite(LED_RESUME_PIN, HIGH);
            digitalWrite(LED_PAUSE_PIN, LOW);
        }
    }

    // Volume Up
    if (digitalRead(BUTTON_VOL_UP) == LOW) {
        delay(300);
        myDFPlayer.volumeUp();
    }

    // Volume Down
    if (digitalRead(BUTTON_VOL_DOWN) == LOW) {
        delay(300);
        myDFPlayer.volumeDown();
    }
}
