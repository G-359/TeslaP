#include <Arduino.h>

// ultrasonic
const int tringPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 8;  // Echo Pin of Ultrasonic Sensor
int flexiPower = 0;
int range;
int max_range_index = 11;
int us_measure_timer;

long microsecondsToInches(long microseconds)
{
    return microseconds / 74 / 2;
}


long microsecondsToCentimeters(long microseconds)
{
    return microseconds / 29 / 2;
}


void us_setup()
{
    // Servo_setup();
   Serial.begin(9600); // Starting Serial Terminal
}

void us_loop()
{
    long duration, cm;
    pinMode(tringPin, OUTPUT);
    digitalWrite(tringPin, LOW);
    delayMicroseconds(2);
    digitalWrite(tringPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(tringPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);
    if (duration > 0)
    {
        range = cm;
    }
}
