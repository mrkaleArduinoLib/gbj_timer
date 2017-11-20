/*
  NAME:
  Demonstration usage of gbjTimer library.

  DESCRIPTION:
  The sketch writes to the serial monitor peridicaly.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#define SKETCH "GBJTIMER-DEMO 1.0.0"

#include "gbj_timer.h"

const unsigned int  TIMER_INDEX_DEMO_A   = 0;
const unsigned int  TIMER_INDEX_DEMO_B   = 1;
//
const unsigned long TIMER_PERDIOD_DEMO_A = 3000;
const unsigned long TIMER_PERDIOD_DEMO_B = 6000;

gbj_timer Timer = gbj_timer();

void timerDemoA()
{
  static unsigned int round;
  round++;
  Serial.print("TimerDemo A: ");
  Serial.println(round);
}

void timerDemoB()
{
  static unsigned int round;
  round++;
  Serial.print("TimerDemo B: ");
  Serial.println(round);
}

void setup()
{
  Serial.begin(9600);
  Timer.setPeriod(TIMER_INDEX_DEMO_A, TIMER_PERDIOD_DEMO_A, timerDemoA);
  Timer.setPeriod(TIMER_INDEX_DEMO_B, TIMER_PERDIOD_DEMO_B, timerDemoB, true);
}

void loop()
{
  Timer.run();
}
