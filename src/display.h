// display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <DHT.h>
#include <DHT_U.h>

extern DHT dht;  // Declare the DHT object as extern

void initDisplay();
void updateDisplay(int songIndex);
void updateSensorReadings(float temperature, float humidity);
void animateWaveform();

#endif
