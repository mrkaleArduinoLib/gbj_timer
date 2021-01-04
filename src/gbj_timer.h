/*
  NAME:
  gbjTimer

  DESCRIPTION:
  Library provides periodical calling of a procedure.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the license GNU GPL v3
  http://www.gnu.org/licenses/gpl-3.0.html (related to original code) and MIT
  License (MIT) for added code.

  CREDENTIALS:
  Author: Libor Gabaj
  GitHub: https://github.com/mrkaleArduinoLib/gbj_timer.git
 */
#ifndef GBJ_TIMER_H
#define GBJ_TIMER_H

#if defined(__AVR__)
  #if ARDUINO >= 100
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif
  #include <inttypes.h>
#elif defined(ESP8266) || defined(ESP32)
  #include <Arduino.h>
#elif defined(PARTICLE)
  #include <Particle.h>
#endif

class gbj_timer
{
public:
  static const String VERSION;

  typedef void Handler();

  /*
    Constructor.

    DESCRIPTION:
    Constructor creates the class instance object and initiate a timer.
    - Timer handler is a procedure (function) within a sketch that receives
      no parameters and returns no value.

    PARAMETERS:
    timerPeriod - The duration of repeating interval in milliseconds.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: 0 ~ 2^32 - 1

    timerHandler - Pointer to a procedure within a sketch that receives
      no parameters and returns no value, and is called periodically by
      the timer.
      - Data type: Handler
      - Default value: none
      - Limited range: system address range

    start - Flag about immediate starting the timer.
      - Data type: boolean
      - Default value: false
      - Limited range: true, false
        - true: The timer handler is called at the very first
                calling the method run().
        - false: The timer handler is the first time called
                after set time period counting from the setting
                period by this method.
    RETURN: none
  */
  inline gbj_timer(uint32_t timerPeriod,
                   Handler *timerHandler,
                   bool start = false)
  {
    _timer.period = timerPeriod;
    _timer.handler = timerHandler;
    _timer.flagStart = start;
    reset();
    resume();
  }

  /*
    Process a timer.

    DESCRIPTION:
    The method should be called in the LOOP section of a sketch. It evaluates
    a timer and calls its handler at appripriate time.
    - The method does not run a halted timer and one with zero time period.

    PARAMETERS: none

    RETURN: none
  */
  void run()
  {
    if (_timer.period == 0 || !_timer.flagActive)
      return;
    // Active timer
    unsigned long tsNow = millis();
    if (tsNow - _timer.timestamp >= _timer.period || _timer.flagStart)
    {
      _timer.timestamp = tsNow;
      _timer.flagStart = false;
      _timer.handler();
    }
  }

  /*
    Reset timer.

    DESCRIPTION:
    The method sets the timestamp of the timer to the current time, so that
    the timer starts counting from beginning of its period.

    PARAMETERS: none

    RETURN: none
  */
  inline void reset() { _timer.timestamp = millis(); }

  /*
    Halt timer.

    DESCRIPTION:
    The method suspends (temprary stops) the timer and makes it inactive, so
    that the timer's handler is not run more.

    PARAMETERS: none

    RETURN: none
  */
  inline void halt() { _timer.flagActive = false; }

  /*
    Resume timer.

    DESCRIPTION:
    The method resumes halted (inactive) timer with current timestamp and makes
    it active, so that the timer's handler is run again.
    - If the timer has starting flag set, the handler is run immidiately.
    - The timer's period is measured from resuming.
    - Resuming still active timer has no effect.

    PARAMETERS: none

    RETURN: none
  */
  inline void resume()
  {
    if (!_timer.flagActive)
    {
      _timer.flagActive = true;
      reset();
    }
  }

private:
  struct Timer
  {
    Handler *handler;
    bool flagStart;
    bool flagActive;
    uint32_t period;
    uint32_t timestamp;
  } _timer;
};

#endif
