// on the arduino micro
#include <FastLED.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#define LED_PIN     6
#define LED_GROUP   5
#define NUM_LEDS    200

bool sequenceReceived = false;
int bounce = 0;
int sequence[] = {1,2,3,4,5,6,7,8};

const int rs = 22, 
          en = 23, 
          d4 = 2,
          d5 = 3,
          d6 = 4,
          d7 = 5;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int b = 50;
int g = 50;
int r = 50;

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(2400);
  Serial1.begin(2400);
  pinMode(LED_BUILTIN, OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Geco Board"));
}

void aliveLed() {
    if (bounce == 0)
      bounce = 1;
    else if(bounce == 1)
      bounce = 0;

    if(bounce == 0) {
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    } else {
      digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
    }
}

int ledsFound = 0;
const int MAXLEDSDISPLAYED = 14;
int ledsToShow[MAXLEDSDISPLAYED]; // to the board

void convertLeds(String sequence) {
  String currentNumber = "";
  ledsFound = 0;
  for (int i = 0; i < sequence.length(); i++) {
    char c = sequence[i];

    if (isDigit(c)) {
      currentNumber += c; // Append the digit to our temporary string
    } else if (currentNumber.length() > 0) {
      // We hit a non-digit character, so the number we were building is finished
      ledsToShow[ledsFound] = currentNumber.toInt();
      ledsFound++;
      currentNumber = ""; // Reset for the next number
    }
  }
}

void loop() {
    Serial.println("loop");
    sequenceReceived = false;
    if (Serial1.available() > 0) { // CHANGED
      String teststr = Serial1.readStringUntil('\n');  //read until timeout //CHANGED
      teststr.trim();
      r = 0;
      g = 0;
      b = 0;
      //Serial.print("RECV: ");
      Serial.println(teststr);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(teststr);
      if(teststr.indexOf("S;") > -1 && teststr.indexOf("E;") > -1) {
        b = 100;
      } else if (teststr.indexOf("S;") > -1 ) {
        r = 100;
      } else {
        g = 100;
      }
      sequenceReceived = true;
      convertLeds(teststr);
    }
    aliveLed();
    for (int c = 0; c<NUM_LEDS; c++) { //sblanko
      leds[c] = CRGB (0, 0, 0);
    }
    if (ledsFound > 0) {
      for (int l = 0; l<ledsFound; l++) {
        leds[ledsToShow[l]] = CRGB (r, g, b);
      }      
    } else {
      leds[0] = CRGB (r, g, b);
    }
    FastLED.show(); 
    delay(500);
  // print the number of seconds since reset:
}
