#include "Us.h"
#include <Arduino.h>

int buzzerPin = A0;
int beepOn = 0;
int beep_toggle = HIGH;
int beepcounter = 0;

int RangeToBeepTime(int cm)
{
    if (cm == 0)
    {
        return -3;
    }
    else if (cm < 10)
        return -1;
    else if (cm > 100)
        return -2;
    else
        return (50 + ((200 - 50) / (100 - 10)) * (cm - 10)) / 10;
}

    void beep_on()
    {
        digitalWrite(buzzerPin, LOW);
    }
    void beep_off()
    {
        digitalWrite(buzzerPin, HIGH);
    }


void beep_setup()
{
    pinMode(buzzerPin, OUTPUT);
}

void beep_loop()
{

    int T = RangeToBeepTime(range);
    // Serial.print(T);
    // Serial.print(" ms,  counter= ");
    // Serial.println(beepcounter);

    switch (T)
    {
    case -1:
        digitalWrite(buzzerPin, HIGH);
        break;

    case -2:
        digitalWrite(buzzerPin, LOW);
        break;
    case -3:
        return;
        break;
    default:
        if (beepcounter > T)
        {
            beepcounter = 0;

            if (beep_toggle == HIGH)
            {
                beep_toggle = LOW;
                digitalWrite(buzzerPin, LOW);
            }
            else
            {
                beep_toggle = HIGH;
                digitalWrite(buzzerPin, HIGH);
            }
        }
        break;
    }
}