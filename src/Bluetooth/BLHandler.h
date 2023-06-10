#pragma once

#include "AppConfig.h"
#include "BLDefinition.h"
#include "BluetoothSerial.h"

class BLHandler
{
private:
    /* data */
    BluetoothSerial SerialBT;
    String name;
    char *pin;
    bool connected;
    char Databluetooth;
    TaskHandle_t _taskHandle;

    static void _staticTaskFunc(void *pvParam);
    void _taskFunc();

public:
    BLHandler(String MACadd_, String name_, char *pin_);
    ~BLHandler();

    void setup(String name_, bool isMaster_ = false);
};

BLHandler::BLHandler(String MACadd_, String name_, char *pin_)
{
    name = name_;
    pin = pin_;
}

BLHandler::~BLHandler()
{
}

void BLHandler::setup(String name_, bool isMaster_)
{
    SerialBT.begin(name_, !isMaster_);
    connected = SerialBT.connect(address);

    // Serial.println(connected ? "Connected Successfully!" : SerialBT.connected(10000) ? "" : "Failed to connect. Make sure remote device is available and in range, then restart app.");
    ESP_LOGD(BLHANDLERTAG, connected ? "Connected Successfully!" : SerialBT.connected(10000) ? "" : "Failed to connect. Make sure remote device is available and in range, then restart app.");
    if (SerialBT.disconnect())
        Serial.println("Disconnected Succesfully!");
    SerialBT.connect();

    xTaskCreate(&BLHandler::_staticTaskFunc,
                CONFIG_BL_HANDLER_TASK_NAME,
                CONFIG_BL_HANDLER_TASK_STACK,
                this,
                CONFIG_BL_HANDLER_TASK_PRIO,
                &_taskHandle);

}

/*STATIC*/ void BLHandler::_staticTaskFunc(void *pvParam)
{
    BLHandler *handler = reinterpret_cast<BLHandler *>(pvParam);
    handler->_taskFunc();
}

void BLHandler::_taskFunc()
{
    ESP_LOGD(BLHANDLERTAG, "Bluetooth Handler Task Started");

    while (1)
    {
        if (SerialBT.available())
        {
            //    Serial.write(SerialBT.read());
            Databluetooth = SerialBT.read();
            if (Databluetooth == '1')
            {
                ESP_LOGD(BLHANDLERTAG, "Data Bluetooth: %d", Databluetooth);
                ESP_LOGD(BLHANDLERTAG, "masukkkk coyyyyyyyyyyyyyyyyyyyyyyyy");

                // sudutlock = sudut;

                // lockservo = servoPosition;
                // myServo.write(lockservo);
                // tekan = 0;
            }
        }
    }
    vTaskDelete(NULL);
}
