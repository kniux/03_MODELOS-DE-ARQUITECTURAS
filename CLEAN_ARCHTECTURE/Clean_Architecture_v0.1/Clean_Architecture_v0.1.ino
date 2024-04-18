/*
 * Name: EJEMPLO DE ARQUITECTURA LIMPIA
 * created: 24/08/2022
 * Author: Edgar Cano
 * Ver: 0.1
 * Rev: 18/04/2024
 */

#include <FastLED.h>
#define NUM_LEDS  4

const byte DATA_PIN = 12;

CRGB leds[NUM_LEDS];

void fadeall();   // Función prototipo

void setup(){
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(84);
}

void loop(){
  static byte hue = 0;  
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    delay(10);
  }
  for(int i = (NUM_LEDS) - 1; i >= 0; i--){
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    delay(10);
  }
}

 void fadeall(){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i].nscale8(250);
  }
}
