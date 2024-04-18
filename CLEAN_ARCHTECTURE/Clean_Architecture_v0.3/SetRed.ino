void SetRed(){
  byte red = 0;  
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CHSV(red, 255, 255);
    FastLED.show();
    fadeall();
    delay(LED_DELAY);
  }
}  
