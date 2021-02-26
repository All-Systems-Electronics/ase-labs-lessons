// Teach how to structure data and code to make it easier to maintain, and to avoid repeating functionality.
// Introduces structs, pointers and header files.
// VARIANT1 shows 3 leds being flashed at different rates.
// The necessary code is duplicated exactly for each LED.
// VARIANT2 also shows the same functionality.
// However, the tLEDFlash structure as created in led.h helps us keep tracks of each LED.
// This allows us to minimise duplicated functionality, as well as only having to define the pin and flash time
// when each LED is initialised.

#include "led.h"

#define VARIANT1  false
#define VARIANT2  true

#define PIN_LED1 13
#define PIN_LED2 12
#define PIN_LED3 11

#define LED1_FLASHTIMEMS 300
#define LED2_FLASHTIMEMS 1000
#define LED3_FLASHTIMEMS 1300

#if VARIANT1
static long unsigned lastFlashTime1MS = millis();
static long unsigned lastFlashTime2MS = millis();
static long unsigned lastFlashTime3MS = millis();

void setup() {
  pinMode(PIN_LED1, OUTPUT);
  digitalWrite(PIN_LED1, false);
  
  pinMode(PIN_LED2, OUTPUT);
  digitalWrite(PIN_LED2, false);
  
  pinMode(PIN_LED3, OUTPUT);
  digitalWrite(PIN_LED3, false);
}

void loop() {
  if ((millis() - lastFlashTime1MS >= LED1_FLASHTIMEMS)) {
    digitalWrite(PIN_LED1, !digitalRead(PIN_LED1));
    lastFlashTime1MS = millis();
  }
  
  if ((millis() - lastFlashTime2MS >= LED2_FLASHTIMEMS)) {
    digitalWrite(PIN_LED2, !digitalRead(PIN_LED2));
    lastFlashTime2MS = millis();
  }
  
  if ((millis() - lastFlashTime3MS >= LED3_FLASHTIMEMS)) {
    digitalWrite(PIN_LED3, !digitalRead(PIN_LED3));
    lastFlashTime3MS = millis();
  }
}
#endif

#if VARIANT2
#define LEDFLASH_COUNT (3)

static tLEDFlash leds[LEDFLASH_COUNT];

void setup() {
  LEDFlashInit(&leds[0], PIN_LED1, LED1_FLASHTIMEMS);
  LEDFlashInit(&leds[1], PIN_LED2, LED2_FLASHTIMEMS);
  LEDFlashInit(&leds[2], PIN_LED3, LED3_FLASHTIMEMS);
}

void loop() {
  for (int i = 0; i < LEDFLASH_COUNT; i++) {
    LEDFlashUpdate(&leds[i]);
  }
}
#endif
