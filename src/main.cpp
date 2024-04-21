#include <Arduino.h>
#include "Led.h"
#include "Us.h"
#include <FlexiTimer2.h>
#include <beep.h>
#include "Wheel.h"
#include "RemoteReceive.h"

void timerFired()
{
  // beepcounter++;
  // led_conter++;
  wheel_counter++;
  vero_counter++;
}

void setup()
{
  FlexiTimer2::set(10, timerFired); // 10 ms
  Us_setup();
  // beep_setup();
  Led_setup();
  FlexiTimer2::start();
  // wheel_setup();
  remote_setup();

}

void loop()
{
  // wheel_loop();
  Us_loop();
  // beep_loop();
  Led_loop();
  remote_loop();
}
