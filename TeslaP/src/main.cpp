#include <Arduino.h>
#include <FlexiTimer2.h>

#include "beep.h"
#include "lights.h"
#include "ultrasound.h"
#include "wheel.h"
#include "app-servo.h"
#include "remote-receiver.h"

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
            us_setup{Ultrasonic.cpp, shared}
            us_loop{Ultrasonic.cpp, shared}
            Wheel_setup{Wheel.cpp, shared}
            Wheel_loop{Wheel.cpp, shared}
            lights_setup{LED_strip.cpp, shared}
            lights_loop{LED_strip.cpp}
            rengeToFlashTime{LED_strip.cpp, not shared}
            beep_setup{beep.cpp}
            beep_loop{beep.cpp}
            rangeToBeepTime{beep.cpp}
            wheel_setup{wheel.cpp}
            wheel.loop{wheel.cpp}
            servo.setup{servo.cpp}
            servo.loop{servo.cpp}
            remote_rx_setup{nrf remote.cpp}
            remote_rx_loop{nrf remote.cpp}

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
}

void loop()
{
  us_loop();
  remote_rx_loop();
  lights_loop();
  beep_loop();
  wheel_loop();
  servo_loop();
}
