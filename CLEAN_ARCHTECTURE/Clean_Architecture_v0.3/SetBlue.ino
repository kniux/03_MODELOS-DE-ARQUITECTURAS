void SetBlue(){
  byte blue = 160;  
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CHSV(blue, 255, 255);
    FastLED.show();
    fadeall();
    delay(LED_DELAY);
  }
}  
