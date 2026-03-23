String options(byte a) {
  if (a == 0) return "LED 1 Turn on       ";
  else if (a == 1) return "LED 1 Turn off      ";
  else if (a == 2) return "LED 2 Turn on       ";
  else if (a == 3) return "LED 2 Turn off      ";
  else if (a == 4) return "LED 3 Turn on       ";
  else if (a == 5) return "LED 3 Turn off         ";
  else if (a == 6) return "Option 6            ";
  else if (a == 7) return "Option 7            ";
  else if (a == 8) return "Option 8            ";
  else if (a == 9) return "Option 9            ";
  else if (a == 10) return "Option 10            ";
  else if (a == 11) return "Option 11           ";
}


 int  Index = 0,temp = -1, base = 0, peak = 7, limit = 11;
byte panel() {

  display.setTextSize(1);
 

  while (1) {

      display.clearDisplay();
      for (int i = base; i <= peak; i++) {
        (i == Index) ? text(options(i), 0, (i - base) * 8, 0) : text(options(i), 0, (i - base) * 8, 1);
      }
      display.display();
   

    //Interrupt service routine
    if (int_flag) {
      int_flag = 0;
      // Read the current state of inputCLK
      currentStateCLK = digitalRead(inputCLK);

      // If the previous and the current state of the inputCLK are different then a pulse has occured
      if (currentStateCLK != previousStateCLK) {
        // If the inputDT state is different than the inputCLK state then
        // the encoder is rotating counterclockwise
        if (digitalRead(inputDT) != currentStateCLK) {
          Index++;
          if (Index >= limit) Index = limit;
          if (Index > peak) {
            peak = Index;
            base = peak - 7;
          }
        } else {
          // Encoder is rotating clockwise
          Index--;
          if (Index < 0) Index = 0;
          if (Index < base) {
            base = Index;
            peak = base + 7;
          }
        }
        //Serial.println(encoderChange);
      }
      // Update previousStateCLK with the current state
      previousStateCLK = currentStateCLK;
    }

    if(buttonPressed)
    {
      buttonPressed = 0; 
      return Index + 1; 
    }
  }
}