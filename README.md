<a id="library"></a>
# gbj_timer
Library provides periodical calling of a procedure (timer handler) without input and output parameters.

* The library does not use system interrupts, just the `millis()` function.


<a id="dependency"></a>
## Dependency

#### Particle platform
* **Particle.h**: Includes alternative (C++) data type definitions.

#### Arduino platform (including Espressif ESP8266, ESP32)
* **Arduino.h**: Main include file for the Arduino SDK version greater or equal to 100.
* **inttypes.h**: Integer type conversions. This header file includes the exact-width integer definitions and extends them with additional facilities provided by the implementation.


<a id="constants"></a>
## Constants

* **VERSION**: Name and semantic version of the library.


<a id="interface"></a>
## Interface

##### Custom data types

* [Handler()](#handler)


##### Main functions

* [gbj_timer()](#constructor)
* [halt()](#halt)
* [reset()](#reset)
* [resume()](#resume)
* [run()](#run)


##### Setters

* [setPeriod()](#setPeriod)


##### Getters
* [getPeriod()](#getPeriod)
* [isActive()](#isActive)


<a id="handler"></a>
## Handler

#### Description
The template or signature of a timer handler, which is call by a timer at the end of a timer period, or immediatelly at the begining of it respectivelly.

* A handler is just a bare function without any input parameters and returning nothing.

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

* Timer handler is a procedure (function) within a sketch that receives no parameters and returns no value.
* Timer without a time handler is suitable for created internal timer objects in classes and run their member functions as handlers separately.

#### Syntax
    gbj_timer(uint32_t timerPeriod, Handler* timerHandler, bool start)

#### Parameters
<a id="prm_timerPeriod"></a>
* **timerPeriod**: Duration of a repeating interval in milliseconds.
  * *Valid values*: 0 ~ 2^32 - 1
  * *Default value*: none


* **timerHandler**: Pointer to a procedure that is called periodically by the timer. If no handler is provided, the timer just runs.
  * *Valid values*: valid address space
  * *Default value*: 0


* **start**: Flag about immediate starting the timer.
  * *Valid values*: true, false
    * **true**: The timer handler is called at the very first calling the method [run()](#run).
    * **false**: The timer handler is called the first time after set time period counting from the setting period by this method.
  * *Default value*: false

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
```cpp
void timerTest() {}
gbj_timer timer = gbj_timer(1000L);
void loop()
{
  if (timer.run()) timerTest();
}
```

#### See also
[run()](#run)

[Back to interface](#interface)


<a id="run"></a>
## run()

#### Description
The method should be called in the LOOP section of a sketch. It evaluates a timer and calls its handler at appripriate time.

* The method does not run a halted timer and one with zero time period.
* The method still measures time, i.e., saves timestamp of its recent running even if in inactive mode.

#### Syntax
    bool run()

#### Parameters
None

#### Returns
Flag about reaching a timer period and some action should be taken.

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
The method suspends (temporary stops) the timer and makes it inactive, so that the timer's handler is not run more.

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
The method resumes halted (inactive) timer and makes it active, so that the timer runs again.

* Because the timer measures time always, although it is in inactive, it calls next run after timer period, not imediately after resuming.
* Resuming still active timer has no effect.

#### Syntax
    void resume()

#### Parameters
None

#### Returns
None

#### See also
[halt()](#halt)

[Back to interface](#interface)


<a id="setPeriod"></a>
## setPeriod()

#### Description
The method sets a new timer period. It allows to dynamically change a timer frequency in an application.

#### Syntax
    void setPeriod(uint32_t timerPeriod)

#### Parameters
* **timerPeriod**: Duration of a repeating interval in milliseconds.
  * *Valid values*: 0 ~ 2^32 - 1
  * *Default value*: none

#### Returns
None

#### See also
[gbj_timer()](#constructor)

[getPeriod()](#getPeriod)

[Back to interface](#interface)


<a id="getPeriod"></a>
## getPeriod()

#### Description
The method returns current timer period, usually set in [timerPeriod](#prm_timerPeriod) parameter of the [constructor](#constructor).

#### Syntax
    uint32_t getPeriod()

#### Parameters
None

#### Returns
Current timer period in milliseconds.

#### See also
[gbj_timer()](#constructor)

[setPeriod()](#getPeriod)

[Back to interface](#interface)


<a id="isActive"></a>
## isActive()

#### Description
The method returns flag about active (running, not halted) timer.

#### Syntax
    bool isActive()

#### Parameters
None

#### Returns
Flag about current timer activity.

#### See also
[halt()](#halt)

[resume()](#resume)

[Back to interface](#interface)
