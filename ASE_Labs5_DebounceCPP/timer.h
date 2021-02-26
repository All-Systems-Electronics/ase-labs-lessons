#pragma once

class tTimerMS {
public:
  void Reset()
  {
    lastTime_ = millis();
  }
  
  bool HasElapsed(long unsigned periodMS) const
  {
    return (millis() - lastTime_) >= periodMS;
  }

private:
  long unsigned lastTime_ = millis();
};
