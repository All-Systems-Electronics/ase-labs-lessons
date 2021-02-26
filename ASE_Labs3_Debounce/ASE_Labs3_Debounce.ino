// Teaches how to debounce a button, and why its important.
// Since we've already learnt how to use a timer, a seperate tTimerMS struct is
// provided in timer.h so we can make it easier to manage time.

// VARIANT1 just makes the LED state follow the button state.
// It may flicker slightly, but we probably won't notice it.
// However, not many real systems use buttons like this.

// VARIANT2 tracks the state of the button and toggles the LED if the button was just pressed.
// This MOSTLY works. However, sometimes the LED can be seen to quickly toggle on and then immediately off again.
// This is due to contact bounce in the button. It can be clearly seen on an oscilloscope.

// VARIANT3 does the same as VARIANT2, but it tracks the state of the button over time.
// The button must be in its new state for at least 10ms before we consider it a change of state.
// This is called "debouncing", and allows the button to settle before we acknowledge it.

#define VARIANT1  false
#define VARIANT2  false
#define VARIANT3  true

#include "timer.h"

#define LED1 12
#define BUTTON1 0

static bool buttonState = false;
static tTimerMS debounceTimer;

void setup() {
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, false);
  
  pinMode(BUTTON1, INPUT_PULLUP);
  buttonState = !digitalRead(BUTTON1);
}

void loop() {
#if VARIANT1
  // LED changes state directly according to button state.
  if (digitalRead(BUTTON1)) {
    digitalWrite(LED1, false);
  }
  else {
    digitalWrite(LED1, true);
  }
#endif

#if VARIANT2
  // LED toggles on every button press.
  // No debounce is used, so it gets out of sync somehow.
  bool buttonStateNew = !digitalRead(BUTTON1);

  if (buttonStateNew != buttonState) {
    if (buttonStateNew) {
      digitalWrite(LED1, !digitalRead(LED1));
    }
    buttonState = buttonStateNew;
  }
#endif

#if VARIANT3
  // LED toggles on every button press.
  // 10ms debounce smooths out the handling of the button press.
  bool buttonStateNew = !digitalRead(BUTTON1);

  if (buttonStateNew != buttonState) {
    if (TimerHasElapsed(&debounceTimer, 10)) {
      TimerReset(&debounceTimer);
      if (buttonStateNew) {
        digitalWrite(LED1, !digitalRead(LED1));
      }
      buttonState = buttonStateNew;
    }
  }
  else {
    TimerReset(&debounceTimer);
  }
#endif
}
