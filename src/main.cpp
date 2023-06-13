#include <Arduino.h>
#include <Wire.h>

#include "AppConfig.h"
#include "Bluetooth/BLHandler.h"
// #include "Sensors/GyroHandler.h"

BLHandler bluetooth(MACadd, BLUETOOTH_NAME, (char*)BLUETOOTH_PIN);

/*
Components:
1. Bluetooth Handler
2. Wifi Handler
3. Gyro Handler
4. Servo Handler
5. LCD Handler
*/

void setup()
{
    Serial.begin(115200);
    // bluetooth.setup(BLUETOOTH_NAME, true); //when the device as master to anothe devices
    bluetooth.setup(BLUETOOTH_NAME); //when device as client (example when communicate with android BT)
    // GyroHandler_t gyro::setup(true);
}

void loop()
{
    vTaskDelete(NULL);
}