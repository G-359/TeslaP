// define
#include <Arduino.h>
#include "Ultrasonic.h"
#include "struct.h"

#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT 4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT 6

int wheel_counter = 0;
int turning_on = 0;
int turning_right = 1;
int back_counter = 0;
int last_pack_update = 0;
int motorRun_max = 255;
int motorRun_min = -255;

// wheel speed control
int acceleration = 0;
int direction = 0;
int spin_speed_l;
int spin_speed_r;
int base_speed = 100;
int current_speed = 0;
bool stop = true;

// int cm; //replace cm in the code with range.

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
    spin_speed_l = base_speed;
    spin_speed_r = base_speed;
}

// functions

void wheel_start()
{
    motorRun(100, 100);
}

void wheel_stop()
{
    motorRun(0, 0);
}

// void wheel_speedHigh(unsigned int kmph)
// {
// }

// void wheel_speedLow(unsigned int kmph)
// {
// }

// void wheel_brake(unsigned int kmph)
// {
// }

// void wheel_run()
// {
//     motorRun(255, 255);
// }

void wheel_backward()
{
    motorRun(-100, -100);
}

// void wheel_left()
// {
//     motorRun(70, 215);
// }

// void wheel_right()
// {
//     motorRun(255, 30);
// }

// void wheel_back_left()
// {
//     motorRun(-50, -250);
// }

// void wheel_back_right()
// {
//     motorRun(-255, -30);
// }

// void eightShapeRun()
// {
//     if (wheel_counter < 500)
//     {
//         return;
//     }
//     if (turning_right == 1)
//     {
//         wheel_left();
//         turning_right = 0;
//     }
//     else if (turning_right == 0)
//     {
//         wheel_right();
//         turning_right = 1;
//     }
//     wheel_counter = 0;
// }

// main

void wheel_setup()
{
    Serial.begin(9600);
    wheel_stop();
    current_speed = base_speed;
    // wheel_right();
    // turning_right = 1;

    // wheel_start();
    // state = START;
}

void wheel_loop()
{

    if (last_pack_update != pack_update)
    {
        last_pack_update = pack_update;
        acceleration = Pack.joystick_x - 508;
        direction = Pack.joystick_y - 509;
        // current_speed = current_speed + acceleration;
        // 1023, 1023
        // Serial.println(Pack.joystick_x);
        // Serial.println(Pack.joystick_y);
        // Serial.println(acceleration);
        // Serial.println(direction);

        // set the running speed
        if (acceleration < 0)
        {
            current_speed--;
            if (current_speed <= 0)
            {
                wheel_backward();
            }
        }
        else if (acceleration > 0)
        {
            current_speed++;
        }

        // set the direction

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


        // stop
        if (Pack.s_1 == 0)
        {
            wheel_stop();
            reset_speed();
        }
        else
        {
            motorRun(spin_speed_l, spin_speed_r);
        }

        // if (Pack.joystick_z == 0)
        // {
        //     if (state == STOP)
        //     {
        //         stop = false;
        //     }
        //     else
        //     {
        //         stop = true;
        //     }

        // }

        // if (stop == true)
        // {
        //     wheel_stop();
        //     state = STOP;
        // }

        // else
        // {
        //     wheel_start();
        //     state = RUN;
        // }

        // Serial.print("motorRun(");
        // Serial.print(spin_speed_l);
        // Serial.print(",");
        // Serial.print(spin_speed_r);
        // Serial.println(")");
    }

    // speed = 150;
    // wheel_forward();

    // if (wheel_counter > 1.5)
    // {
    //     wheel_counter = 0;
    //     return;
    // }

    // switch (state)
    // {
    // case START:
    //     wheel_run();
    //     state = RUN;
    //     break;

    // case RUN:
    //     if (range > 30)
    //     {
    //         return;
    //     }
    //     wheel_stop();
    //     state = STOP;
    //     break;

    // case STOP:
    //     if (range <= 30)
    //     {
    //         wheel_back_left();
    //         state = BACK_LEFT;
    //         back_counter = 0;
    //     }
    //     else
    //     {
    //         wheel_run();
    //         state = RUN;
    //     }
    //     break;
    // case BACK_LEFT:
    //     if (back_counter < 100)
    //     {
    //         return;
    //     }
    //     wheel_stop();
    //     state = STOP;
    //     break;

    // default:
    //     break;
    // }
}