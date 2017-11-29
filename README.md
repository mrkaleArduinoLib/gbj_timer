<a id="library"></a>
# gbjTimer
Library provides periodical calling procedures (as the timer handlers) without input and output parameters.

- Due to as small as possible memory footprint of the library, the functionality of the library is kept as simple as reasonable.
- The timer identification numbers (indices to the timer list) should be managed by a sketch. On the other hand, it enables redefining timer on the fly.
- The maximal number of available timers is 8 and can be redefined by appropriate macro defined before including the library header file.
- The library does not use system interrupts, just the `millis()` function.


<a id="dependency"></a>
## Dependency

#### Particle platform
- **Particle.h**: Includes alternative (C++) data type definitions.

#### Arduino platform
- **Arduino.h**: Main include file for the Arduino SDK version greater or equal to 100.
- **WProgram.h**: Main include file for the Arduino SDK version less than 100.
- **inttypes.h**: Integer type conversions. This header file includes the exact-width integer definitions and extends them with additional facilities provided by the implementation.


<a id="constants"></a>
## Constants
- **GBJ_TIMER\_VERSION**: Name and semantic version of the library.
- **GBJ_TIMER\_TIMERS**: Maximal number of available timers. Default is 8 and can be redefined by defining this macro before including the library header file into a sketch.

Remaining constants are listed in the library include file. They are used internally.


<a id="interface"></a>
## Interface
- [gbj_timer()](#gbj_timer)
- [run()](#run)
- [setPeriod()](#setPeriod)


<a id="gbj_timer"></a>
## gbj_timer()
#### Description
Constructor just creates the class instance object.
- Maximum of available timers is defined by macro GBJ_TIMER_TIMERS, which is set to 8 by default.
- The maximum of available timers can be change by defining macro [GBJ\_TIMER\_TIMERS](#constants) before including the header file into a sketch.
- There is no exact sanitizing for maximum number of timers, just by platform and system memory for arrays.

#### Syntax
    gbj_timer();

#### Parameters
None

#### Returns
Object performing the timer management.

[Back to interface](#interface)


<a id="run"></a>
## run()
#### Description
The method processes all registered timers and calls their respective timer handlers at particular points in time.
- The method does not utilizes system interrupts, just the system function `millis()`.
- The method should be called in the LOOP section of a sketch.
- If a timer has the flag parameter set for immediate start, the method calls respective timer handler at its very first run regardless of the timer period of the timer.
- The method starts time counting for the second on time period of a timer.
- Each registered timer is independent of each other. Counting the next time period starts right at the beginning of the calling the time handler for previous period.

#### Syntax
    void run();

#### Parameters
None

#### Returns
None

[Back to interface](#interface)


<a id="setPeriod"></a>
## setPeriod()
#### Description
The method registers a timer by storing its parameters.
- A registered timer is considered one with defined timer handler.
- Timer handler is a procedure (function) within a sketch that receives no parameters and returns no value.
- The method starts time counting for the very first time period of a timer.

#### Syntax
    void setPeriod(uint8_t timerIndex, uint32_t timerPeriod, gbj_timer_handler* timerHandler, bool immediateStart);

#### Parameters
- **timerIndex**: Identification number (index) of a timer within a list (array) of timers.
  - *Valid values*: non-negative integer 0 to [GBJ_TIMER\_TIMERS](#constants)
  - *Default value*: 8 ([GBJ_TIMER\_TIMERS](#constants))

- **timerPeriod**: Duration of repeating interval in milliseconds.
  - *Valid values*: non-negative integer 0 to 2^32 - 1
  - *Default value*: none

- **timerHandler**: Pointer to a procedure that is called periodically by the timer.
  - *Valid values*: non-negative integer 0 to system memory range
  - *Default value*: none

- **immediateStart**: Flag about immediate starting the timer.
  - *Valid values*: true, false
    - **true**: The timer handler is called at the very first calling the method [run()](#run).
    - **false**: The timer handler is the first time called after set time period counting from the setting period by this method.
  - *Default value*: false

#### Returns
None

#### Example
```cpp
gbj_timer Timer = gbj_timer();
void timerTest() {}
void setup()
{
  Timer.setPeriod(0, 1000, timerTest, true);  
}
void loop()
{
  Timer.run();
}
```

[Back to interface](#interface)
