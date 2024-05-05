#include <Arduino.h>
#include <Freenove_WS2812B_RGBLED_Controller.h>

#include "ultrasound.h"
#include "packets.h"
#include "remote-receiver.h"

#define I2C_ADDRESS 0x20
#define LEDS_COUNT 10 // it defines number of lEDs.

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

Freenove_WS2812B_Controller strip(I2C_ADDRESS, LEDS_COUNT, TYPE_GRB); // initialization

int light_counter = 0;
int led_power = 0;

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

void lights_setup()
{

  while (!strip.begin())
    ;
  currentPos = 0;
  prePos = 9;
  currentColor = RED;
  nextColor = WHITE;
  strip.setAllLedsColor(255, 0, 0);
}

void lights_loop()
{
  if (remote_ready == false)
    return;

  brightness = Pack.pot2 / 4;

  if (Pack.s2 == 0)
  {
    s2_pressed = true;
  }

  if (Pack.s2 == 1 && s2_pressed == true)
  {
    s2_pressed = false;

    currentColor = nextColor;
    nextColor++;
    if (nextColor >= 7)
    {
      nextColor = 0;
    }
    Serial.print("current color : ");
    Serial.println(currentColor);
    Serial.print("next color : ");
    Serial.println(nextColor);
  }
  switch (currentColor)
  {
  case 0:
    strip.setAllLedsColorData(0, 0, 0);
    Serial.println("case BLACK");
    break;

  case 1:
    strip.setAllLedsColorData(brightness, brightness, brightness);
    Serial.println("case WHITE");
    break;

  case 2:
    strip.setAllLedsColorData(brightness, 0, 0);
    Serial.println("case RED");
    break;

  case 3:
    strip.setAllLedsColorData(0, brightness, 0);
    Serial.println("case GREEN");
    break;

  case 4:
    strip.setAllLedsColorData(0, 0, brightness);
    Serial.println("case BLUE");
    break;

  case 5:
    strip.setAllLedsColorData(brightness, brightness, 0);
    Serial.println("case YELLOW");
    break;

  case 6:
    strip.setAllLedsColorData(brightness, 0, brightness);
    Serial.println("case Purple");
    break;

  default:
    break;
  }
  strip.show();
}
