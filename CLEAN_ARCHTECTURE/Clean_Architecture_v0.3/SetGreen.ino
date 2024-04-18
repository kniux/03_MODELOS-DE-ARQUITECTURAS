void SetGreen(){
  byte green = 96;  
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CHSV(green, 255, 255);
    FastLED.show();
    fadeall();
    delay(LED_DELAY);
  }
}  
