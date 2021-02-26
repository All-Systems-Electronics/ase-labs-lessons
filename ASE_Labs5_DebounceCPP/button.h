#pragma once
#include "timer.h"

class tButton {
public:
  // Configuring the pin in the initialiser list saves us 10 bytes flash, because nothing gets initialised twice.
  tButton(int pin):
    pin_([](int pin)
      {
        InitPin(pin);
        return pin;
      }(pin)),
    state_(ReadPin(pin_)),
    lastState_(state_)
  {
  }

  void Update()
  {
    lastState_ = state_;
    
    bool stateNew = ReadPin(pin_);
  
    if (stateNew != state_) {
      if (debounceTimer_.HasElapsed(DebounceTimeMS)) {
        debounceTimer_.Reset();
        state_ = stateNew;
      }
    }
    else {
      debounceTimer_.Reset();
    }
  }

  bool ChangedState() const
  {
    if (state_ != lastState_) {
      return true;
    }
    return false;
  }

  bool IsPressed() const
  {
    return state_;
  }

  bool IsReleased() const
  {
    return !state_;
  }

  bool JustPressed() const
  {
    if (ChangedState()) {
      return state_;
    }
    return false;
  }

  bool JustReleased() const
  {
    if (ChangedState()) {
      return !state_;
    }
    return false;
  }
  
private:
  static constexpr long unsigned DebounceTimeMS = 10;
  
  tTimerMS debounceTimer_;
  uint8_t pin_ = 0;
  bool state_ = false;
  bool lastState_ = false;

  static void InitPin(int pin)
  {
    pinMode(pin, INPUT_PULLUP);
  }

  static bool ReadPin(int pin)
  {
    return !digitalRead(pin);
  }
};
