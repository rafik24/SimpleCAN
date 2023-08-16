#include <Arduino.h>
#include "simplecan.h" // <- this is the only include required, it should be smart enough to find the correct subclass

CanFrame rxFrame = {}; // <- these will get reused, so declare them globally
CanFrame txFrame = {}; // <- this will be passed in by reference and set within writeFrame

Can can(CAN_RX, CAN_TX, CAN_SHDN); // <-- define these as build flags or replace with your own pin numbers (see platformio.ini)

void setup()
{
    Serial.begin(230400);
    delay(2000);

    can.init(CAN_LOOPBACK, 250000); // <- start in LOOPBACK mode (for testing), and move to NORMAL mode later
    can.filter(FILTER_ACCEPT_ALL);  // <- accepting all frames, without this readFrame won't work
    can.start();                    // <- start CAN peripheral, if CAN_SHDN is defined, it will also enable CAN transceiver

    // prepare frame
    txFrame.identifier = 0x321; // <- 11-bit identifier (standard).
    txFrame.isExtended = false; // <- frame is STANDARD type
    txFrame.isRTR = true;       // <- this is a remote frame, not a data frame
    txFrame.dataLength = 0;     // <- all boards support 8 bytes (can 2b), but some boards support 4 bytes (fdcan)

    delay(500);
}

void loop()
{
    can.writeFrame(&txFrame); // <- send remote frame. As mode is LOOPBACK, it will be received even without CAN transsceiver connected
    delay(1);

    if (can.readFrame(&rxFrame) == CAN_OK) // <-- CAN_ERROR, typically means no data available
    {
        Serial.print("polling read: ");
        Serial.print(rxFrame.identifier, HEX);
        if (rxFrame.isExtended)
            Serial.println(" Extended ✅");
        else
            Serial.println(" Standard ✅");
    }

    delay(2000);
}