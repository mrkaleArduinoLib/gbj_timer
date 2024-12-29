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
#endif

class gbj_timer
{
public:
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
      - Default value: nullptr
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

    halt - Flag about immediate halting the timer.
      - Data type: boolean
      - Default value: false
      - Limited range: true, false
        - true: The timer is halted for the very beginning and the method run()
                is not called even if the immidiate start is enabled. In order
                to activate the timer, it should be restarted or resumed.
        - false: The timer is in active mode from the very beginning.

    RETURN: none
  */
  inline gbj_timer(uint32_t timerPeriod,
                   Handler *timerHandler = nullptr,
                   bool start = false,
                   bool halt = false)
  {
    period_ = timerPeriod;
    handler_ = timerHandler;
    flagStart_ = start;
    flagActive_ = !halt;
    timestamp_ = millis();
  }

  /*
    Process timer

    DESCRIPTION:
    The method should be called in the LOOP section of a sketch. It evaluates
    a timer and calls its handler at appripriate time.
    - The method does not run a halted timer and one with zero time period.

    PARAMETERS: none

    RETURN:
    Flag about reaching a timer period and some action should be taken.
  */
  inline bool run()
  {
    if (period_ == 0 || !flagActive_)
    {
      timestamp_ = millis();
      return false;
    }
    // Active timer
    if (millis() - timestamp_ >= period_ || flagStart_)
    {
      fire();
      flagStart_ = false;
      return true;
    }
    return false;
  }

  /*
    Run timer immediately

    DESCRIPTION:
    The method resets the timer and runs its handler, if defined.

    PARAMETERS: none

    RETURN: none
  */
  inline void fire()
  {
    reset();
    if (handler_ != nullptr)
    {
      handler_();
    }
  }

  /*
    Halt timer

    DESCRIPTION:
    The method suspends (temporary stops) the timer and makes it inactive, so
    that the timer's handler is not run more.

    PARAMETERS: none

    RETURN: none
  */
  inline void halt() { flagActive_ = false; }

  /*
    Reset timer

    DESCRIPTION:
    The method sets the timestamp of the timer to the current time, so that
    the timer starts counting from beginning of its period.

    PARAMETERS: none

    RETURN: none
  */
  inline void reset() { timestamp_ = millis(); }

  /*
    Resume timer

    DESCRIPTION:
    The method resumes halted (inactive) and makes it active, so that it runs
    again.
    - Resuming still active timer has no effect.

    PARAMETERS: none

    RETURN: none
  */
  inline void resume() { flagActive_ = true; }

  /*
    Restart timer

    DESCRIPTION:
    The wrapper method for resuming and resetting the timer.

    PARAMETERS: none

    RETURN: none
  */
  inline void restart()
  {
    resume();
    reset();
  }

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
