#include <Arduino.h>
#include "beep.h"
#include "LED_strip.h"
#include "ultrasound.h"
#include "FlexiTimer2.h"
#include "wheel.h"
#include "code_servo.h"
#include "nrf_remote.h"

void timerFired()
{
  beep_counter++;
  led_counter++;
  wheel_counter++;
  back_counter++;
  ultrasound_measurment_timer++;
}

void setup()
{
  ultrasound_setup();
  nrf_setup();
  LED_setup();
  beep_setup();
  wheel_setup();
  servo_setup();
  FlexiTimer2::set(10, timerFired);
  FlexiTimer2::start();
}

void loop()
{
  ultrasound_loop();
  nrf_loop();
  LED_loop();
  beep_loop();
  wheel_loop();
  servo_loop();
}