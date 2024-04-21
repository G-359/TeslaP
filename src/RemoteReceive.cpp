/**********************************************************************
  Filename    : Receive_Data.ino
  Product     : Freenove 4WD Car for UNO
  Description :Receive data from remote control and print it to monitor.
  Auther      : www.freenove.com
  Modification: 2019/08/06
**********************************************************************/
#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"
#include "beep.h"
#include "Servo.h"  //servo liberary
#include "Led.h"
#define PIN_SERVO 2 // define servo pin

Servo servo;          // create servo object to control a servo
#define PIN_SPI_CE 9
#define PIN_SPI_CSN 10

RF24 radio(PIN_SPI_CE, PIN_SPI_CSN); // define an object to control NRF24L01
const byte addresses[6] = "Vic";     // set commucation address, same to remote controller
int nrfDataRead[8];                  // define an array to save data from remote controller

int Servo_degree;
bool Change = false;
int pre_value = 0;

struct My_pack_st
{
  int pot1;
  int pot2;
  int x;
  int y;
  int z;
  int s1;
  int s2;
  int s3;
};

struct My_pack_st P;

void remote_setup()
{
  Serial.begin(9600);

  pinMode(PIN_SERVO, OUTPUT);
  servo.attach(PIN_SERVO);      // initialize servo


  // NRF24L01
  if (radio.begin())
  {                                      // initialize RF24
    radio.setPALevel(RF24_PA_MAX);       // set power amplifier (PA) level
    radio.setDataRate(RF24_1MBPS);       // set data rate through the air
    radio.setRetries(0, 15);             // set the number and delay of retries
    radio.openWritingPipe(addresses);    // open a pipe for writing
    radio.openReadingPipe(1, addresses); // open a pipe for reading
    radio.startListening();              // start monitoringtart listening on the pipes opened
    Serial.println("Start listening remote data ... ");
  }
  else
  {
    Serial.println("Not found the nrf chip!");
  }
}

void remote_loop()
{

  if (radio.available())
  {                            // if receive the data
    radio.read(&P, sizeof(P)); // read data

    float Servo_degree = 180.0 / 1023.0 * (float)P.pot1;

    Serial.print(P.pot1);
    Serial.print(" ");
    // Serial.print(P.pot2);
    // Serial.print(" ");
    // Serial.print(P.s1);
    // Serial.print(" ");
    // Serial.print(P.s2);
    // Serial.print(" ");
    // Serial.print(P.s3);
    // Serial.print(" ");
    // Serial.print(P.x);
    // Serial.print(" ");
    // Serial.print(P.y);
    // Serial.print(" ");
    // Serial.print(P.z);
    // Serial.print(" ");

    Serial.print('\t');

    Serial.print('\n');
    if (P.s1 != pre_value)
    {
      if (P.s1 == 1)
      {
        Change =  true;
      }
      pre_value = P.s1;
    }
    Serial.print(Servo_degree);
    {
      servo.write(0 + Servo_degree); // Calibrate servo
    }
  }
}
