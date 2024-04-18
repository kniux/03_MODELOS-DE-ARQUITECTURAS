void fadeall(){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i].nscale8(250);
  }
}
