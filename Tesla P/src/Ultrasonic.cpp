#include <Arduino.h>

// ultrasonic
const int tringPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 8;  // Echo Pin of Ultrasonic Sensor
int flexiPower = 0;
int range;
int current_range_index = 0;
int max_range_index = 11;
int ultrasonic_measurment_timer;
bool ultrasonic_redy_for_servo = false;

long microsecondsToInches(long microseconds)
{
    return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
    return microseconds / 29 / 2;
}

void Ultrasonic_setup()
{
    Serial.begin(9600); // Starting Serial Terminal
}

void Ultrasonic_loop()
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
    ultrasonic_redy_for_servo = true;
}