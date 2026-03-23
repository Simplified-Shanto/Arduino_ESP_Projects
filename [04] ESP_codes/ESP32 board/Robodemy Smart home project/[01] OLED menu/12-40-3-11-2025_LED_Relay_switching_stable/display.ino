void text(String t, byte x, byte y, bool c)
{
  display.setCursor(x, y); 
  (c) ? display.setTextColor(1) : display.setTextColor(0, 1);
  display.print(t); 
}