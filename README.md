<a id="library"></a>
# gbjTimer
Library provides periodical calling procedures (timer handlers) without input and output parameters.

- In order to keep memory footprint of the library as small as possible, the functionality of the library is kept as simple as reasonable.
- The timer identification numbers (indices to the timers list) should be managed by a sketch. On the other hand, it enables redefining timer on the fly.
- The timers list as an array of timer records has to be defined in a sketch, so that number of available timers is determined in a sketch not in the library.
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
- **gbj\_timer::VERSION**: Name and semantic version of the library.


<a id="interface"></a>
## Interface

##### Custom data types
- [gbj_timer_handler()](#gbj_timer_handler)
- [gbj_timer_record](#gbj_timer_record)


##### Main functions
- [gbj_timer()](#gbj_timer)
- [run()](#run)
- [setPeriod()](#setPeriod)


<a id="gbj_timer_handler"></a>
## gbj_timer_handler
#### Description
The template or signature of a timer handler, which is call by timers at the end of a timer period.
It is just a bare function without any input parameters and returning nothing.

#### Syntax
    void gbj_timer_handler();

#### Parameters
None

#### Returns
None

#### See also
[gbj_timer_record](#gbj_timer_record)

[Back to interface](#interface)


<a id="gbj_timer_record"></a>
## gbj_timer_record
#### Description
Custom data type defining the structure of a timer record, which holds essential parameters of a timer.

#### Syntax
    struct gbj_timer_record
    {
      gbj_timer_handler* handler;
      bool startFlag;
      uint32_t period;
      uint32_t timestamp;
    };

#### Parameters
- **handler**: Pointer to a function in the role of a timer handler.
  - *Valid values*: within address space of the microcontroller
  - *Default value*: 0


- **startFlag**: Flag determining whether a timer should start immediately after it setting or just after the very firts period.
  - *Valid values*: true, false
  - *Default value*: false

  
- **period**: Period of handler calling repeatation in milliseconds.
  - *Valid values*: non-negative integer
  - *Default value*: 0

  
- **timestamp**: The system timestamp of the recent handler calling in milliseconds.
  - *Valid values*: non-negative integer
  - *Default value*: 0

#### See also
[gbj_timer_handler()](#gbj_timer_handler)

[Back to interface](#interface)


<a id="gbj_timer"></a>
## gbj_timer()
#### Description
Constructor just creates the class instance object and initiate a timers list provided.
- A sketch should declare and define a one-dimensional array of type [gbj_timer_record](#gbj_timer_record) with as many items as many timers are needed.
- There is no exact sanitizing for maximum number of timers, just by platform and system memory for arrays.

#### Syntax
    gbj_timer(gbj_timer_record* timers);

#### Parameters
- **timers**: Pointer to a function in the role of a timer handler.
  - *Valid values*: within address space of the microcontroller
  - *Default value*: 0

#### Returns
Object performing the timer management.

#### Example

``` cpp
gbj_timer::gbj_timer_record timers[2];
gbj_timer Timer = gbj_timer(timers);
```

[Back to interface](#interface)


<a id="run"></a>
## run()
#### Description
The method processes all registered timers and calls their respective timer handlers at particular points in time.
- The method does not utilizes system interrupts, just the system function `millis()`.
- The method should be called in the LOOP section of a sketch.
- If a timer has the flag parameter set for immediate start, the method calls respective timer handler at its very first run regardless of the timer period of the timer.
- The method starts time counting for the next time period of a timer.
- Each registered timer is independent of each other. Counting the next time period starts right at the beginning of the calling the time handler for previous period.
- If more timers should be executed at the same millisecond, their handlers are called in the order of defining those timers by the method [setPeriod()](#setPeriod).

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
- A registered timer is considered one with defined timer handler and positive time period.
- Timer handler is a procedure (function) within a sketch that receives no parameters and returns no value.
- The method starts time counting for the very first time period of a timer.

#### Syntax
    void setPeriod(uint8_t timerIndex, uint32_t timerPeriod, gbj_timer_handler* timerHandler, bool immediateStart);

#### Parameters
- **timerIndex**: Identification number (index) of a timer within a list (array) of timers.
  - *Valid values*: non-negative integer within the size of timers list
  - *Default value*: none

  
- **timerPeriod**: Duration of repeating interval in milliseconds.
  - *Valid values*: non-negative integer 0 to 2^32 - 1
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
gbj_timer::gbj_timer_record timers[2];
gbj_timer Timer = gbj_timer(timers);
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
