/*
  NAME:
  gbj_timer

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
  #include <Arduino.h>
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
    - Timer without a time handler is suitable for created internal timer
    objects in classes and run their member functions as handlers separately.

    PARAMETERS:
    timerPeriod - The duration of repeating interval in milliseconds.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: 0 ~ 2^32 - 1

    timerHandler - Pointer to a procedure within a sketch that receives
      no parameters and returns no value, and is called periodically by
      the timer.
      If no handler is provided, the timer just runs.
      - Data type: Handler
      - Default value: 0
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
                   Handler *timerHandler = 0,
                   bool start = false)
  {
    period_ = timerPeriod;
    handler_ = timerHandler;
    flagStart_ = start;
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

    RETURN:
    Flag about reaching a timer period and some action should be taken.
  */
  bool run()
  {
    if (period_ == 0 || !flagActive_)
    {
      timestamp_ = millis();
      return false;
    }
    // Active timer
    unsigned long tsNow = millis();
    if (tsNow - timestamp_ >= period_ || flagStart_)
    {
      timestamp_ = tsNow;
      flagStart_ = false;
      if (handler_)
      {
        handler_();
      }
      return true;
    }
    return false;
  }

  /*
    Reset timer.

    DESCRIPTION:
    The method sets the timestamp of the timer to the current time, so that
    the timer starts counting from beginning of its period.

    PARAMETERS: none

    RETURN: none
  */
  inline void reset() { timestamp_ = millis(); }

  /*
    Halt timer.

    DESCRIPTION:
    The method suspends (temporary stops) the timer and makes it inactive, so
    that the timer's handler is not run more.

    PARAMETERS: none

    RETURN: none
  */
  inline void halt() { flagActive_ = false; }

  /*
    Resume timer.

    DESCRIPTION:
    The method resumes halted (inactive) and makes it active, so that it runs
    again.
    - Resuming still active timer has no effect.

    PARAMETERS: none

    RETURN: none
  */
  inline void resume() { flagActive_ = true; }

  // Public setters
  inline void setPeriod(uint32_t period) { period_ = period; }

  // Public getters
  inline uint32_t getPeriod() { return period_; }
  inline bool isActive() { return flagActive_; }

private:
  Handler *handler_;
  bool flagStart_;
  bool flagActive_;
  uint32_t period_;
  uint32_t timestamp_;
};

#endif
