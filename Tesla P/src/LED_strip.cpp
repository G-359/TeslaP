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
  currentPos = 0;
  prePos = 9;
  strip.setAllLedsColor(0, 0, 0);
  currentColor = BLACK;
  nextColor = WHITE;
  strip.setAllLedsColor(255, 0, 0);
}

void LED_loop()
{
  // brightness
  brightness = 180.0 / 1023.0 * (float)Pack.pot_2;

  if (remote_ready == false)
  {
    return;
  }

  // switch color

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
}