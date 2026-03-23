//Change the pin numbers as you connect it with your microcontroller
const int latchPin = 9;  //Pin 12 of 74HC595 shift register
const int clockPin = 7;  //Pin 11 of the 74HC595 shift register
const int dataPin = 8;   //Pin 14 of the 74HC595 shift register

/*We can use the following pins of the 74HC595 shift register as new digital output pins: 
 * Shift register pins                  New digital pin
 * ^^^^^^^^^^^^^^^^^^^                  ^^^^^^^^^^^^^^^
 *        15                                  14  
 *        1                                   15
 *        2                                   16
 *        3                                   17
 *        4                                   18
 *        5                                   19
 *        6                                   20
 *        7                                   21
 */        

//The new function for the extended pin 14, 15, 16, 17,  18 , 19, 20, 21 is DigitalWrite(pinNumber, state); 
boolean extraPinState[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //Initially all extra pins are turned low
void DigitalWrite(int extraPinNumber, int state)
{
  extraPinState[extraPinNumber - 14] = state; 
  /*Since there's already 13 pins in arduino UNO and we are counting the extra pins from 14....to 21 */
  unsigned short decimalValue  = 0; 
  for(int i = 0; i <= 7; i++)  //Converting the 8 bit bit pattern to decimalvalue
  { 
    decimalValue+= (ceil(pow(2, i))*extraPinState[i]); 
  }
  digitalWrite(latchPin, LOW); //Don't changing the pin state while sending data serially
  shiftOut(dataPin, clockPin, MSBFIRST, decimalValue); 

  digitalWrite(latchPin, HIGH); 
}



void setup()
{
  Serial.begin(9600); 
  pinMode(latchPin, OUTPUT); 
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, OUTPUT); 

  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, MSBFIRST, 0); //Pulling all extra pins to LOW initially
  digitalWrite(latchPin, HIGH); 
  delay(100); 
}

void loop()
{
  for(int i = 14; i<=21; i++)
  {
    DigitalWrite(i, HIGH); 
    delay(500); 
    DigitalWrite(i, LOW); 
    delay(500); 
  }

  delay(1000); 
  for(int i = 21; i>=14; i--)
  {
    DigitalWrite(i, HIGH); 
    delay(500);
    DigitalWrite(i, LOW); 
    delay(500); 
  }

  delay(1000); 
  
}
