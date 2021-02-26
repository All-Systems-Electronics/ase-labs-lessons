#pragma once

struct tTimerMS {
  long unsigned lastTime;
};

void TimerReset(tTimerMS *self)
{
  self->lastTime = millis();
}

bool TimerHasElapsed(tTimerMS *self, long unsigned periodMS)
{
  return (millis() - self->lastTime) >= periodMS;
}
