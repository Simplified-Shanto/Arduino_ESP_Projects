/*This piece of code reads the value of 5 sensors connected from pin A1 to A5 and 
 * prints the reading in the Serial monitor in the format: 
 * 
 * readingA5|readingA4|readingA3|readingA2|readingA1
 * 
 * This reading can be used to tune line following logic. 
 * The serial data is intended to be recieved by a MIT app inventor 
 * mobile app which recieves data via Bluetooth module. 
 * 
 * Author: Nayeem Islam Shanto
 * Last modified: 19-5-2023
 * 
 * 
 */

/*Consider the car is as; 
 * 
 *  ______
 * /Front \
 * ``|  |``
 *  |    |
 * ,,|  |,,
 * \Back  /
 *  ``````
 * We name the sensors as
 * 
 * (0)Leftmost   (1)Left    (2)Middle    (3)Right   (4)Rightmost
 * 
 */

#define rightmostVal analogRead(A1)   //Value of the rightmost sensor
#define rightVal     analogRead(A2)   
#define  middleVal   analogRead(A3)   
#define  leftVal     analogRead(A4)
#define leftmostVal analogRead(A5) 

void setup() {
 Serial.begin(9600); 
  pinMode(A1, INPUT); 
  pinMode(A2, INPUT); 
  pinMode(A3, INPUT); 
  pinMode(A4, INPUT); 
  pinMode(A5, INPUT); 
}

void loop() {
Serial.print(leftmostVal); 
Serial.print('|');  
Serial.print(leftVal); 
Serial.print('|'); 
Serial.print(middleVal); 
Serial.print('|'); 
Serial.print(rightVal);
Serial.print('|'); 
Serial.print(rightmostVal);
 
 delay(500); 
}
