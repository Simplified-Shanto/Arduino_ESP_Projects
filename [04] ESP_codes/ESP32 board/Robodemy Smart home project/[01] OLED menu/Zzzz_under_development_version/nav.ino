int Index = 0, temp = -1, base = 0, peak = 7, limit = 11;


void printMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  for (int i = base; i <= peak; i++) {
    (i == Index) ? text(options[i], 0, (i - base) * 10, 0) : text(options[i], 0, (i - base) * 10, 1);
  }
  display.display();
}





byte panel() {
  printMenu(); 

  while (1) {
    //Interrupt service routine
    if (int_flag) {
      int_flag = 0;
      currentStateCLK = digitalRead(inputCLK);
      if (currentStateCLK != previousStateCLK) {
        if (digitalRead(inputDT) != currentStateCLK) {
          Index++;
          if (Index >= limit) Index = limit;
          if (Index > peak) {
            peak = Index;
            base = peak - 7;
          }
        }

        else {  //encoder rotating in other direction
          Index--;
          if (Index < 0) Index = 0;
          if (Index < base) {
            base = Index;
            peak = base + 7;
          }
        }
        printMenu();
      }
      // Update previousStateCLK with the current state
      previousStateCLK = currentStateCLK;
    }

    if (buttonPressed) {
      delay(200);
      buttonPressed = 0;
      return Index + 1;
    }
  }
}