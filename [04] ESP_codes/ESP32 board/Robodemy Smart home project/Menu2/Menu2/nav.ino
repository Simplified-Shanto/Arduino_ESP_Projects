String options(byte a) {
  if (a == 0) return "LED Control         ";
  else if (a == 1) return "Gas Sensor Read     ";
  else if (a == 2) return "Temp Sensor Read    ";
  else if (a == 3) return "Option 4            ";
  else if (a == 4) return "Option 5            ";
  else if (a == 5) return "Option 6            ";
  else if (a == 6) return "Option 7            ";
  else if (a == 7) return "Option 8            ";
  else if (a == 8) return "Option 9            ";
  else if (a == 9) return "Option 10           ";
  else if (a == 10) return "Option 11           ";
  else if (a == 11) return "Option 12           ";
}

byte panel() {
  display.set1X();
  int index = 0, temp = -1, base = 0, peak = 7, limit = 11;
  while (1) {
    if (temp != index) {
      temp = index;
      // display.clearDisplay();
      for (int i = base; i <= peak; i++) {
        (i == index) ? text(options(i), 0, (i - base), 0) : text(options(i), 0, (i - base), 1);
      }
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

    else if (r == 2) return index + 1;

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