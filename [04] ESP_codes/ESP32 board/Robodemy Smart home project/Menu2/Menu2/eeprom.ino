void memory_read() {
  led1_state = EEPROM.read(0);
  led2_state = EEPROM.read(1);
  led3_state = EEPROM.read(2);
  led2_brightness = EEPROM.read(3);
  led1_blink_time = EEPROM.read(4);
  led2_blink_time = EEPROM.read(5);
}