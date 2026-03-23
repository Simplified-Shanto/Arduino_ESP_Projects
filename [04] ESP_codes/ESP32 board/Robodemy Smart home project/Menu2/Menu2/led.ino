String LED_options(byte a) {
  if (a == 0) return "LED 1 Status     ";
  else if (a == 1) return "LED 2 Status     ";
  else if (a == 2) return "LED 3 Status     ";
  else if (a == 3) return "LED 2 Brightness ";
  else if (a == 4) return "LED 1 Blink Time ";
  else if (a == 5) return "LED 2 Blink Time ";
  else if (a == 6) return "Option 7            ";
  else if (a == 7) return "Option 8            ";
}

byte LED_control() {
  display.set1X();
  int index = 0, temp = -1, base = 0, peak = 7, limit = 5;
  String value;
  while (1) {
    if (temp != index) {
      temp = index;
      // display.clearDisplay();
      for (int i = base; i <= peak; i++) {
        if (i >= 0 && i <= 2) {
          value = (EEPROM.read(i)) ? " On" : "Off";
        } else if (i == 3) value = String(EEPROM.read(i)) + "%";
        else if (i >= 4 && i <= 5) value = String(EEPROM.read(i) * 10);
        else value = "";

        (i == index) ? text(LED_options(i) + value, 0, (i - base), 0) : text(LED_options(i) + value, 0, (i - base), 1);
      }
      // display.display();
    }

    byte r = push(select);
    if (r == 1) {
      index++;
      if (index >= limit) index = limit;
      if (index > peak) {
        peak = index;
        base = peak - 7;
      }
    }

    else if (r == 2) {
      adjustment(index);
      temp = -1;
    }

    r = push(back);
    if (r == 1) {
      index--;
      if (index < 0) index = 0;
      if (index < base) {
        base = index;
        peak = base + 7;
      }
    }
    if (r == 2) return 0;
  }
}

void adjustment(byte i) {
  display.clear();
  display.set2X();
  int val = EEPROM.read(i);
  int temp = -1;
  byte limit;

  if (i >= 0 && i <= 2) limit = 1;
  else if (i == 3) limit = 100;
  else if (i >= 4 && i <= 5) limit = 250;



  while (1) {
    if (temp != val) {
      display.clear();
      temp = val;
      String value;
      if (i >= 0 && i <= 2) {
        value = (val) ? "ON" : "OFF";
      } else if (i == 3) value = String(val) + "%";
      else if (i >= 4 && i <= 5) value = String(val * 10);
      else value = "";
      int l = value.length();
      String display = "";
      for (int i = 0; i < (10 - l) / 2; i++) display += " ";
      display += value;
      (l % 2) ? text(display, 11, 4, 1) : text(display, 4, 4, 1);
    }

    byte r = push(select);
    if (r == 1) {
      val++;
      if (val >= limit) val = limit;
    }

    else if (r == 2) {
      EEPROM.write(i, val);
      delay(10);
      memory_read();
      break;
    }

    r = push(back);
    if (r == 1) {
      val--;
      if (val < 0) val = 0;
    }
    if (r == 2) break;
  }
  display.set1X();
}