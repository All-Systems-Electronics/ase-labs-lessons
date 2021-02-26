#pragma once

struct tLEDFlash {
  long unsigned lastFlashMS;
  long unsigned flashMS;
  uint8_t pin;
};

void LEDFlashInit(tLEDFlash *self, uint8_t pin, long unsigned flashMS)
{
  self->lastFlashMS = millis();
  self->pin = pin;
  self->flashMS = flashMS;
  
  pinMode(self->pin, OUTPUT);
  digitalWrite(self->pin, false);
}

void LEDFlashUpdate(tLEDFlash *self)
{
  if ((millis() - self->lastFlashMS >= self->flashMS)) {
    digitalWrite(self->pin, !digitalRead(self->pin));
    self->lastFlashMS  = millis();
  }
}
