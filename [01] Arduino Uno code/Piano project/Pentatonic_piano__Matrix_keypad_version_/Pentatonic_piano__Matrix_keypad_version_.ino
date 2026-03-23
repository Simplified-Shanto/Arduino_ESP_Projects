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
#define pause   200
#define ledPin  A0  //LED connected to A0 to indicate whether it's recording or not. 

unsigned short notes[6] = {0, 262, 294, 330, 392, 440}; 
unsigned short analogPins[5] = {A1, A2, A3, A4, A5}; //Those five pins are connected to 
                                          // five buttons (piano key). 

void setup() {
  Serial.begin(9600); 
  pinMode(A1, INPUT_PULLUP); 
  pinMode(A2, INPUT_PULLUP); 
  pinMode(A3, INPUT_PULLUP); 
  pinMode(A4, INPUT_PULLUP); 
  pinMode(A5, INPUT_PULLUP); 

  pinMode(ledPin, OUTPUT); 

}

unsigned long long lastPress = millis(); 
char Key; 
byte isRecording = 0; //Whether we are recording the notes or not. 
byte notesIndex[300];     //Notes will and durations will be recorded sequentially in those arrays. 
int duration[300]; 
byte lastNote = 0;   //The last note we played to be saved in the array. 
unsigned long lastNoteStart = 0; //The duration of the last note played in milli second. 
unsigned short noteCounter = 0; //The number of entries we have made to our notes and duration array. 

long long startRecording = millis(); //variable to hold the starting time of the recording. 


void loop() {
  Key = matrixKeypad.getKey();
  
  if(Key=='*')//We are triggering the recording. 
  {
     startRecording = millis();          //(isRecording==0?millis():startRecording); 
    lastNoteStart = millis(); 
    isRecording = 1 - isRecording; 
    //Problem: Variable isRecording is being set to 0 unexpectedly. 
    Serial.print("isRecording = "); 
    Serial.println(isRecording); 
    Serial.print("noteCounter = "); 
    Serial.println(noteCounter); 
  }
  digitalWrite(ledPin, isRecording); //We want the led to glow only when we will be recording. 
  

  if(isRecording==1 && (millis() - startRecording >= 5000 || noteCounter>=300)) //If our recording time is over, we'll stop recording and play the notes. 
  {
    Serial.print("startRecording = "); 
   // Serial.print(String(startRecording)); 
    
    digitalWrite(ledPin, 0);
    delay(1000); 
    digitalWrite(ledPin, 1); 
    for(int i = 0; i<noteCounter; i++)
    {
      tone(speaker, notes[notesIndex[i]]); 
      delay(duration[i]); 
    }
  //Resetting variables. 
  isRecording = 0; 
  noteCounter = 0; 
  lastNote = 0; 
  lastNoteStart = 0;  
  notesIndex[0] = 0; 
  
   Serial.print("isRecording = "); 
    Serial.println(isRecording); 
  }

  for(int i = 0; i<5; i++)
  {
      if( digitalRead(analogPins[i])==LOW )
      {
        tone(speaker, notes[i+1]); 
        lastPress = millis(); 
  
          if(isRecording==1 && notesIndex[noteCounter]!=i+1)
          {
            duration[noteCounter] = millis() - lastNoteStart; 
            lastNoteStart = millis(); //Starting timer for the current note. 
            notesIndex[++noteCounter] = i+1; 
            Serial.println(noteCounter); 
          }
      }
  }

   if(millis() - lastPress > pause)
    {
      noTone(speaker); 
      lastPress = millis(); 
    
       if(isRecording==1)
        {
            if(notesIndex[noteCounter]!=0)
            { 
              duration[noteCounter] = millis() - lastNoteStart; //Saving the duration of the previous note. 
              lastNoteStart = millis(); //Starting timer for the current note. 
              notesIndex[++noteCounter] = 0; 
               Serial.println(noteCounter); 
            }
        }
  }  
}
