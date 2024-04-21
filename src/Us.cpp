#include <Arduino.h>
#include <FlexiTimer2.h>
#include <beep.h>

        // create servo object to control a servo
byte servoOffset = 0; // change the value to Calibrate servo
int D[11];
int range[10];
int max = 0;
int position = 0;
int vero_counter = 0;

int MaxDistance()
{
    int maxPos=0;
    Serial.begin(9600);
    for (int i = 0; i < 11; i++)
    {
        if (D[i] > max)
        {
            max = D[i];
            maxPos=i;
        }
    }
    // servo.write(maxPos*180/10);
}
const int trigPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 8; // Echo Pin of Ultrasonic Sensor
long microsecondsToInches(long microseconds)
{
    return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
    return microseconds / 29 / 2;
}
void Us_setup()
{
    // pinMode(PIN_SERVO, OUTPUT);
    // servo.attach(PIN_SERVO);      // initialize servo
    // servo.write(0 + servoOffset); // Calibrate servo

    Serial.begin(9600); // Starting Serial Terminal
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void Us_loop()
{

    long duration;
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH, 20000);
    if (duration == 0)
    {
        pinMode(echoPin, OUTPUT);   // Then we set echo pin to output mode
        digitalWrite(echoPin, LOW); // We send a LOW pulse to the echo pin
        delayMicroseconds(200);
        pinMode(echoPin, INPUT); // And finaly we come back to input mode
        // return;
    }
    // if (vero_counter > 100)
    // {
    //     vero_counter = 0;
    //     servoOffset += 180 / 10;
    //     if (servoOffset > 180)
    //     {
    //         servoOffset = 0;
    //     }
    //     servo.write(0 + servoOffset); // Calibrate servo
    // }

    range[position] = microsecondsToCentimeters(duration);
    position++;
    if (position >= 10)
    {
        position = 0;
        int i;
        int max = 0;
        MaxDistance();

    }
    // Serial.print(cm);
    // Serial.print(" centimetres");
    // Serial.println();
}