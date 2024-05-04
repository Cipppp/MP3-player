#ifndef CONFIG_H
#define CONFIG_H

#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <DFRobotDFPlayerMini.h>

#define TFT_CS 5
#define TFT_RST 4
#define TFT_DC 2

#define RX_PIN 16
#define TX_PIN 17
#define BUTTON_PREVIOUS 25
#define BUTTON_PAUSE_PLAY 26
#define BUTTON_NEXT 27
#define BUTTON_START 13     // New button for starting music
#define LED_RESUME_PIN 33   // Define your LED pin here
#define LED_PAUSE_PIN 12    // Define your LED pin here
#define BUTTON_VOL_UP 32    // Define volume up button pin
#define BUTTON_VOL_DOWN 14  // Define volume down button pin

extern Adafruit_ST7735 tft;
extern DFRobotDFPlayerMini myDFPlayer;

#endif  // CONFIG_H
