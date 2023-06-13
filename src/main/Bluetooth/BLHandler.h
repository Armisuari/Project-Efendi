#pragma once

#include "AppConfig.h"
#include "BLDefinition.h"
#include "BluetoothSerial.h"

// Deklarasi kelas BLHandler
class BLHandler
{
private:
    BluetoothSerial SerialBT; // Objek untuk komunikasi serial Bluetooth
    String name;              // Nama Bluetooth
    char *pin;                // PIN Bluetooth
    char Databluetooth;       // Data yang diterima dari Bluetooth
    TaskHandle_t _taskHandle; // Handle tugas untuk tugas Bluetooth

    // Fungsi statis untuk menjalankan tugas
    static void _staticTaskFunc(void *pvParam);
    // Fungsi tugas sebenarnya
    void _taskFunc();

public:
    BLHandler(String MACadd_, String name_, char *pin_);
    ~BLHandler();

    bool received = false; // Status penerimaan data
    void setup(String name_, bool isMaster_);
    void setup(String name_);
};

// Implementasi konstruktor BLHandler
BLHandler::BLHandler(String MACadd_, String name_, char *pin_)
    : name(name_), pin(pin_)
{
}

// Implementasi destruktor BLHandler
BLHandler::~BLHandler()
{
}

// Fungsi setup untuk mengatur koneksi Bluetooth
void BLHandler::setup(String name_, bool isMaster_)
{
    SerialBT.begin(name_, isMaster_);           // Memulai koneksi Bluetooth dengan nama dan mode master/slave
    bool connected = SerialBT.connect(address); // Mencoba melakukan koneksi ke alamat Bluetooth

    // Serial.println(F("The device started in master mode, make sure remote BT device is on!"));
    ESP_LOGD(BLHANDLERTAG, "The device started in master mode, make sure remote BT device is on!");

    // Menampilkan pesan tergantung apakah koneksi berhasil atau tidak
    // ESP_LOGD(BLHANDLERTAG, connected ? F("Connected Successfully!") : SerialBT.connected(10000) ? "": F("Failed to connect. Make sure remote device is available and in range, then restart app."));

    if (connected)
    {
        ESP_LOGD(BLHANDLERTAG, "Connected Successfully!");
    }
    else
    {
        while (!SerialBT.connected(10000))
        {
            ESP_LOGE(BLHANDLERTAG, "Failed to connect. Make sure remote device is available and in range, then restart app.");
        }
    }

    if (SerialBT.disconnect()) // Mencoba memutuskan koneksi Bluetooth
    ESP_LOGD(BLHANDLERTAG, "Disconnected Successfully!");

    xTaskCreate(&BLHandler::_staticTaskFunc, // Membuat tugas Bluetooth
                CONFIG_BL_HANDLER_TASK_NAME,
                CONFIG_BL_HANDLER_TASK_STACK,
                this,
                CONFIG_BL_HANDLER_TASK_PRIO,
                &_taskHandle);
}

void BLHandler::setup(String name_)
{
    SerialBT.begin(name_);           // Memulai koneksi Bluetooth dengan nama dan mode master/slave
    bool connected = SerialBT.connect(address); // Mencoba melakukan koneksi ke alamat Bluetooth

    // Serial.println(F("The device started in master mode, make sure remote BT device is on!"));
    ESP_LOGD(BLHANDLERTAG, "The device started in master mode, make sure remote BT device is on!");

    // Menampilkan pesan tergantung apakah koneksi berhasil atau tidak
    // ESP_LOGD(BLHANDLERTAG, connected ? F("Connected Successfully!") : SerialBT.connected(10000) ? "": F("Failed to connect. Make sure remote device is available and in range, then restart app."));

    if (connected)
    {
        ESP_LOGD(BLHANDLERTAG, "Connected Successfully!");
    }
    else
    {
        while (!SerialBT.connected(10000))
        {
            ESP_LOGE(BLHANDLERTAG, "Failed to connect. Make sure remote device is available and in range, then restart app.");
        }
    }

    if (SerialBT.disconnect()) // Mencoba memutuskan koneksi Bluetooth
    ESP_LOGD(BLHANDLERTAG, "Disconnected Successfully!");

    xTaskCreate(&BLHandler::_staticTaskFunc, // Membuat tugas Bluetooth
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

// Fungsi tugas sebenarnya untuk mengambil data dari Bluetooth
void BLHandler::_taskFunc()
{
    ESP_LOGD(BLHANDLERTAG, "Bluetooth Handler Task Started");

    while (1)
    {
        if (SerialBT.available()) // Memeriksa apakah ada data yang tersedia di Bluetooth
        {
            Databluetooth = SerialBT.read(); // Membaca data dari Bluetooth

            if (Databluetooth == '1') // Memeriksa apakah data yang diterima adalah '1'
            {
                ESP_LOGD(BLHANDLERTAG, "Data Bluetooth: %d", Databluetooth);
                ESP_LOGD(BLHANDLERTAG, "masukkkk coyyyyyyyyyyyyyyyyyyyyyyyy");

                received = true; // Mengatur status penerimaan data menjadi benar
            }
        }
    }
    vTaskDelete(NULL); // Menghapus tugas setelah selesai
}
