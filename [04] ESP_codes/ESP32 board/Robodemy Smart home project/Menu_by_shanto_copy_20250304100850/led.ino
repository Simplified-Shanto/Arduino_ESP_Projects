String led_options(byte a) {
  if (a == 0) return "       ";
  else if (a == 1) return "LED 1 status       ";
  else if (a == 2) return "LED 2 status       ";
  else if (a == 3) return "LED 3 status       ";
  else if (a == 4) return "LED 1 brightness        ";
  else if (a == 5) return "LED 2 blink time        ";
  else if (a == 6) return "LED 1 blink time        ";
  else if (a == 7) return "Option 7            ";
  else if (a == 8) return "Option 8            ";
  else if (a == 9) return "Option 9            ";
  else if (a == 10) return "Option 10            ";
  else if (a == 11) return "Option 11           ";
}


byte LED_control() {
  display.setTextSize(1);
  int index = 0, temp = -1, base = 0, peak = 7, limit = 5;
  String value; 
  while (1) {
    if (temp != index) {
      temp = index;
      display.clearDisplay();
      for (int i = base; i <= peak; i++) {
        if(i >=0 && i<=2)
        {
          value = (EEPROM.read(i)) ? "On": "Off"; 
        }
        else if(i ==3) value = String(EEPROM.read(i)); 
        else if(i > 4 && i <=5) value = String(EEPROM.read(i)*10); 
        else value = ""; 


        
        (i == index) ? text(options(i) + value, 0, (i - base) * 8, 0) : text(options(i), 0, (i - base) * 8, 1);
      }
      display.display();
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

    else if (r == 2) {  //Long press will return the particular index of 
                        //item under focus as the output of the function
      display.setTextSize(2);
      return index + 1;
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
    if (r == 2) {   //Long pressing the back button will simply exit the 
                    //menu mode
      display.setTextSize(2);
      return 0;
    }
  }
}