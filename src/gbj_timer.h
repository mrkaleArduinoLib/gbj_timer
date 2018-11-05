/*
  NAME:
  gbj_timer

  DESCRIPTION:
  Library provides periodical calling procedures.
  - Due to as small as possible memory footprint of the library,
    the functionality of the library is kept as simple as reasonable.
  - The timer identification numbers (indices to the timer list) should be
    managed by a sketch. On the other hand, it enables redefining timer
    on the fly.
  - The maximal number of available timers is 8 and can be redefined by macro
    GBJ_TIMER_TIMERS defined before including this header file to a sketch.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the license GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html
  (related to original code) and MIT License (MIT) for added code.

  CREDENTIALS:
  Author: Libor Gabaj
  GitHub: https://github.com/mrkaleArduinoLib/gbj_timer.git
 */
#ifndef GBJ_TIMER_H
#define GBJ_TIMER_H
#define GBJ_TIMER_VERSION "GBJ_TIMER 1.0.0"

#if defined(__AVR__)
  #if ARDUINO >= 100
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif
  #include <inttypes.h>
#elif defined(PARTICLE)
  #include <Particle.h>
#endif

#ifndef GBJ_TIMER_TIMERS
#define GBJ_TIMER_TIMERS  8
#endif

typedef void gbj_timer_handler();
struct gbj_timer_record
{
  gbj_timer_handler* handler;
  uint32_t timestamp;
  uint32_t period;
  bool startFlag;
};

class gbj_timer
{
public:
//------------------------------------------------------------------------------
// Public methods
//------------------------------------------------------------------------------

/*
Constructor.

DESCRIPTION:
Constructor just creates the class instance object.
- Maximum of available timers is defined by macro GBJ_TIMER_TIMERS, which is set
  to 8 by default.
- The maximum of available timers can be change by defining macro
  GBJ_TIMER_TIMERS before including this header file into a sketch.
- There is no exact sanitizing for maximum number of timers, just by platform
  and system memory for arrays.

PARAMETERS: none

RETURN:
Library instance object performing the timer management.
*/
  gbj_timer();



/*
  Process all registered timers.

  DESCRIPTION:
  The method should be called in the LOOP section of a sketch. It evaluates
  registered timers and call appropriate timer handlers at appripriate time.

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
  void setPeriod(
    uint8_t timerIndex, \
    uint32_t timerPeriod, \
    gbj_timer_handler* timerHandler = 0, \
    bool immediateStart = false);


private:
//------------------------------------------------------------------------------
// Private attributes
//------------------------------------------------------------------------------
gbj_timer_record _timerParams[GBJ_TIMER_TIMERS];

};
#endif
