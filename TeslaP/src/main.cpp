#include <Arduino.h>
#include <FlexiTimer2.h>

#include "beep.h"
#include "lights.h"
#include "ultrasound.h"
#include "wheel.h"
#include "app-servo.h"
#include "remote-receiver.h"
#include "key.h"

void timerFired()
{
  light_counter++;
  us_measure_timer++;
}

void setup()
{
  us_setup();
  remote_rx_setup();
  lights_setup();
  beep_setup();
  wheel_setup();
  servo_setup();
  FlexiTimer2::set(10, timerFired);
  FlexiTimer2::start();
  key_setup();
}

void loop()
{
  us_loop();
  remote_rx_loop();
  lights_loop();
  beep_loop();
  wheel_loop();
  servo_loop();
  key_loop();
}