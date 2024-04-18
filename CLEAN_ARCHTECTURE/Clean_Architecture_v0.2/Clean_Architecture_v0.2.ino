/*
 * Name: EJEMPLO DE ARQUITECTURA LIMPIA
 * created: 24/08/2022
 * Author: Edgar Cano
 * Ver: 0.2
 * Rev: 18/04/2024
 */
#include <FastLED.h>

#define NUM_LEDS  4
#define LED_DELAY  300

const byte DATA_PIN = 12;
CRGB leds[NUM_LEDS];

/******************************************************
   Funciones prototipadas
 *****************************************************/
void fadeall();
void SetRed(); 
void SetBlue(); 
void SetGreen(); 
/*****************************************************/
   
void setup(){
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(84);
}

void loop(){
  SetRed();
  SetBlue();
  SetGreen();
}

void fadeall(){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i].nscale8(250);
  }
}

void SetRed(){
  byte red = 0;  
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CHSV(red, 255, 255);
    FastLED.show();
    fadeall();
    delay(LED_DELAY);
  }
}  
void SetGreen(){
  byte green = 96;  
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CHSV(green, 255, 255);
    FastLED.show();
    fadeall();
    delay(LED_DELAY);
  }
}  
void SetBlue(){
  byte blue = 160;  
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CHSV(blue, 255, 255);
    FastLED.show();
    fadeall();
    delay(LED_DELAY);
  }
}  
