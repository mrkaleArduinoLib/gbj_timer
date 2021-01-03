/*
  NAME:
  Demonstration usage of gbjTimer library.

  DESCRIPTION:
  The sketch writes to the serial monitor periodically.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#define SKETCH "GBJ_TIMER_DEMO 1.1.0"

#include "gbj_timer.h"

const byte TIMER_INDEX_DEMO_A = 0;
const byte TIMER_INDEX_DEMO_B = 1;
//
const unsigned long TIMER_PERIOD_DEMO_A = 3000;
const unsigned long TIMER_PERIOD_DEMO_B = 6000;

gbj_timer::Timer timers[2];
gbj_timer timer = gbj_timer(timers, sizeof(timers) / sizeof(timers[0]));

void timerDemoA()
{
  static byte round;
  round++;
  Serial.print("TimerDemo A: ");
  Serial.println(round);
}

void timerDemoB()
{
  static byte round;
  round++;
  Serial.print("TimerDemo B: ");
  Serial.println(round);
}

void setup()
{
  Serial.begin(9600);
  Serial.println(SKETCH);
  Serial.println("Libraries:");
  Serial.println(gbj_timer::VERSION);
  Serial.println("---");

  timer.begin(TIMER_INDEX_DEMO_A, TIMER_PERIOD_DEMO_A, timerDemoA);
  timer.begin(TIMER_INDEX_DEMO_B, TIMER_PERIOD_DEMO_B, timerDemoB, true);
}

void loop()
{
  timer.run();
}
