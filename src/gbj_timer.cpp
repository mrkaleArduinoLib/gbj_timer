#include "gbj_timer.h"


gbj_timer::gbj_timer()
{
  for (uint8_t i = 0; i < GBJ_TIMER_TIMERS; i++)
  {
    _timerParams[i].period = 0;
    _timerParams[i].handler = 0;
  }
}


void gbj_timer::setPeriod( \
  uint8_t timerIndex, \
  uint32_t timerPeriod, \
  gbj_timer_handler* timerHandler, \
  bool immediateStart)
{
  timerIndex = constrain(timerIndex, 0, GBJ_TIMER_TIMERS - 1);
  // Define or redefine timer
  _timerParams[timerIndex].period = timerPeriod;
  _timerParams[timerIndex].handler = timerHandler;
  _timerParams[timerIndex].startFlag = immediateStart;
  _timerParams[timerIndex].timestamp = millis();
}


void gbj_timer::run()
{
  for (uint8_t i = 0; i < GBJ_TIMER_TIMERS; i++)
  {
    if (_timerParams[i].handler == 0) continue;  // Not active timer
    unsigned long tsNow = millis();
    if (tsNow - _timerParams[i].timestamp >= _timerParams[i].period || _timerParams[i].startFlag)
    {
      _timerParams[i].timestamp = tsNow;
      _timerParams[i].startFlag = false;
      _timerParams[i].handler();
    }
  }
}
