// Built on the debounce lesson, but created a tButton struct and associated functions
// for managing and debouncing the button.
// The button handling code is in button.h, and the timer code is in timer.h
// However, our main code is now much simpler and easier to follow.
// We can clearly see from the functions that get called that when the button is pressed the LED is toggled.

#include "button.h"

static const unsigned PinLed1   = 12;
static const unsigned PinButton = 0;

static tButton button;

void setup() {
  pinMode(PinLed1, OUTPUT);
  digitalWrite(PinLed1, false);

  ButtonInit(&button, PinButton);
}

void loop() {
  ButtonUpdate(&button);

  if (ButtonJustPressed(&button)) {
    digitalWrite(PinLed1, !digitalRead(PinLed1));
  }
}
