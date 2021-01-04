<a id="library"></a>
# gbj_timer
Library provides periodical calling of a procedure (timer handler) without input and output parameters.
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


##### Main functions

- [gbj_timer()](#constructor)
- [halt()](#halt)
- [reset()](#reset)
- [resume()](#resume)
- [run()](#run)


<a id="handler"></a>
## Handler

#### Description
The template or signature of a timer handler, which is call by a timer at the end of a timer period, or immediatelly at the begining of it respectivelly.
- A handler is just a bare function without any input parameters and returning nothing.

#### Syntax
    void gbj_timer::Handler()

#### Parameters
None

#### Returns
None

[Back to interface](#interface)


<a id="constructor"></a>
## gbj_timer()

#### Description
Constructor creates the class instance object and initiate a timer.
- Timer handler is a procedure (function) within a sketch that receives no parameters and returns no value.

#### Syntax
    gbj_timer(uint32_t timerPeriod, Handler* timerHandler, bool start)

#### Parameters
- **timerPeriod**: Duration of a repeating interval in milliseconds.
  - *Valid values*: 0 ~ 2^32 - 1
  - *Default value*: none


- **timerHandler**: Pointer to a procedure that is called periodically by the timer.
  - *Valid values*: valid address space
  - *Default value*: none


- **start**: Flag about immediate starting the timer.
  - *Valid values*: true, false
    - **true**: The timer handler is called at the very first calling the method [run()](#run).
    - **false**: The timer handler is called the first time after set time period counting from the setting period by this method.
  - *Default value*: false

#### Returns
None

#### Example
```cpp
void timerTest() {}
gbj_timer timer = gbj_timer(1000L, timerTest, true);
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
The method should be called in the LOOP section of a sketch. It evaluates a timer and calls its handler at appripriate time.
- The method does not run a halted timer and one with zero time period.

#### Syntax
    void run()

#### Parameters
None

#### Returns
None

[Back to interface](#interface)


<a id="reset"></a>
## reset()

#### Description
The method sets the timestamp of the timer to the current time, so that the timer starts counting from beginning of its period.

#### Syntax
    void reset()

#### Parameters
None

#### Returns
None

#### See also
[run()](#run)

[Back to interface](#interface)


<a id="halt"></a>
## halt()

#### Description
The method suspends (temprary stops) the timer and makes it inactive, so that the timer's handler is not run more.

#### Syntax
    void halt()

#### Parameters
None

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
    void resume()

#### Parameters
None

#### Returns
None

#### See also
[halt()](#halt)

[Back to interface](#interface)
