#include <Arduino.h>

void key_setup()
{
    Serial.begin(9600);
    Serial.setTimeout(100);
}

void key_loop()
{
    String cmd = Serial.readString();
    if (cmd == "whoismaster")
    {
        Serial.println ("me");
    }
    else
    {
        Serial.println ("nobody");
    }
}