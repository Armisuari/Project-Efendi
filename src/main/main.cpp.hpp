#include <Arduino.h>

#include "BluetoothSerial.h"
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <math.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

BluetoothSerial SerialBT;
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

String MACadd = "AA:BB:CC:11:22:33";
uint8_t address[6]  = {0xCC, 0xDB, 0xA7, 0x16, 0x01, 0x9A};
//uint8_t address[6]  = {0x00, 0x1D, 0xA5, 0x02, 0xC3, 0x22};
String name = "ESP32test";
char *pin = "1234"; //<- standard pin would be provided by default
bool connected;

MPU6050 mpu6050(Wire);

const int triggerPin = 12;
const int echoPin = 13;
const int servoPin = 18;
const int buttonPin = 5;
int tekan;
int servoPosition = 0;
int buttonState = 0;

float sudut;
float jarak_sudut;
float tinggis;
float sudutlock;
float sudutawal;
float sudutreal;

int lockservo;

char Databluetooth;

void setup() {
  Serial.begin(115200);
  // Wire.begin();
  // mpu6050.begin();
  // mpu6050.calcGyroOffsets(true);

  // pinMode(triggerPin, OUTPUT);
  // pinMode(echoPin, INPUT);

  // tekan=0;
  // myServo.attach(servoPin);
  // pinMode(buttonPin, INPUT_PULLUP);
  // myServo.write(servoPosition);

  // lcd.init();  // Inisialisasi LCD dengan kolom 16 dan baris 2
  // lcd.backlight();   // Mengaktifkan pencahayaan LCD
  
  
  //SerialBT.setPin(pin);
  // SerialBT.begin("ESP32test"); 
  SerialBT.begin("ESP32test", true); 
  //SerialBT.setPin(pin);
  Serial.println("The device started in master mode, make sure remote BT device is on!");
  
//  connected = SerialBT.connect(name);
  connected = SerialBT.connect(address);
  
  if(connected) {
    Serial.println("Connected Succesfully!");
  } else {
    while(!SerialBT.connected(10000)) {
    Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
    }
  }
  // disconnect() may take upto 10 secs max
  if (SerialBT.disconnect()) {
    Serial.println("Disconnected Succesfully!");
  }
  // this would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  SerialBT.connect();
  
  // mpu6050.update();
  // sudutawal=(mpu6050.getAngleX()*(-1));
}

void loop() {
  // lcd.clear();
  // mpu6050.update();
  // sudut=mpu6050.getAngleX();
  
  // digitalWrite(triggerPin, LOW);
  // delayMicroseconds(2);
  // digitalWrite(triggerPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(triggerPin, LOW);
  // long duration = pulseIn(echoPin, HIGH);
  // int distance = duration * 0.035 / 2;
  
  // buttonState = digitalRead(buttonPin);
  // Serial.print("tekan:");
  // Serial.println(tekan);
  //  if (buttonState == LOW) {
  //   tekan=1;
  // }
  //  if (tekan==1){
  //       servoPosition+=1;
  //       myServo.write(servoPosition);
  //      if (servoPosition>=90){
  //           servoPosition=90;
  //  }
  // }
  if (SerialBT.available()) {
//    Serial.write(SerialBT.read());
  Databluetooth=SerialBT.read();
    if (Databluetooth == '1'){
      Serial.println(Databluetooth);
      Serial.println("masukkkk coyyyyyyyyyyyyyyyyyyyyyyyy");
      // sudutlock=sudut;
      
      // lockservo=servoPosition;
      // myServo.write(lockservo);
      // tekan=0;
    }
  }
  
//   sudutreal=sudut-sudutawal;
//   jarak_sudut=distance;
//    float sudut_radian = radians(sudutreal);
//     // Hitung tinggi objek menggunakan rumus trigonometri
//    tinggis = ((jarak_sudut * tan(sudut_radian))*(-1));
// //  

//   // Menampilkan data pertama
//   lcd.setCursor(0, 0);
//   lcd.print("Jarak:");
//   lcd.print(distance);
//   lcd.print(" cm");
  
//   // Menampilkan data kedua
//   lcd.setCursor(0, 1);
//   lcd.print("Tinggi:");
//   lcd.print(tinggis);
//   lcd.print(" cm");

// //  Serial.print("Sudut : ");
// //  Serial.println(mpu6050.getAngleX());
// //  Serial.print("SudutLock :");
// //  Serial.println(sudutlock);
// //  Serial.print("Lock Servo :");
// //  Serial.println(lockservo);
// //  Serial.print("Jarak: ");
// //  Serial.println(distance);
// //  Serial.print("Tinggi objek adalah ");
// //  Serial.println(tinggi);
// //  Serial.print("SudutAwal");
// //  Serial.println(sudutawal);
// //  Serial.print("Sudutreal");
// //  Serial.println(sudutreal);
// //  Serial.print("Radian");
// //  Serial.println(sudut_radian);

  delay(150);
}