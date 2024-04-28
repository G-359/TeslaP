#include <Arduino.h>
#include "app-servo.h"
#include "ultrasound.h"
#include "packets.h"

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
  // servo
  servo_direction = 180.0 / 1023.0 * (float)Pack.pot1;
  vero.write(servo_direction);

  // if (servo_done == true)
  //   return;
  // if (servo_counter >= 50)
  // {
  //   servo_counter = 0;
  //   if (us_ready_for_servo == true)
  //   {
  //     vero.write(servo_index * 18);
  //     distance[servo_index] = range;
  //     // servo_counter = 0;
  //     us_ready_for_servo = false;
  //     servo_index++;
  //     if (servo_index > 11)
  //     {
  //       // servo_index = 0;
  //       min_distance = 10000;
  //       min_distance_index = 0;
  //       pV = &distance[0];
  //       for (int i = 0; i < 11; i++)
  //       {
  //         if (*pV < min_distance)
  //         {
  //           min_distance = *pV;
  //           min_distance_index = i;
  //         }
  //         pV++;
  //       }
  //       // min_distance = range;
  //       // Serial.println("Maximum distance : ");
  //       // Serial.println(min_distance);
  //       // Serial.println(range);
  //       // Serial.println("Maximum distance's range index : ");
  //       // Serial.println(min_distance_index);
  //       vero.write(min_distance_index * 18);
  //       servo_done = true;
  //     }
  //   }
  // }
}
