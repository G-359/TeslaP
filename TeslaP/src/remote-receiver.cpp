#include <SPI.h>
#include <RF24.h>
#include <EEPROM.h>

#include "packets.h"

#define PIN_SPI_CE 9
#define PIN_SPI_CSN 10

RF24 radio(PIN_SPI_CE, PIN_SPI_CSN); // define an object to control RF24L01
byte remote_name[6];   // set commutation address, same to remote controller
struct my_pack_st Pack;              // define an array to save data from remote controller
int packet_id = 0;
bool remote_ready = false;

void remote_rx_setup()
{

#if 1
EEPROM.put(0, "ZXM123");
#endif

    // RF24L01 initialization steps
    if (radio.begin())
    {                                       // initialize RF24
        EEPROM.get(0, remote_name);
        radio.setPALevel(RF24_PA_MAX);       // set power amplifier (PA) level
        radio.setDataRate(RF24_1MBPS);       // set data rate through the air
        radio.setRetries(0, 15);             // set the number and delay of retries
        radio.openWritingPipe(remote_name);    // open a pipe for writing
        radio.openReadingPipe(1, remote_name); // open a pipe for reading
        radio.startListening();              // start monitoringtart listening on the pipes opened
        Serial.println("Start listening remote data ... ");
    }
    else
    {
        Serial.println("Not found the RF chip!");
    }
}

void remote_rx_loop()
{
    if (!(radio.available()))
    {
        return;
    }
    radio.read(&Pack, sizeof(Pack)); // read data
    remote_ready = true;
    packet_id++;

    // for (int i = 0; i < sizeof(P) / 2; i++)
    Serial.print(Pack.pot1);
    Serial.print(' ');
    Serial.print(Pack.pot2);
    Serial.print(' ');
    Serial.print(Pack.x);
    Serial.print(' ');
    Serial.print(Pack.y);
    Serial.print(' ');
    Serial.print(Pack.z);
    Serial.print(' ');
    Serial.print(Pack.s1);
    Serial.print(' ');
    Serial.print(Pack.s2);
    Serial.print(' ');
    Serial.print(Pack.s3);
    Serial.print('\n');
}