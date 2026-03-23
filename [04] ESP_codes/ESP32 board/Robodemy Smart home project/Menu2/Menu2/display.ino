void text(String t, byte x, byte y, bool c) {
  display.setCursor(x, y);
  (c) ? display.setInvertMode(0) : display.setInvertMode(1);
  display.print(t);
}