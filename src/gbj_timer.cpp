#include "gbj_timer.h"
const String gbj_timer::VERSION = "GBJ_TIMER 1.0.0";


gbj_timer::gbj_timer(gbj_timer_record* timers)
{
  _status.timers = timers;
  _status.cntTimers = sizeof(timers);
  init();
}


void gbj_timer::run()
{
  for (uint8_t i = 0; i < _status.cntTimers; i++)
  {
    if (_status.timers[i].period == 0) continue;  // Inactive timer
    if (_status.timers[i].handler == 0) continue;  // Useless timer
    unsigned long tsNow = millis();
    if (tsNow - _status.timers[i].timestamp >= _status.timers[i].period || _status.timers[i].startFlag)
    {
      _status.timers[i].timestamp = tsNow;
      _status.timers[i].startFlag = false;
      _status.timers[i].handler();
    }
  }
}


//-------------------------------------------------------------------------
// Setters
//-------------------------------------------------------------------------
void gbj_timer::setPeriod(uint8_t timerIndex, uint32_t timerPeriod, \
  gbj_timer_handler* timerHandler, bool immediateStart)
{
  timerIndex = constrain(timerIndex, 0, _status.cntTimers - 1);
  // Define or redefine timer
  _status.timers[timerIndex].period = timerPeriod;
  _status.timers[timerIndex].handler = timerHandler;
  _status.timers[timerIndex].startFlag = immediateStart;
  _status.timers[timerIndex].timestamp = millis();
}


//------------------------------------------------------------------------------
// Private methods
//------------------------------------------------------------------------------
void gbj_timer::init()
{
  for (uint8_t i = 0; i < _status.cntTimers; i++)
  {
    _status.timers[i].handler = 0;
    _status.timers[i].startFlag = false;
    _status.timers[i].period = 0;
    _status.timers[i].timestamp = 0;
  }
}
