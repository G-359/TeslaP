#include <Arduino.h>
#include "Freenove_WS2812B_RGBLED_Controller.h"
#include "Ultrasonic.h"
#include "struct.h"
#include "nrf_remote.h"
#define I2C_ADDRESS 0x20
#define LEDS_COUNT 10 // it defines number of lEDs.

Freenove_WS2812B_Controller strip(I2C_ADDRESS, LEDS_COUNT, TYPE_GRB); // initialization

int led_counter = 0;
int led_power = 0;
int led_pin; // pin of led, 1 ~ 9
bool colorIsBlue = false;
int currentPos;
int currentPos2;
int currentPos3;
int prePos;
int currentColor;
int nextColor;
int pre_s2_value;
int current_s2_value;
bool s2_pressed = false;
int brightness = 255;

int rangeToFlashTime()
{
  if (range > 50)
    return -1;
  if (range < 10)
    return -2;
  return (50 + range * (950 / 40)) / 10;
}

void switchCase1()
{
  if (led_counter < 29)
  {
    return;
  }
  led_counter = 0;
  prePos = currentPos3;
  currentPos3 = currentPos2;
  currentPos2 = currentPos;
  currentPos++;
  if (currentPos > 9)
  {
    currentPos = 0;
  }
  Serial.print(prePos);
  Serial.println(currentPos);
  strip.setLedColor(currentPos, 0, 255, 0);
  strip.setLedColor(currentPos2, 0, 255, 0);
  strip.setLedColor(currentPos3, 0, 255, 0);
  strip.setLedColor(prePos, 0, 0, 0);
  strip.show();
}

typedef enum color
{
  BLACK = 0,
  WHITE = 1,
  RED = 2,
  GREEN = 3,
  BLUE = 4,
  YELLOW = 5
} led_color_t;
led_color_t color;

void LED_setup()
{

  while (!strip.begin())
    ;
  // /***1***/
  // strip.setAllLedsColor(0xFF0000);    // Set all LED color to red
  // strip.setAllLedsColor(0x00FF00);    // set all LED color to green
  // strip.setAllLedsColor(0x0000FF); // set all LED color to blue
  // strip.setAllLedsColor(255, 255, 0); // set all LED color to yellow. this is just deffent form of rgb value.
  // strip.setAllLedsColor(255, 255, 255);
  // strip.setAllLedsColor(0, 0, 0); // set all LED off .
  // /***2***/
  // strip.setLedColor(0, 255, 0, 0);   // set the N0.0 LED to red
  // strip.setLedColor(1, 0, 255, 0);   // set the N0.1 LED to green
  // strip.setLedColor(2, 0, 0, 255);   // set the N0.2 LED to blue
  // strip.setLedColor(3, 255, 255, 0); // set the N0.3 LED to yellow
  // strip.setLedColor(4, 255, 0, 255); // set the N0.4 LED to purple
  currentPos = 0;
  prePos = 9;
  strip.setAllLedsColor(0, 0, 0);
  // color = BLACK;
  currentColor = BLACK;
  nextColor = WHITE;
  strip.setAllLedsColor(255, 0, 0);
}

void LED_loop()
{
  // brightness
  brightness = 180.0 / 1023.0 * (float)Pack.pot_2;

  // led strip roll
  //  for (int k = 0; k < 255; k = k + 2)
  //  {
  //    strip.setAllLedsColorData(strip.Wheel(k)); // set color data for all LED
  //    strip.show();                              // show the color set before
  //  }

  // for (int j = 0; j < 255; j += 2)
  // {
  //   for (int i = 0; i < LEDS_COUNT; i++)
  //   {
  //     strip.setLedColorData(i, strip.Wheel(i * 256 / LEDS_COUNT + j)); // set color data for LED one by one
  //   }
  //   strip.show(); // show the color set
  // }

  if (remote_ready == false)
  {
    return;
  }

  // switch color

  // if (current_s2_value != Pack.s_2)
  // {
  //   pre_s2_value = current_s2_value;
  //   current_s2_value = Pack.s_2;
  // }

  if (Pack.s_2 == 0)
  {
    s2_pressed = true;
  }

  if (Pack.s_2 == 0 && s2_pressed == true)
  {
    s2_pressed = false;

    currentColor = nextColor;
    nextColor++;
    if (nextColor >= 6)
    {
      nextColor = 0;
    }
    Serial.print("current color : ");
    Serial.println(currentColor);
    Serial.print("next color : ");
    Serial.println(nextColor);
  }
  brightness = Pack.pot_2;
  switch (currentColor)
  {
  case 0:
    strip.setAllLedsColorData(0, 0, 0);
    Serial.println("case BLACK");
    strip.show();
    break;

  case 1:
    strip.setAllLedsColorData(brightness, brightness, brightness);
    Serial.println("case WHITE");

    strip.show();
    break;

  case 2:
    strip.setAllLedsColorData(brightness, 0, 0);
    Serial.println("case RED");

    strip.show();
    break;

  case 3:
    strip.setAllLedsColorData(0, brightness, 0);
    Serial.println("case GREEN");

    strip.show();
    break;

  case 4:
    strip.setAllLedsColorData(0, 0, brightness);
    Serial.println("case BLUE");

    strip.show();
    break;

  case 5:
    strip.setAllLedsColorData(brightness, brightness, 0);
    Serial.println("case YELLOW");

    strip.show();
    break;

  default:
    break;
  }
  strip.show();

  // this is the backup program. If the other program works, delete this program
  //   change = false;

  //   if (Pack.s_2 == 0)
  //   {
  //     change = true;
  //   }

  //   if (color == BLACK)
  //   {
  //     if (change == true)
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(brightness, 0, 0);
  //       color = RED;
  //       change = false;
  //     }
  //     else
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(0, 0, 0);
  //     }
  //   }

  //   else if (color == RED)
  //   {
  //     if (change == true)
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(0, brightness, 0);
  //       color = GREEN;
  //       change = false;
  //     }
  //     else
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(brightness, 0, 0);
  //     }
  //   }

  //   else if (color == GREEN)
  //   {
  //     if (change == true)
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(0, 0, brightness);
  //       color = BLUE;
  //       change = false;
  //     }
  //     else
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(0, brightness, 0);
  //     }
  //   }

  //   else if (color == BLUE)
  //   {
  //     if (change == true)
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(brightness, brightness, 0);
  //       color = YELLOW;
  //       change = false;
  //     }
  //     else
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(0, 0, brightness);
  //     }
  //   }

  //   else if (color == YELLOW)
  //   {
  //     if (change == true)
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(brightness, brightness, brightness);
  //       color = WHITE;
  //       change = false;
  //     }
  //     else
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(brightness, brightness, 0);
  //     }
  //   }

  //   else if (color == WHITE)
  //   {
  //     if (change == true)
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(0, 0, 0);
  //       color = BLACK;
  //       change = false;
  //     }
  //     else
  //     {
  //       brightness = 180.0 / 1023.0 * (float)Pack.pot_2;
  //       strip.setAllLedsColor(brightness, brightness, brightness);
  //     }
  //   }
  // }

  // switch (color)
  // {
  // case BLACK:
  //   if (Pack.s_2 == 0)
  //   {
  //     strip.setAllLedsColor(255, 0, 0);
  //     color = RED;
  //   }
  //   break;

  // case RED:
  //   if (Pack.s_2 == 0)
  //   {
  //     strip.setAllLedsColor(0, 255, 0);
  //     color = GREEN;
  //   }
  //   break;

  // case GREEN:
  //   if (Pack.s_2 == 0)
  //   {
  //     strip.setAllLedsColor(0, 0, 255);
  //     color = BLUE;
  //   }
  //   break;

  // case BLUE:
  //   if (Pack.s_2 == 0)
  //   {
  //     strip.setAllLedsColor(255, 255, 0);
  //     color = YELLOW;
  //   }
  //   break;

  // case YELLOW:
  //   if (Pack.s_2 == 0)
  //   {
  //     strip.setAllLedsColor(255, 255, 255);
  //     color = WHITE;
  //   }
  //   break;

  // case WHITE:
  //   if (Pack.s_2 == 0)
  //   {
  //     strip.setAllLedsColor(0, 0, 0);
  //     color = BLACK;
  //   }
  //   break;

  // default:
  //   break;
  // }

  // led control
  // int T = rangeToFlashTime();
  // switch (T)
  // {
  // case -1:
  //   switchCase1();
  //   // strip.setAllLedsColor(0, 255, 0);
  //   break;
  // case -2:
  //   strip.setAllLedsColor(255, 0, 0);
  //   led_counter = 0;
  //   break;
  // default:
  //   if (led_counter > T)
  //   {
  //     led_counter = 0;
  //     if (led_power == 0)
  //     {
  //       strip.setAllLedsColor(255, 255, 0);
  //       led_power = 1;
  //     }
  //     else if (led_power == 1)
  //     {
  //       strip.setAllLedsColor(0, 0, 0);
  //       led_power = 0;
  //     }
  //   }
  //   break;
  // }

  // color control
}