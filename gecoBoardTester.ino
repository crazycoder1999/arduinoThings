#include <FastLED.h>

#define LED_PIN     21 //21
#define LED_GROUP   5
#define NUM_LEDS    200
#define step 5

int start = 0;

int end = step;

CRGB leds[NUM_LEDS];
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {  
    for (int c = 0; c<NUM_LEDS; c++) { //sblanko
      leds[c] = CRGB (0, 0, 0);
    }

    for (int l = start; l<end; l++) {
      int b = 130;
      leds[l] = CRGB (0, 0, b);
    }
    FastLED.show();  
    delay(350);
    start = end;
    end += step;
    if (end > NUM_LEDS) {
      start = 0;
      end = step;
    }
}
/*
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {  
  for (int i = 0; i<NUM_LEDS-LED_GROUP; i++) {
    for (int b = 0; b<150; b+=5) {
      leds[i] = CRGB (0, 0, b);
      leds[i+1] = CRGB (0, 0, b);
      leds[i+2] = CRGB (0, 0, b);
      leds[i+3] = CRGB (0, 0, b);
      FastLED.show();
      delay(50);
    }
    for (int b = 150; b>=0; b-=5) {
      leds[i] = CRGB (0, 0, b);
      leds[i+1] = CRGB (0, 0, b);
      leds[i+2] = CRGB (0, 0, b);
      leds[i+3] = CRGB (0, 0, b);
      FastLED.show();
      delay(50);
    }
  }
}*/
