// The exact same code as the structured c debounce code, but written in c++.

// Uses the same amount of SRAM as the c version.
// Uses 48 bytes more flash than the c version.
// This seems to be because the button object is global, its constructor is getting called during the c++ startup code.
// If it is changed so there are no constructors, and we manually initialise the button in setup, then the flash usage is the same.
// If the object is created on the stack then we don't get any flash difference either, so its something to do with the startup code.
// This is a small price to pay for the benefits of c++ objects that manage themselves.

#include "button.h"

static const unsigned PinLed1   = 12;
static const unsigned PinButton = 0;

static tButton button(PinButton);

void setup() {
  pinMode(PinLed1, OUTPUT);
  digitalWrite(PinLed1, false);
}

void loop() {
  button.Update();

  if (button.JustPressed()) {
    digitalWrite(PinLed1, !digitalRead(PinLed1));
  }
}
