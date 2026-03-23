//Challenge: Upgrade this piano to a level where we can record currenttunes, delete them etc. 

//Update 1: (31-01-2023) Replacing push buttons with matrics keypad. 

//Update 2: (08-02-2023) Including push buttons along with keypad due to inability to implement long press in keypad. 

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
#define pause   150
#define ledPin  A0  //LED connected to A0 to indicate whether it's recording or not. 

unsigned short notes[6] = {0, 262, 294, 330, 392, 440}; 

void setup() {
  Serial.begin(9600); 
  pinMode(A1, INPUT_PULLUP); 
  pinMode(A2, INPUT_PULLUP); 
  pinMode(A3, INPUT_PULLUP); 
  pinMode(A4, INPUT_PULLUP); 
  pinMode(A5, INPUT_PULLUP); 

  pinMode(ledPin, OUTPUT); 

}

long long lastPress = millis(); 
char Key; 
byte isRecording = 0; //Whether we are recording the notes or not. 
byte notesIndex[300];     //Notes will and durations will be recorded sequentially in those arrays. 
int duration[300]; 
byte lastNote = 0;   //The last note we played to be saved in the array. 
int lastNoteStart = 0; //The duration of the last note played in milli second. 
int noteCounter = 0; //The number of entries we have made to our notes and duration array. 

int startRecording = millis(); //variable to hold the starting time of the recording. 

int analogPins[5] = {A1, A2, A3, A4, A5}; 

void loop() {
 for(int i = 0; i<5; i++)
 {
  if(digitalRead(analogPins[i])==LOW)
  {
    tone(speaker, notes[i+1]); 
    lastPress = millis(); 
  }

  if(millis() - lastPress > 200)
  {
  noTone(speaker); 
  lastPress = millis(); 
  }

 }

}
