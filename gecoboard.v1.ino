/*

  BLE_Peripheral.ino
  This program uses the ArduinoBLE library to set-up an Arduino Nano 33 BLE 
  as a peripheral device and specifies a service and a characteristic. Depending 
  of the value of the specified characteristic, an on-board LED gets on. 

  The circuit:
  - Arduino Nano 33 BLE. 

*/


#include <ArduinoBLE.h>

//const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
//const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceUuid =   "9ecadc24-0ee5-a9e0-93f3-a3b5-0100406e";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
BLEService gestureService("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
//BLECharacteristic rxCharacteristic("6E400002-B5A3-F393-E0A9-E50E24DCCA9E", BLEWriteWithoutResponse, 20);
//BLECharacteristic txCharacteristic("6E400003-B5A3-F393-E0A9-E50E24DCCA9E", BLENotify, 20);

//BLEByteCharacteristic gestureCharacteristic("6E400002-B5A3-F393-E0A9-E50E24DCCA9E", BLERead | BLEWrite);
BLEStringCharacteristic gestureCharacteristic("6E400002-B5A3-F393-E0A9-E50E24DCCA9E", BLERead | BLEWrite, 2000);

String gesture = "";

//BLEService gestureService(deviceServiceUuid); 
//BLEByteCharacteristic gestureCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);

void setup() {

  Serial.begin(9600);
  while (!Serial);  

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LED_BUILTIN, LOW);

  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("GecoBoard");
  BLE.setAdvertisedService(gestureService);
  gestureService.addCharacteristic(gestureCharacteristic);
  BLE.addService(gestureService);
  gestureCharacteristic.writeValue("Hello");
  BLE.advertise();

  Serial.println("Nano 33 BLE (Peripheral Device)");
  Serial.println(" ");
}


void loop() {

  BLEDevice central = BLE.central();

  Serial.println("- Waiting for central device connecting...");
  delay(500);


  if (central) {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
    Serial.println("* Connected. Device MAC address: ");
    Serial.println(central.address());
    Serial.println(" ");

    while (central.connected()) {
      if (gestureCharacteristic.written()) {
         gesture = gestureCharacteristic.value();
         Serial.print("Received... ");
         Serial.println(gesture);
       }

    }
    
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, LOW);
  
    Serial.println("* Disconnected to central device!");
  }

}

