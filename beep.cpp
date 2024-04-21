#include <Arduino.h>
#include "Ultrasonic.h"
#include "struct.h"
#include "nrf_remote.h"

// int beepNumber = 0;
int beepPin = A0;
int beep_counter = 0;
int beepPower;

int rangeToBeeptime()
{
    if (range > 50)
        return -1;
    if (range < 10)
        return -2;
    return 50 + range * (950 / 40);
}

void beep_setup()
{
    pinMode(beepPin, OUTPUT);
    digitalWrite (beepPin, LOW);
}

void beep_loop()
{
    // buzzer control
    if (remote_ready == false)
    {
        return;
    } 

    if (Pack.joystick_z == 0)
    {
        digitalWrite(beepPin, HIGH);
    }
    else
    {
        digitalWrite(beepPin, LOW);
    }

    // int T = rangeToBeeptime();
    // switch (T)
    // {
    // case -1:
    //     digitalWrite(beepPin, LOW);
    //     break;
    // case -2:
    //     digitalWrite(beepPin, HIGH);
    //     break;
    // default:
    //     if (beep_counter > T / 10)
    //     {
    //         beep_counter = 0;
    //         if (beepPower == 0)
    //         {
    //             digitalWrite(beepPin, HIGH);
    //             beepPower = 1;
    //         }
    //         else if (beepPower == 1)
    //         {
    //             digitalWrite(beepPin, LOW);
    //             beepPower = 0;
    //         }
    //     }
    //     break;
    // }
}