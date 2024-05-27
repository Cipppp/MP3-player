#ifndef CONFIG_H
#define CONFIG_H

#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <DFRobotDFPlayerMini.h>
#include "esp_timer.h"

#define TIMER_INTERVAL_SEC 1  // intervalul timerului în secunde

#define TFT_CS 5
#define TFT_RST 4
#define TFT_DC 2

#define RX_PIN 16
#define TX_PIN 17
#define BUTTON_PREVIOUS 25
#define BUTTON_PAUSE_PLAY 26
#define BUTTON_NEXT 27
#define DHTPIN 22
#define BUTTON_START 13
#define LED_RESUME_PIN 33
#define LED_PAUSE_PIN 12
#define BUTTON_VOL_UP 32
#define BUTTON_VOL_DOWN 14

extern Adafruit_ST7735 tft;
extern DFRobotDFPlayerMini myDFPlayer;

#endif
