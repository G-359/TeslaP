#include <Arduino.h>
#include "ultrasound.h"
#include "packets.h"

#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT 4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT 6


typedef enum wheel_state
{
    START = 0,
    STOP = 1,
    RUN = 2,
    BACK = 3,
    BACK_LEFT = 4,
    BACK_RIGHT = 5
} wheel_state_t;
wheel_state_t state;

void motorRun(int speedl, int speedr)
{
    int dirL = 0, dirR = 0;
    if (speedl > 0)
    {
        dirL = 0;
    }
    else
    {
        dirL = 1;
        speedl = -speedl;
    }
    if (speedr > 0)
    {
        dirR = 1;
    }
    else
    {
        dirR = 0;
        speedr = -speedr;
    }
    digitalWrite(PIN_DIRECTION_LEFT, dirL);
    digitalWrite(PIN_DIRECTION_RIGHT, dirR);
    analogWrite(PIN_MOTOR_PWM_LEFT, speedl);
    analogWrite(PIN_MOTOR_PWM_RIGHT, speedr);
}

void reset_speed()
{
    int spin_speed_l;
    int spin_speed_r;
    int base_speed = 100;
    spin_speed_l = base_speed;
    spin_speed_r = base_speed;
}

void wheel_start()
{
    motorRun(100, 100);
}

void wheel_stop()
{
    motorRun(0, 0);
}

void wheel_backward()
{
    motorRun(-100, -100);
}

void wheel_setup()
{
    int base_speed = 100;
    int current_speed = 0;
    Serial.begin(9600);
    wheel_stop();
    current_speed = base_speed;
}

void wheel_loop()
{
    int last_pack_update = 0;
    int acceleration = 0;
    int direction = 0;
    int spin_speed_l;
    int spin_speed_r;
    int current_speed = 0;

    if (last_pack_update != packet_id)
    {
        last_pack_update = packet_id;
        acceleration = Pack.x - 508;
        direction = Pack.y - 509;
        if (acceleration < 0)
        {
            wheel_backward();
        }
    }
    else if (acceleration > 0)
    {
        current_speed++;
    }

    if (direction <= -5)
    {
        spin_speed_l = current_speed + direction;
        spin_speed_r = current_speed;
    }
    else if (direction > -5 && direction < 5)
    {
        spin_speed_l = current_speed;
        spin_speed_r = current_speed;
    }
    else
    {
        spin_speed_l = current_speed;
        spin_speed_r = current_speed - direction;
    }

    if (Pack.s1 == 0)
    {
        wheel_stop();
        reset_speed();
    }
    else
    {
        motorRun(spin_speed_l, spin_speed_r);
    }
}