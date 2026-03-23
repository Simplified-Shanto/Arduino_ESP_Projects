byte push() {
  bool long_press_flag = 0;
  if (buttonPressed == 1) {
    buttonPressed = 0; 
    delay(20);  //debounce delay
   // uint32_t t = millis();
    while (digitalRead(encoderButtonPin==0)) {
      if (millis() - lastPress > 500) {
        long_press_flag = 1;
        digitalWrite(13, 1);
      }
    }
    digitalWrite(13, 0);
    if (long_press_flag)
      return 2; //A long press has been detected
    else return 1;  //A short press has been detected
  }

  return 0;  //The button is not being pressed when push()
             // function is being called.
}