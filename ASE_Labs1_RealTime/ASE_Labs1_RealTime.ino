// Teach how to manage events in realtime rather than using delays.
// VARIANT1 shows how to flash LED's using delays.
// However, this means we can't process the button until the delay has finished.
// We fix this by tracking time in MS since the board started up, as shown in VARIANT2

#define VARIANT1    false
#define VARIANT2    true

#define PIN_LED1    (13)
#define PIN_LED2    (12)
#define PIN_BUTTON  (A5)

static long unsigned lastFlashTimeMS = millis();

void setup() {
  pinMode(PIN_LED1, OUTPUT);
  digitalWrite(PIN_LED1, false);
  
  pinMode(PIN_LED2, OUTPUT);
  digitalWrite(PIN_LED2, false);

  pinMode(PIN_BUTTON, INPUT_PULLUP);
}

#if VARIANT1
void loop() {
  delay(1000);
  digitalWrite(PIN_LED1, true);
  delay(1000);
  digitalWrite(PIN_LED1, false);

  if (digitalRead(PIN_BUTTON) == false) {
    digitalWrite(PIN_LED2, true);
  }
  else {
    digitalWrite(PIN_LED2, false);
  }
}
#endif

#if VARIANT2
void loop() {
  if ((millis() - lastFlashTimeMS >= 1000)) {
    digitalWrite(PIN_LED1, !digitalRead(PIN_LED1));
    lastFlashTimeMS = millis();
  }

  if (digitalRead(PIN_BUTTON) == false) {
    digitalWrite(PIN_LED2, true);
  }
  else {
    digitalWrite(PIN_LED2, false);
  }
}
#endif
