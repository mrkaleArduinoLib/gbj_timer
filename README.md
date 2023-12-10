<a id="library"></a>

# gbj_timer
Library provides periodical calling of a procedure (timer handler) without input and output parameters.
* The library does not use system interrupts, just the `millis()` function.
* The timer realizes timing at the principle `not sooner than`.


<a id="dependency"></a>

## Dependency

#### Particle platform
* **Particle.h**: Includes alternative (C++) data type definitions.

#### Arduino platform (including Espressif ESP8266, ESP32)
* **Arduino.h**: Main include file for the Arduino SDK version greater or equal to 100.
* **inttypes.h**: Integer type conversions. This header file includes the exact-width integer definitions and extends them with additional facilities provided by the implementation.


<a id="interface"></a>

## Interface


##### Main functions
* [gbj_timer()](#constructor)
* [fire()](#fire)
* [halt()](#halt)
* [reset()](#reset)
* [resume()](#resume)
* [restart()](#restart)
* [run()](#run)


##### Setters
* [setPeriod()](#setPeriod)


##### Getters
* [getPeriod()](#getPeriod)
* [isActive()](#isActive)


## Custom data types
* [Handler()](#handler)


<a id="handler"></a>

## Handler

#### Description
The template or the signature of a timer handler function, which is called by a timer at the end of a timer period, or immediatelly at the begining of it respectivelly.
* A handler is just a bare function without any input parameters and returning nothing.
* A handler can be declared just as `void` type. It is not needed to be declared as `gbj_timer::Handler` type.

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
    gbj_timer(uint32_t timerPeriod, Handler *timerHandler, bool start, bool halt)

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


* **halt**: Flag about immediate halting the timer.
  * *Valid values*: true, false
    * **true**: The timer is halted for the very beginning and the method [run()](#run) is not called even if the immidiate start is enabled. In order to activate the timer, it should be restarted by [restart()](#resume) or just resumed [resume()](#resume), if not entire new period is needed.
    * **false**: The timer is in active mode from the very beginning.
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

```cpp
void timerTest() {}
gbj_timer timer = gbj_timer(1000L, timerTest, false, true);
void setup()
{
  timer.restart();
}
void loop()
{
  timer.run();
}
```

#### See also
[run()](#run)

[restart()](#restart)

[resume()](#resume)

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


<a id="fire"></a>

## fire()

#### Description
The method starts new timer period and runs the timer's handler, if defined.

#### Syntax
    void fire()

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


<a id="restart"></a>

## restart()

#### Description
The wrapper method for resuming and resetting the timer.

#### Syntax
    void restart()

#### Parameters
None

#### Returns
None

#### See also
[resume()](#resume)

[reset()](#reset)

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
