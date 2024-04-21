#include <Arduino.h>
#include "beep.h"
#include "LED_strip.h"
#include "Ultrasonic.h"
#include "FlexiTimer2.h"
#include "wheel.h"
#include "code_servo.h"
#include "nrf_remote.h"
/**********************************************************************
  Product     : Freenove 4WD Car for UNO
  Description : Control ws2812b led through freenove_controller.
  Auther      : www.freenove.com
  Modification: 2019/08/03
**********************************************************************/

/***********************************************************************
 Fonctions(not up to date):
            microsecondsToInches(long microseconds){Ultrasonic.cpp, not shared}
            microsecondsToCentimeters(long microseconds){Ultrasonic.cpp, not shared}
            Ultrasonic_setup{Ultrasonic.cpp, shared}
            Ultrasonic_loop{Ultrasonic.cpp, shared}
            Wheel_setup{Wheel.cpp, shared}
            Wheel_loop{Wheel.cpp, shared}
            LED_setup{LED_strip.cpp, shared}
            LED_loop{LED_strip.cpp}
            rengeToFlashTime{LED_strip.cpp, not shared}
            beep_setup{beep.cpp}
            beep_loop{beep.cpp}
            rangeToBeepTime{beep.cpp}
            wheel_setup{wheel.cpp}
            wheel.loop{wheel.cpp}
            servo.setup{servo.cpp}
            servo.loop{servo.cpp}
            nrf_setup{nrf remote.cpp}
            nrf_loop{nrf remote.cpp}

            setup{main.cpp}
            loop{main.cpp}
 ***********************************************************************/

/***********************************************************************
 Legend:
          u = ultrasonic
          ls = led strip
          b = beep
          w = wheel
          s = servo
          nrf = nrf24 remote
 ***********************************************************************/

void timerFired()
{
  beep_counter++;
  led_counter++;
  wheel_counter++;
  back_counter++;
  servo_counter++;
  ultrasonic_measurment_timer++;
}

void setup()
{
  Ultrasonic_setup();
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
  Ultrasonic_loop();
  nrf_loop();
  LED_loop();
  beep_loop();
  wheel_loop();
  servo_loop();
}