#include "gbj_timer.h"
const String gbj_timer::VERSION = "GBJ_TIMER 1.1.0";

void gbj_timer::run()
{
  for (uint8_t i = 0; i < _status.cntTimers; i++)
  {
    if (_status.timers[i].period == 0)
      continue; // No period timer
    if (_status.timers[i].handler == 0)
      continue; // Useless timer
    if (!_status.timers[i].activeFlag)
      continue; // Inactive timer
    // Active timer
    unsigned long tsNow = millis();
    if (tsNow - _status.timers[i].timestamp >= _status.timers[i].period ||
        _status.timers[i].startFlag)
    {
      _status.timers[i].timestamp = tsNow;
      _status.timers[i].startFlag = false;
      _status.timers[i].handler();
    }
  }
}

void gbj_timer::begin(uint8_t timerIndex,
                      uint32_t timerPeriod,
                      Handler *timerHandler,
                      bool immediateStart)
{
  if (timerIndex >= 0 && timerIndex < _status.cntTimers)
  {
    _status.timers[timerIndex].period = timerPeriod;
    _status.timers[timerIndex].handler = timerHandler;
    _status.timers[timerIndex].startFlag = immediateStart;
    reset(timerIndex);
    resume(timerIndex);
  }
}

void gbj_timer::reset(uint8_t timerIndex)
{
  if (timerIndex >= 0 && timerIndex < _status.cntTimers)
  {
    _status.timers[timerIndex].timestamp = millis();
  }
}

void gbj_timer::halt(uint8_t timerIndex)
{
  if (timerIndex >= 0 && timerIndex < _status.cntTimers)
  {
    _status.timers[timerIndex].activeFlag = false;
  }
}

void gbj_timer::resume(uint8_t timerIndex)
{
  if (timerIndex >= 0 && timerIndex < _status.cntTimers &&
      !_status.timers[timerIndex].activeFlag)
  {
    _status.timers[timerIndex].activeFlag = true;
    reset(timerIndex);
  }
}

void gbj_timer::init()
{
  for (uint8_t i = 0; i < _status.cntTimers; i++)
  {
    _status.timers[i].handler = 0;
    _status.timers[i].startFlag = false;
    _status.timers[i].activeFlag = true;
    _status.timers[i].period = 0;
    _status.timers[i].timestamp = 0;
  }
}