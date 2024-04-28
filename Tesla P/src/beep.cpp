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
    digitalWrite(beepPin, LOW);
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
}