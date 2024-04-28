#include <Arduino.h>

// ultrasonic
const int tringPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 8;  // Echo Pin of Ultrasonic Sensor
int flexiPower = 0;
int range;
int current_range_index = 0;
int max_range_index = 11;
int us_measure_timer;
bool us_ready_for_servo = false;

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

        // us_measure_timer = 0;

        range = cm;
        // Serial.print("distance of range ");
        // // Serial.print(current_range_index);
        // Serial.print(":");
        // Serial.print(range);
        // Serial.println("cm");
        // current_range_index++;
        // if (current_range_index == max_range_index)
        // {
        //     current_range_index = 0;
        // }
    }
    us_ready_for_servo = true;
}
