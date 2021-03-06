#pragma once
#include "timer.h"

struct tButton {
  tTimerMS debounceTimer;
  uint8_t pin;
  bool state;
  bool lastState;
};

void ButtonInit(tButton *self, int pin)
{
  self->pin = pin;
  pinMode(self->pin, INPUT_PULLUP);
  self->state = !digitalRead(self->pin);

  TimerReset(&self->debounceTimer);
}

void ButtonUpdate(tButton *self)
{
  self->lastState = self->state;
  
  bool stateNew = !digitalRead(self->pin);

  if (stateNew != self->state) {
    if (TimerHasElapsed(&self->debounceTimer, 10)) {
      TimerReset(&self->debounceTimer);
      self->state = stateNew;
    }
  }
  else {
    TimerReset(&self->debounceTimer);
  }
}

bool ButtonChangedState(const tButton *self)
{
  if (self->state != self->lastState) {
    return true;
  }
  return false;
}

bool ButtonPressed(const tButton *self)
{
  return self->state;
}

bool ButtonJustPressed(const tButton *self)
{
  if (ButtonChangedState(self)) {
    return self->state;
  }
  return false;
}

bool ButtonReleased(const tButton *self)
{
  return !self->state;
}

bool ButtonJustReleased(const tButton *self)
{
  if (ButtonChangedState(self)) {
    return !self->state;
  }
  return false;
}
