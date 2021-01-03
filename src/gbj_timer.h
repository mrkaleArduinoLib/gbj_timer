/*
  NAME:
  gbjTimer

  DESCRIPTION:
  Library provides periodical calling of procedures.
  - The timer identification numbers (indices to the timer list) should be
    managed by a sketch. On the other hand, it enables redefining timer
    on the fly.

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
  struct Timer
  {
    Handler *handler;
    bool startFlag;
    bool activeFlag;
    uint32_t period;
    uint32_t timestamp;
  };

  /*
    Constructor.

    DESCRIPTION:
    Constructor just creates the class instance object and initiate a timers
    list provided.
    - A sketch should declare and define a one-dimensional array of type
      Timer with as many items as many timers are needed or more.

    PARAMETERS:
    timerTable - Pointer to a list of timer records.
      - Data type: Timer
      - Default value: none
      - Limited range: valid address space

    timersCount - Number of timer records used from timerTable. Usually all of
    them.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: 0 ~ 255

    RETURN: object
  */
  gbj_timer(Timer *timerTable, uint8_t timersCount)
  {
    _status.timers = timerTable;
    _status.cntTimers = timersCount;
    init();
  }

  /*
    Process all registered timers.

    DESCRIPTION:
    The method should be called in the LOOP section of a sketch. It evaluates
    registered timers and call appropriate timer handlers at appripriate time.
    - The method does not run halted timers, timers without a handler, and
    timers with zero time period.

    PARAMETERS: none

    RETURN: none
  */
  void run();

  /*
    Register timer.

    DESCRIPTION:
    The method registers a timer by storing its parameters.
    - A registered timer is considered one with defined timer handler.
    - Timer handler is a procedure (function) within a sketch that receives
      no parameters and returns no value.

    PARAMETERS:
    timerIndex - Identification number of a timer.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: 0 ~ 255

    timerPeriod - The duration of repeating interval in milliseconds.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: 0 ~ 2^32 - 1

    timerHandler - Pointer to a procedure that is called periodically by
      the timer.
      - Data type: gbj_timer_handler
      - Default value: 0 (no handler)
      - Limited range: system address range

    immediateStart - Flag about immediate starting the timer.
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
  void begin(uint8_t timerIndex,
             uint32_t timerPeriod,
             Handler *timerHandler = 0,
             bool immediateStart = false);

  /*
    Reset timer.

    DESCRIPTION:
    The method sets the timestamp of a timer to the current time, so that
    the timer starts counting from beginning of its period.

    PARAMETERS:
    timerIndex - Identification number of a timer.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: registared timers

    RETURN: none
  */
  void reset(uint8_t timerIndex);

  /*
    Halt timer.

    DESCRIPTION:
    The method suspends (temprary stops) a timer and makes it inactive, so that
    the timer's handler is not run more.

    PARAMETERS:
    timerIndex - Identification number of a timer.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: registared timers

    RETURN: none
  */
  void halt(uint8_t timerIndex);

  /*
    Resume timer.

    DESCRIPTION:
    The method resumes halted (inactive) timer with current timestamp and makes
    it active, so that the timer's handler is run again.
    - If the timer has starting flag set, the handler is run immidiately.
    - The timer's period is measured from resuming.
    - Resuming still active timer has no effect.

    PARAMETERS:
    timerIndex - Identification number of a timer.
      - Data type: non-negative integer
      - Default value: none
      - Limited range: registared timers

    RETURN: none
  */
  void resume(uint8_t timerIndex);

  // Public getters
  inline uint8_t getTimers() { return _status.cntTimers; }

private:
  struct
  {
    uint8_t cntTimers; // Number of controlled timers
    Timer *timers; // Pointer to external array of timer definitions
  } _status;

  void init();
};
#endif
