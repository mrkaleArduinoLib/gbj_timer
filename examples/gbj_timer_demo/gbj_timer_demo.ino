/*
  NAME:
  Demonstration usage of gbj_timer library.

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

gbj_timer timerA(3000L, timerDemoA);
gbj_timer timerB(6000L, timerDemoB, true);

void setup()
{
  Serial.begin(9600);
  Serial.println(SKETCH);
  Serial.println("Libraries:");
  Serial.println(gbj_timer::VERSION);
  Serial.println("---");
}

void loop()
{
  timerA.run();
  timerB.run();
}
