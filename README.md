<a id="library"></a>
# gbj_timer
Library provides periodical calling of procedures (timer handlers) without input and output parameters.

- The timerTable (list of timers) as an array of timer records has to be defined in a sketch, so that number of available timers is determined in a sketch not in the library.
- The timer identification numbers (indices of the timer records array) should be managed by a sketch. On the other hand, it enables redefining timer on the fly.
- The library does not use system interrupts, just the `millis()` function.


<a id="dependency"></a>
## Dependency

#### Particle platform
- **Particle.h**: Includes alternative (C++) data type definitions.

#### Arduino platform (including Espressif ESP8266, ESP32)
- **Arduino.h**: Main include file for the Arduino SDK version greater or equal to 100.
- **WProgram.h**: Main include file for the Arduino SDK version less than 100.
- **inttypes.h**: Integer type conversions. This header file includes the exact-width integer definitions and extends them with additional facilities provided by the implementation.


<a id="constants"></a>
## Constants

- **VERSION**: Name and semantic version of the library.


<a id="interface"></a>
## Interface

##### Custom data types

- [Handler()](#handler)
- [Timer](#timer)


##### Main functions

- [gbj_timer()](#constructor)
- [begin()](#begin)
- [halt()](#halt)
- [reset()](#reset)
- [resume()](#resume)
- [run()](#run)


<a id="getters"></a>
#### Getters

- [getTimers()](#getTimers)


<a id="handler"></a>
## Handler

#### Description
The template or signature of a timer handler, which is call by timers at the end of a timer period, or once on the begining of it respectivelly.
It is just a bare function without any input parameters and returning nothing.

#### Syntax
    void gbj_timer::Handler()

#### Parameters
None

#### Returns
None

[Back to interface](#interface)


<a id="timer"></a>
## Timer

#### Description
Custom data type defining the structure of a timer record, which holds parameters of a timer.

#### Syntax
    struct Timer
    {
      Handler* handler;
      bool startFlag;
      bool activeFlag;
      uint32_t period;
      uint32_t timestamp;
    }

#### Parameters
- **handler**: Pointer to a function in the role of a timer handler.
  - *Valid values*: within address space of the microcontroller
  - *Default value*: 0


- **startFlag**: Flag determining whether a timer should start immediately after its begining or just after the very firts period.
  - *Valid values*: true, false
  - *Default value*: false


- **activeFlag**: Flag determining whether a timer should run, i.e., to measure time and run its handler.
  - *Valid values*: true, false
  - *Default value*: true


- **period**: Period of handler calling repeatation in milliseconds.
  - *Valid values*: non-negative integer
  - *Default value*: 0


- **timestamp**: The system timestamp of the recent handler calling in milliseconds.
  - *Valid values*: non-negative integer
  - *Default value*: 0

[Back to interface](#interface)


<a id="constructor"></a>
## gbj_timer()

#### Description
Constructor just creates the class instance object and initiate a timer table provided.
- A sketch should declare and define a one-dimensional array of type [Timer](#timer) with as many items as many timers are needed or more.
- There is no exact sanitizing for maximum number of timers, just by platform and system memory for arrays.

#### Syntax
    gbj_timer(Timer* timerTable, uint8_t timersCount)

#### Parameters
<a id="prm_timerTable"></a>
- **timerTable**: Number of timer records used from timerTable. Usually all of
    them.
  - *Valid values*: within address space of the microcontroller
  - *Default value*: none

<a id="prm_timersCount"></a>
- **timersCount**: Number of timers that should.
  - *Valid values*: 0 ~ 255
  - *Default value*: none

#### Returns
Object performing the timer management.

#### Example
``` cpp
gbj_timer::Timer timers[2];
gbj_timer timer = gbj_timer(timers, sizeof(timers) / sizeof(timers[0]));
```

[Back to interface](#interface)


<a id="begin"></a>
## begin()

#### Description
The method registers a timer by storing its parameters.
- A registered timer is considered one with defined timer handler and positive time period.
- Timer handler is a procedure (function) within a sketch that receives no parameters and returns no value.
- The method starts time counting for the very first time period of a timer.

#### Syntax
    void begin(uint8_t timerIndex, uint32_t timerPeriod, Handler* timerHandler, bool immediateStart)

#### Parameters
- **timerIndex**: Identification number (index) of a timer within a timerTable array. If the index is outside of the timerTable, the method does nothing.
  - *Valid values*: 0 ~ [timersCount - 1](#prm_timersCount) from [constructor](#constructor).
  - *Default value*: none


- **timerPeriod**: Duration of a repeating interval in milliseconds.
  - *Valid values*: 0 ~ 2^32 - 1
  - *Default value*: none


- **timerHandler**: Pointer to a procedure that is called periodically by the timer.
  - *Valid values*: valid address space
  - *Default value*: none


- **immediateStart**: Flag about immediate starting the timer.
  - *Valid values*: true, false
    - **true**: The timer handler is called at the very first calling the method [run()](#run).
    - **false**: The timer handler is called the first time after set time period counting from the setting period by this method.
  - *Default value*: false

#### Returns
None

#### Example
```cpp
gbj_timer::Timer timers[2];
gbj_timer timer = gbj_timer(timers, sizeof(timers) / sizeof(timers[0]));
void timerTest() {}
void setup()
{
  timer.begin(0, 1000, timerTest, true);
}
void loop()
{
  timer.run();
}
```

#### See also
[run()](#run)

[Back to interface](#interface)


<a id="run"></a>
## run()

#### Description
The method processes all registered timers and calls their timer handlers at particular points in time.
- The method does not utilizes system interrupts, just the system function `millis()`.
- The method should be called in the LOOP section of a sketch.
- If a timer has the flag parameter set for immediate start, the method calls respective timer handler at its very first run regardless of the timer period of the timer.
- The method starts time counting for the next time period of a timer.
- Each registered timer is independent of each other. Counting the next time period starts right at the beginning of the calling the time handler for previous period.
- If more timers should be executed at the same millisecond, their handlers are called in the order of defining those timers by the method [begin()](#begin).
- The method does not run halted timers, timers without a handler, and timers with zero time period.

#### Syntax
    void run()

#### Parameters
None

#### Returns
None

#### See also
[begin()](#begin)

[Back to interface](#interface)


<a id="reset"></a>
## reset()

#### Description
The method sets the timestamp of a timer to the current time, so that the timer starts counting from beginning of its period.

#### Syntax
    void reset(uint8_t timerIndex)

#### Parameters
- **timerIndex**: Identification number (index) of a timer within a timerTable array. If the index is outside of the timerTable, the method does nothing.
  - *Valid values*: 0 ~ [timersCount - 1](#prm_timersCount) from [constructor](#constructor).
  - *Default value*: none

#### Returns
None

[Back to interface](#interface)


<a id="halt"></a>
## halt()

#### Description
The method suspends (temprary stops) a timer and makes it inactive, so that the timer's handler is not run more.

#### Syntax
    void halt(uint8_t timerIndex)

#### Parameters
- **timerIndex**: Identification number (index) of a timer within a timerTable array. If the index is outside of the timerTable, the method does nothing.
  - *Valid values*: 0 ~ [timersCount - 1](#prm_timersCount) from [constructor](#constructor).
  - *Default value*: none

#### Returns
None

#### See also
[resume()](#resume)

[Back to interface](#interface)


<a id="resume"></a>
## resume()

#### Description
The method resumes halted (inactive) timer with current timestamp and makes it active, so that the timer's handler is run again.
- If the timer has starting flag set, the handler is run immidiately.
- The timer's period is measured from resuming.
- Resuming still active timer has no effect.

#### Syntax
    void resume(uint8_t timerIndex)

#### Parameters
- **timerIndex**: Identification number (index) of a timer within a timerTable array. If the index is outside of the timerTable, the method does nothing.
  - *Valid values*: 0 ~ [timersCount - 1](#prm_timersCount) from [constructor](#constructor).
  - *Default value*: none

#### Returns
None

#### See also
[halt()](#halt)

[Back to interface](#interface)


<a id="getTimers"></a>
## getTimers()

#### Description
The method returns number of registered timers in the [constructor](#constructor).

#### Syntax
    uint8_t getTimers()

#### Parameters
None

#### Returns
Number of registered timers as defined in parameter [timersCount](#prm_timersCount) of [constructor](#constructor).

#### See also
[gbj_timer()](#constructor)

[Back to interface](#interface)
