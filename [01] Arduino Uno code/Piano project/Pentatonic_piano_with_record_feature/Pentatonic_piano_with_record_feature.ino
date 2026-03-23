//Challenge: Upgrade this piano to a level where we can record currenttunes, delete them etc. 
//Challenge implementation 0.1: 
/*Features: 
 * a. Simple pentatonic piano playing. 
 * b. There'll be 6 buttons in total.  
 * c. 5 buttons for playing 5 notes. 
 * d. The remaining button will be used for recording
 * e. Press the button once, the notes played in the next 45 second will be recorded, 
 *    a red led will be turned on. 
 * f. The user can finish recording before 45 second by pressing the button once again. 
 * g. After the recording process is finished, the recording will be playing withing 2 seconds. 
 * h. The user can stop it and reset everything by pressing the 6th button one more time. 
 *
 * 
 * 
 */

//Update 1: (31-01-2023) Replacing push buttons with matrics keypad. 

#include<Keypad.h> 
const byte rows = 4; 
const byte cols = 4; 

char hexaKeys[rows][cols] = 
{
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'}, 
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'} 
}; 

byte rowPins[rows] = {9, 8, 7, 6}; 
byte colPins[cols] = {5, 4, 3, 2}; 

Keypad matrixKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, rows, cols); 


#define NOTE_C  262
#define NOTE_D  294
#define NOTE_E  330
#define NOTE_G  392
#define NOTE_A  440

#define speaker 10
#define pause   200

void setup() {
 

}

long long lastPress = millis(); 
char pianoKey; 

void loop() {
  pianoKey = matrixKeypad.getKey(); 

  if(matrixKeypad.isPressed('1'))
  {
    tone(speaker, NOTE_C); 
     lastPress = millis();  
  }

  switch(pianoKey){
    case '1': 
    {
     tone(speaker, NOTE_C); 
     lastPress = millis();  
    }
    break; 
    
    case '2':
    {
      tone(speaker, NOTE_D); 
      lastPress = millis(); 
    } 
    break; 

    case '3': 
    {
       tone(speaker, NOTE_E); 
       lastPress = millis();  
    }
    break; 

    case '4': 
    {
        tone(speaker, NOTE_G); 
        lastPress = millis(); 
    }
    break;
    
    case '5': 
    {
      tone(speaker, NOTE_A); 
   lastPress = millis(); 
    }
    break; 

    default: 
    break; 
    
  }
  

  if(millis() - lastPress > pause)
  {
    
    noTone(speaker); 
    
    lastPress = millis(); 
  }
  
  

}
