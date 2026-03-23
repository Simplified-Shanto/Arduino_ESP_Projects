byte push(byte pin_number) {
  bool long_press_flag = 0;
  if (!digitalRead(pin_number)) {
    delay(20);  //debounce delay
    uint32_t t = millis();
    while (!digitalRead(pin_number)) {
      if (millis() - t > 500) {
        long_press_flag = 1;
        digitalWrite(13, 1);
      }
    }
    digitalWrite(13, 0);
    if (long_press_flag) return 2;
    else return 1;
  }
  return 0;
}