/*This piece of program is written to make use of 74HC595 shift register
 * a bit easier and flexible. Having these codes in your programme, let's
 * you use the extra pins created as easily as you would use the built
 * in pins. Notice few things. 
 * 1. No pinmode declaration is necessary, if done it'll result in error. 
 * 2. New digital pins are indexed as 14 to 21. 
 * 3. To toggle the state of any pin extra pin  x (13<x<22) 
 *    call DigitalWrite(x, STATE); 
 *    
 *    
 *    The driver part demonstrates the function call by turning ON 
 *    and OFF 8 leds one by one connected on the extra pins. 
 */

//Change the pin numbers as you connect it with your microcontroller
const int latchPin = 10;  //Pin 12 of 74HC595 shift register
const int clockPi
n = 11;  //Pin 11 of the 74HC595 shift register
const int dataPin = 12;   //Pin 14 of the 74HC595 shift register

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

 boolean extraPinState[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //Initially all extra pins are turned low

//digtalWrite() function for the new extra pins
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
