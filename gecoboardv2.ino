/*

  BLE_Peripheral.ino
  This program uses the ArduinoBLE library to set-up an Arduino Nano 33 BLE 
  as a peripheral device and specifies a service and a characteristic. Depending 
  of the value of the specified characteristic, an on-board LED gets on. 

  The circuit:
  - Arduino Nano 33 BLE. 

*/

#include <ArduinoBLE.h>

const int MAXLEDSDISPLAYED = 14; 
int ledMapping[200]; // more or less are 200 leds
int ledsToShow[MAXLEDSDISPLAYED]; // to the board
const char* deviceServiceUuid =   "9ecadc24-0ee5-a9e0-93f3-a3b5-0100406e";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
BLEService gestureService("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
BLEStringCharacteristic gestureCharacteristic("6E400002-B5A3-F393-E0A9-E50E24DCCA9E", BLERead | BLEWrite, 2000);

void setupLedMap() {
  int l;
  for(l=0;l<200;l++) {
    ledMapping[l] = 0;
  }
  ledMapping[180] = 1;
  ledMapping[179] = 2;
  ledMapping[143] = 3;
  ledMapping[108] = 4;
  ledMapping[107] = 5;
  ledMapping[71] = 6;
  ledMapping[36] = 7;
  ledMapping[35] = 8;
  ledMapping[1] = 9;
  ledMapping[34] = 10;
  ledMapping[37] = 11;
  ledMapping[73] = 12;
  ledMapping[106] = 13;
  ledMapping[142] = 14;
  ledMapping[145] = 15;
  ledMapping[182] = 16; //inizio riga 3 geco board
  ledMapping[177] = 17;
  ledMapping[141] = 18;
  ledMapping[110] = 19;
  ledMapping[105] = 20;
  ledMapping[69] = 21;
  ledMapping[38] = 22;
  ledMapping[2] = 23;
  ledMapping[32] = 24; //inizio riga 4
  ledMapping[39] = 25;
  ledMapping[75] = 26;
  ledMapping[104] = 27;
  ledMapping[111] = 28;
  ledMapping[140] = 29;
  ledMapping[147] = 30;
  ledMapping[176] = 31;
  ledMapping[184] = 32; // inizio riga 5
  ledMapping[148] = 33;
  ledMapping[103] = 34;  
  ledMapping[67] = 35;
  ledMapping[40] = 36;
  ledMapping[4] = 37;
  ledMapping[30] = 38;  // inizio riga 6
  ledMapping[66] = 39;
  ledMapping[77] = 40;
  ledMapping[113] = 41;
  ledMapping[138] = 42;  
  ledMapping[174] = 43;
  ledMapping[173] = 44; // inizio riga 7
  ledMapping[114] = 45; 
  ledMapping[101] = 46; 
  ledMapping[42] = 47; 
  ledMapping[29] = 48; 
  ledMapping[7] = 49;  // inizio riga 8
  ledMapping[28] = 50; 
  ledMapping[43] = 51; 
  ledMapping[79] = 52; 
  ledMapping[115] = 53; 
  ledMapping[151] = 54; 
  ledMapping[172] = 55; 
  ledMapping[187] = 56; 
  ledMapping[188] = 57; // inizio riga 9
  ledMapping[135] = 58; 
  ledMapping[63] = 59; 
  ledMapping[27] = 60; 
  ledMapping[8] = 61; 
  ledMapping[26] = 62; // inizio riga 10
  ledMapping[45] = 63; 
  ledMapping[98] = 64; 
  ledMapping[117] = 65;
  ledMapping[134] = 66; 
  ledMapping[170] = 67; 
  ledMapping[190] = 68; // inizio riga 11
  ledMapping[133] = 69; 
  ledMapping[97] = 70; 
  ledMapping[82] = 71; 
  ledMapping[61] = 72; 
  ledMapping[10] = 73; 
  ledMapping[60] = 74; // inizio riga 12
  ledMapping[96] = 75; 
  ledMapping[155] = 76; 
  ledMapping[191] = 77; 
  ledMapping[192] = 78; // inizio riga 13 
  ledMapping[167] = 79; 
  ledMapping[120] = 80; 
  ledMapping[95] = 81; 
  ledMapping[48] = 82; 
  ledMapping[23] = 83; 
  ledMapping[12] = 84; 
  ledMapping[22] = 85; // inizio riga 14
  ledMapping[85] = 86; 
  ledMapping[94] = 87; 
  ledMapping[121] = 88; 
  ledMapping[130] = 89; 
  ledMapping[157] = 90; 
  ledMapping[194] = 91; // inizio riga 15
  ledMapping[129] = 92; 
  ledMapping[57] = 93; 
  ledMapping[50] = 94; 
  ledMapping[14] = 95; 
  ledMapping[15] = 96; // inizio riga 16
  ledMapping[20] = 97; 
  ledMapping[92] = 98; 
  ledMapping[123] = 99; 
  ledMapping[159] = 100; 
  ledMapping[195] = 101; 
  ledMapping[196] = 102; // inizio riga 17
  ledMapping[160] = 103; 
  ledMapping[127] = 104; 
  ledMapping[124] = 105; 
  ledMapping[55] = 106; 
  ledMapping[52] = 107; 
  ledMapping[19] = 108; 
  ledMapping[17] = 109; // inizio riga 18
  ledMapping[54] = 110; 
  ledMapping[90] = 111; 
  ledMapping[125] = 112;
  ledMapping[126] = 113; 
  ledMapping[197] = 114; 
}

int ledsFound = 0;

int getLed(int l) {
  return ledMapping[l] - 1;
}

void convertLeds(String sequence) {
  String currentNumber = "";
  ledsFound = 0;
  for (int i = 0; i < sequence.length(); i++) {
    char c = sequence[i];

    if (isDigit(c)) {
      currentNumber += c; // Append the digit to our temporary string
    } 
    else if (currentNumber.length() > 0) {
      // We hit a non-digit character, so the number we were building is finished
      ledsToShow[ledsFound] = getLed(currentNumber.toInt());
      ledsFound++;
      currentNumber = ""; // Reset for the next number
    }
  }

}

void displayLeds(){
  //arduino code.
}

void setup() {

  setupLedMap();
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
  String gesture = "";
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
        String gestureTok = gestureCharacteristic.value();
        Serial.println("Received: ");
        Serial.println(gestureTok);
        gesture = gesture + gestureTok;
        int gestureLen = gesture.length();
        if(gestureLen > 0 && gesture[0]=='l' && gesture[gestureLen-1]=='#') {
            Serial.println("To be converted");
            Serial.println(gesture);
            convertLeds(gesture);
            if(ledsFound > 0){
              Serial.println("Converted: ");
              for(int l = 0;l<ledsFound;l++) {
                Serial.print(ledsToShow[l]);
                Serial.print(",");
              }
              Serial.println("");
            } else {
              Serial.println("Converted NONE");
            }
            displayLeds();
            gesture = "";
        }
      }

    }
    
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, LOW);
  
    Serial.println("* Disconnected to central device!");
  }

}
