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

// byte panel() {
//   display.setTextSize(1); 
//   int index = 0;  //Index of the item in the list having focus
//   int temp = -1;
//   int base = 0;    //Index of the first item in the part of the list
//                    //currently being displayed
//   int peak = 7;    //Index of the last item in the part of the list
//                    //currently being displayed
//   int limit = 11;  //Total number of items in the list.
//   while (1) {
//     if (temp != index) {
//       temp = index;
//       display.clearDisplay();
//       for (int i = base; i <= peak; i++) {
//         if (i == index)  //The selected item out of all the displaying
//         {                //items on the display
//           text(options(i), 0, (i - base) * 8, 0);
//           //Printing the selected item in the list with inactive color(black)
//         } else {
//           {
//             text(options(i), 0, (i - base) * 8, 1);
//           }
//         }
//         display.display(); 
//       }

//       byte r = push(select); //Getting the status of the select button
//       Serial.println(r); 
//       // if(r == 1)
//       // {
//       //   index++;
//       //   Serial.println(index);  
//       //   if(index >= limit) index = limit; 
//       //   if(index > peak)
//       //   {
//       //     peak = index; 
//       //     base = peak - 7; 
//       //   }
//       // }

//       // else if (r==2)  //Means that, we've selected something
//       // {
//       //   display.setTextSize(2); 
//       //   return index + 1; 
//       // }

//       // r = push(back); //Getting the status of the back button

//       // if(r==1)
//       // {
//       //   index--; 
//       //   if(index < 0) index = 0; 
//       //   if(index < base)
//       //   {
//       //     base = index; 
//       //     peak = base + 7; 
//       //   }
//       // }

//       // if(r==2)
//       // {
//       //   display.setTextSize(2); 
//       //   return 0; 
//       // }
      
//     }
//   }
// }

byte panel() {
  display.setTextSize(1);
  int index = 0, temp = -1, base = 0, peak = 7, limit = 11;
  while (1) {
    if (temp != index) {
      temp = index;
      display.clearDisplay();
      for (int i = base; i <= peak; i++) {
        (i == index) ? text(options(i), 0, (i - base) * 8, 0) : text(options(i), 0, (i - base) * 8, 1);
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