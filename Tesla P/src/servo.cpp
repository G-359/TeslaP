#include <Arduino.h>
#include "Servo.h"
#include "Ultrasonic.h"
#include "struct.h"

#define SERVO_PIN 2

int servo_counter;
int servo_index = 0;
int distance[11];
int *pV;
int min_distance;
int min_distance_index;
float servo_direction = 0;
bool servo_done = false;

typedef enum direction
{
  dir_l_90 = 0,
  dir_l_72 = 18,
  dir_l_54 = 36,
  dir_l_36 = 54,
  dir_l_18 = 72,
  dir_c_0 = 90,
  dir_r_18 = 108,
  dir_r_36 = 126,
  dir_r_54 = 144,
  dir_r_72 = 162,
  dir_r_90 = 180
} direction_t;
direction_t dir;

Servo vero; // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; // variable to store the servo position

void servo_setup()
{
  vero.attach(SERVO_PIN); // attaches the servo on pin 9 to the servo object
  vero.write(direction::dir_l_90);
  Serial.begin(9600);
  servo_done = false;
}

void servo_loop()
{
  servo_direction = 180.0 / 1023.0 * (float)Pack.pot_1;
  vero.write(servo_direction);
}
