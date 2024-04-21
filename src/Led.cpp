#include <Arduino.h>
#include <FlexiTimer2.h>
#include "Freenove_WS2812B_RGBLED_Controller.h"
#include <Us.h>
#include "RemoteReceive.h"
#define I2C_ADDRESS 0x20
#define LEDS_COUNT 10 // it defines number of lEDs.
#define MAXLED 10

enum color
{
  RED,
  BLUE,
  GREEN,
  YELLOW,
} color_t;

int currLED = 0;
int preLED = MAXLED - 1;
int led_color = RED;

Freenove_WS2812B_Controller strip(I2C_ADDRESS, LEDS_COUNT, TYPE_GRB); // initialization

int led_conter = 0;
int LedisBlue = 0;

int rangeToFlasingtime()
{
  return range[0] * 5;
}

void Led_setup()
{
  while (!strip.begin())
    ;

  //   strip.setAllLedsColor(0xFF0000); // Set all LED color to red

  //   strip.setAllLedsColor(0x00FF00); // set all LED color to gree

  strip.setAllLedsColor(0x0000FF); // set all LED color to blue

  //   strip.setAllLedsColor(255, 255, 0); // set all LED color to yellow. this is just deffent form of rgb value.

  //   strip.setAllLedsColor(0, 255, 255); // set all LED  color turquoise

  //   strip.setAllLedsColor(255, 0, 255); // set all LED  color magenta

  //   strip.setAllLedsColor(255, 255, 255); // set all LED  color white

  //   strip.setAllLedsColor(0, 0, 0); // set all LED off .

  //   strip.setAllLedsColor(255, 255, 255); // set all LED  color white

  //   strip.setAllLedsColor(255, 0, 255); // set all LED  color magenta

  //   strip.setAllLedsColor(0, 255, 255); // set all LED  color turquoise

  //   strip.setAllLedsColor(255, 255, 0); // set all LED color to yellow. this is just deffent form of rgb value.

  //   strip.setAllLedsColor(0x0000FF); // set all LED color to blue

  //   strip.setAllLedsColor(0x00FF00); // set all LED color to green

  //   strip.setAllLedsColor(0xFF0000); // Set all LED color to red

  //   strip.setLedColor(0, 255, 0, 0); // set the N0.0 LED to red
  //
  //   strip.setLedColor(1, 0, 255, 0); // set the N0.1 LED to green
  //
  //   strip.setLedColor(2, 0, 0, 255); // set the N0.2 LED to blue
  //
  //   strip.setLedColor(3, 255, 255, 0); // set the N0.3 LED to yellow
  //
  //   strip.setLedColor(4, 255, 0, 255); // set the N0.4 LED to purple
  //
  // }
}

void Led_loop()
{
  // int t = rangeToFlasingtime();

  // if (led_conter < t)
  //   return;
  if (Change == true)
  {
    Serial.println("changing");
    switch (led_color)
    {
    case RED:
      led_color = BLUE;
      strip.setAllLedsColor(0, 0, 255);
      break;
    case BLUE:
      led_color = GREEN;
      strip.setAllLedsColor(0, 255, 0);
      break;
    case GREEN:
      led_color = YELLOW;
      strip.setAllLedsColor(0, 255, 255);
      break;
    case YELLOW:
      led_color = RED;
      strip.setAllLedsColor(255, 0, 0);
      break;
    }
    Change = false;
  }
  // preLED = currLED;
  // currLED++;
  // if (currLED >= MAXLED)
  // {
  //   currLED = 0;
  // }
  // strip.setLedColor(currLED, 0, 0, 255);
  //  strip.setLedColor(preLED, 250,0 ,0);

  //   if (LedisBlue == true)
  //   {
  //     strip.setAllLedsColor(0x0000FF); // set all LED color to blue
  //     LedisBlue = false;
  //   }
  //   else
  //   {
  //     strip.setAllLedsColor(0xFF0000); // Set all LED color to red
  //     LedisBlue = true;
  //   }
  //   led_conter = 0;
  // }

  // for (int k = 0; k < 255; k = k + 2)
  // {
  //   strip.setAllLedsColorData(strip.Wheel(k)); // set color data for all LED
  //   strip.show();                              // show the color set before
  // }

  // for (int j = 0; j < 255; j += 2)
  // {
  //   for (int i = 0; i < LEDS_COUNT; i++)
  //   {
  //     strip.setLedColorData(i, strip.Wheel(i * 256 / LEDS_COUNT + j)); // set color data for LED one by one
  //   }
  //   strip.show(); // show the color set
  // }
}
