#include <Arduino.h>
#include <Wire.h>

#include "Bluetooth/BLHandler.h"

BLHandler bluetooth(MACadd, BLUETOOTH_NAME, (char*)BLUETOOTH_PIN);

/*
Components:
1. Bluetooth Handler
2. Gyro Handler
3. Servo Handler
4. LCD Handler
*/

void setup()
{
    bluetooth.setup(BLUETOOTH_NAME, true);
}

void loop()
{

}