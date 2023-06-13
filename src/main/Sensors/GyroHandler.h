#pragma once

#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu6050(Wire);

typedef struct
{
    /* data */
    float sudut;
    float sudutAwal;
    float sudutReal;

    static void _staticTaskFunc(void *pvParam);
    void _taskFunc();

    void setup(bool console);

} GyroHandler_t;

void GyroHandler_t::setup(bool console)
{
    mpu6050.begin();
    mpu6050.calcGyroOffsets(console);
}

/* STATIC */ void GyroHandler_t::_staticTaskFunc(void* pvParam)
{
    GyroHandler_t* handler = reinterpret_cast<GyroHandler_t*>(pvParam);
    handler->_taskFunc();
}