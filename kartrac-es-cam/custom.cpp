#include <Arduino.h>
#include "custom.h"

// ========= JSON Data =========
// temp
extern String JSON_TEMP;
// ax
extern String JSON_AX;
// ay
extern String JSON_AY;
// az
extern String JSON_AZ;
// gx
extern String JSON_GX;
// gy
extern String JSON_GY;
// gz
extern String JSON_GZ;
// impact
extern String JSON_IMPACT;
// timestamp
unsigned long JSON_TIMESTAMP = 0;

// ========= Camera controls =========
extern int start_record;
extern bool IMPACT;
#define LED_FLASH 4
bool FLASHED = false;

void custom_loop()
{
    if (Serial.available())
    {
        String msg = Serial.readStringUntil('\n');
        Serial.print("Recibido: ");
        Serial.println(msg);
        handleArduinoMessage(msg);
    }

    int json_count = 0;
    if (JSON_TEMP != "")
        json_count++;
    if (JSON_AX != "")
        json_count++;
    if (JSON_AY != "")
        json_count++;
    if (JSON_AZ != "")
        json_count++;
    if (JSON_GX != "")
        json_count++;
    if (JSON_GY != "")
        json_count++;
    if (JSON_GZ != "")
        json_count++;
    if (JSON_IMPACT != "")
        json_count++;

    if (json_count > 5)
    {
        start_record = 0;
        IMPACT = true;

        if (FLASHED == false)
        {
            // Blink FLASH LED
            digitalWrite(LED_FLASH, HIGH);
            delay(20);
            digitalWrite(LED_FLASH, LOW);
            delay(20);
            digitalWrite(LED_FLASH, HIGH);
            delay(20);
            digitalWrite(LED_FLASH, LOW);
            delay(20);
            digitalWrite(LED_FLASH, HIGH);
            delay(20);
            digitalWrite(LED_FLASH, LOW);
            delay(20);
            digitalWrite(LED_FLASH, HIGH);
            delay(20);
            digitalWrite(LED_FLASH, LOW);
            delay(20);
            digitalWrite(LED_FLASH, HIGH);
            delay(20);
            digitalWrite(LED_FLASH, LOW);
            delay(100);
            digitalWrite(LED_FLASH, HIGH);
            delay(100);
            digitalWrite(LED_FLASH, LOW);
            FLASHED = true;
        }
    }
}

void handleArduinoMessage(String msg)
{
    if (!msg.startsWith("{"))
    {
        Serial.println('Unkown command');
        return;
    }

    if (contains(msg, "temp"))
        JSON_TEMP = msg;
    else if (contains(msg, "ax"))
        JSON_AX = msg;
    else if (contains(msg, "ay"))
        JSON_AY = msg;
    else if (contains(msg, "az"))
        JSON_AZ = msg;
    else if (contains(msg, "gx"))
        JSON_GX = msg;
    else if (contains(msg, "gy"))
        JSON_GY = msg;
    else if (contains(msg, "gz"))
        JSON_GZ = msg;
    else if (contains(msg, "impact"))
        JSON_IMPACT = msg;
    else
    {
        Serial.println("Unkown JSON key");
        return;
    }

    JSON_TIMESTAMP = millis();
    Serial.print("Json recieved at");
    Serial.println(JSON_TIMESTAMP);
    Serial.println(msg);
}

bool contains(String text, String searchText)
{
    return text.indexOf(searchText) >= 0;
}