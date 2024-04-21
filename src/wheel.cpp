#include <Arduino.h>
#include "Wheel.h"
#include "Us.h"

#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT 4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT 6

int back_counter;
int speed;
typedef enum wheel_state
{
    STOP = 1,
    BACK = 2,
    RUN = 0,
} wheel_state_t;

wheel_state_t state;

void motorRun(int speedl, int speedr)
{
    int dirL = 0, dirR = 0;
    speedl = -speedl;
    speedr = -speedr;
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

int wheel_counter;

void wheel_start(void)
{
    motorRun(200, 200);
}

void wheel_stop(void)
{
    motorRun(0, 0);
}

void wheel_setup()
{
    pinMode(PIN_DIRECTION_LEFT, OUTPUT);
    pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT);
    pinMode(PIN_DIRECTION_RIGHT, OUTPUT);
    pinMode(PIN_MOTOR_PWM_RIGHT, OUTPUT);
    speed = 0;
    wheel_counter = 0;
    wheel_start();
    state = RUN;
    range[0] = 10000;
}

void wheel_speedup(unsigned int kmph)
{
    if ((speed + kmph) > 1000)
        speed = 1000;
    else
        speed += kmph;
}

void wheel_brake(unsigned int kmph)
{
    if (kmph > speed)
        speed = 0;
    else
        speed -= kmph;
}

void wheel_forward()
{
    motorRun(speed, speed);
}

void wheel_backward()
{
    motorRun(-speed, -speed);
}

void wheel_left()
{
    motorRun(-speed, speed);
}

void wheel_right()
{
    motorRun(speed, -speed);
}

void wheel_backward_left()
{
    motorRun(-speed, speed);
}

void wheel_backward_right()
{
    motorRun(-50, -200);
}

void wheel_loop()
{
    switch (state)
    {
    case RUN:
        if (range[0]< 30)
        {
            wheel_stop();
            state = STOP;
        }
        break;
    case STOP:
        if (range[0]< 30)
        {
            wheel_backward_right();
            state = BACK;
            back_counter = 0;
        }
        else
        {
            wheel_start();
            state = RUN;
        }
        break;
    case BACK:
        back_counter++;
        if (back_counter > 50)
        {
            wheel_stop();
            state = STOP;
        }
        break;

    default:

        break;
    }
}