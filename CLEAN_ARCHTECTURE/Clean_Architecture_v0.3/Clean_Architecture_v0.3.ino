/*
 * Name: EJEMPLO DE ARQUITECTURA LIMPIA
 * created: 24/08/2022
 * Author: Edgar Cano
 * Ver: 0.3
 * Rev: 18/04/2024
 */
#include <FastLED.h>

#define NUM_LEDS   4
#define LED_DELAY  300
const byte DATA_PIN = 12;

CRGB leds[NUM_LEDS];

/******************************************************
   Functiones prototipadas
 *****************************************************/
void fadeall();
void SetRed(); 
void SetBlue(); 
void SetGreen(); 
/******************************************************
   setup and loop
 *****************************************************/
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
