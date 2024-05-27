#include "config.h"
#include "display.h"
#include "music_control.h"
#include "songs.h"

DFRobotDFPlayerMini myDFPlayer;

volatile bool nextPressed = false;
volatile bool previousPressed = false;
volatile bool pausePlayPressed = false;
volatile bool startPlayPressed = false;
volatile bool volUpPressed = false;
volatile bool volDownPressed = false;

void IRAM_ATTR onNextPressed() {
    nextPressed = true;
}

void IRAM_ATTR onPreviousPressed() {
    previousPressed = true;
}

void IRAM_ATTR onPausePlayPressed() {
    pausePlayPressed = true;
}

void IRAM_ATTR onStartPlayPressed() {
    startPlayPressed = true;
}

void IRAM_ATTR onVolUpPressed() {
    volUpPressed = true;
}

void IRAM_ATTR onVolDownPressed() {
    volDownPressed = true;
}
void initMusicControl() {
    pinMode(BUTTON_NEXT, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_NEXT), onNextPressed, FALLING);

    pinMode(BUTTON_PREVIOUS, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PREVIOUS), onPreviousPressed, FALLING);

    pinMode(BUTTON_PAUSE_PLAY, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PAUSE_PLAY), onPausePlayPressed, FALLING);

    pinMode(BUTTON_START, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_START), onPausePlayPressed, FALLING);

    pinMode(BUTTON_VOL_UP, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_VOL_UP), onVolUpPressed, FALLING);

    pinMode(BUTTON_VOL_DOWN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_VOL_DOWN), onVolDownPressed, FALLING);

    pinMode(LED_RESUME_PIN, OUTPUT);
    pinMode(LED_PAUSE_PIN, OUTPUT);
    digitalWrite(LED_RESUME_PIN, LOW);
    digitalWrite(LED_PAUSE_PIN, HIGH);

    if (!myDFPlayer.begin(Serial2)) {
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1. Please recheck the connection!"));
        Serial.println(F("2. Please insert the SD card!"));
        while (true);
    }

    myDFPlayer.volume(10);
    myDFPlayer.play();
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

    if (nextPressed) {
        int currentSongNumber = myDFPlayer.readCurrentFileNumber() - 1;
        myDFPlayer.next();
        digitalWrite(LED_RESUME_PIN, HIGH);
        digitalWrite(LED_PAUSE_PIN, LOW);
        updateDisplay(currentSongNumber + 2);
        nextPressed = false;
    }

    if (previousPressed) {
        int currentSongNumber = myDFPlayer.readCurrentFileNumber() - 1;
        myDFPlayer.previous();
        digitalWrite(LED_RESUME_PIN, HIGH);
        digitalWrite(LED_PAUSE_PIN, LOW);
        updateDisplay(currentSongNumber - 2);
        previousPressed = false;
    }

    if (pausePlayPressed) {
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
        pausePlayPressed = false;
    }

    // Volume Up
    if (volUpPressed) {
        myDFPlayer.volumeUp();
        volUpPressed = false;
    }

    // Volume Down
    if (volDownPressed) {
        myDFPlayer.volumeDown();
        volDownPressed = false;
    }
}
