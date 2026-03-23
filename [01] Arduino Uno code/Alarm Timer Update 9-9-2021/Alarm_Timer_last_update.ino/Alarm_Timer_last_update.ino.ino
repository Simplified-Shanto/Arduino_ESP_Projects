
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte pauseButton[] = {                                                          //  pauseButton Design
  B00000,
  B10000,
  B11000,
  B11100,
  B11110,
  B11100,
  B11000,
  B10000
};
byte playButton[] = {                                                           //   PlayButton Design
  B00000,
  B00000,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B00000
};

byte percentBlock[] = {                                                          //  Percent Block Design
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

const int buzzerPin = 13;                                                         //  PIN declaration
const int resetPin = 6;
const int pausePin = 7;
const int incrementPin = 8;
const int decrementPin = 9;
const int pauseLED = 10;

unsigned long long int a,b,c=0;
int sm = 0,h=0;                                                                   //Variable declaration
int pause = 0;
int bd=200;
int counter = 0;
int finish=0;
int reset=0;
int counting=0;
int counter2 = 0;
const int SECOND = 50;
int key = 0;

void setup() {
  pinMode(8,INPUT);                                                               //Setup block
  pinMode(9,INPUT);
  pinMode(7,INPUT);
  pinMode(6,INPUT);
  pinMode(13, OUTPUT);
  lcd.begin(16, 2);
  lcd.createChar(0, playButton);
  lcd.createChar(1, pauseButton);
  lcd.createChar(2, percentBlock); 
}
void PauseCheck()
{
  if(digitalRead(pausePin)!=0 && sm!=0)                                           //  PAUSE FUNCTION
  {
      delay(250);                                                     
    if(pause==2)                                                       
    {                                                                                                                   
     counting = 0;
     pause = 1;
     digitalWrite(pauseLED, HIGH);
     lcd.setCursor(9,0);
     lcd.write(byte(1));
    }
    else 
    {
      counting = 1;      //Indicating couneter to pause counting
      pause = 2;        //The counter is paused
      digitalWrite(pauseLED, LOW);
    }
  }
}



void loop() {
  if(pause==0 && digitalRead(incrementPin)!=0  && counting==0)                 // INCREMENTING sm
  {
    sm++;
    delay(bd);
  }
  if(pause==0 && digitalRead(decrementPin)!=0 && sm>0 && counting ==0)         // DECREMENTING sm
  {
    sm--;
    delay(bd);
     if(sm==9)
     {
      lcd.clear();
     }
  }
 
  if(digitalRead(resetPin)!=0 && counting!=1)                                   // RESET FUNCTIONALITY
  {
    delay(250);
    a=0,b=0,c=0,h=0;
    sm = 0;
    counter = 0;
    counter2 = 0;
    reset = 1;
    finish = 0;
    counting = 0;
    pause = 0;
    key = 0; //buzzer
    digitalWrite(buzzerPin, LOW);
    lcd.setCursor(9,0);
    lcd.print(" ");
     lcd.clear();
  }
  
  PauseCheck();
  
  if(counting ==1)                                                             // COUNTING SECTION
  {
    lcd.setCursor(9,0);
     lcd.write(byte(0));
    counting = 1;

    int pos2 = counter/60,ob=12;
    if(pos2>9) --ob;
    if(pos2>99) --ob;
    lcd.setCursor(ob,0);
    lcd.print(pos2);
    lcd.setCursor(13,0);
    lcd.print(":");
    int pos = counter%60;
    if(pos<=9)
    {
      
      lcd.setCursor(14,0);
      lcd.print("0"); 
      lcd.setCursor(15,0); 
    }
    else 
    {
      lcd.setCursor(14,0);
      
    }
   lcd.print(pos);
   counter++;                                                                                // Counter section
delay(200);
PauseCheck();
delay(200);
PauseCheck();
delay(200);
 PauseCheck();
 delay(200);
 PauseCheck();
 delay(194);
 PauseCheck();    
   
    //PERCENTAGE PRINTING START                                                               //PERCENTAGE
    int percent = (counter*16)/(sm*60);
    if(percent>0)
    {
      lcd.setCursor(percent-1,1);
    lcd.write(byte(2));
    }
     //PERCENTAGE PRINTING END
  }

  if(counter/60==sm && counting==1)                                                 //FINISH MESSAGE SECTION
  {
      finish = 1;
    //counter = 0;
    counting = 0;
    pause = 0;
    lcd.clear();
    lcd.setCursor(4,0);
  lcd.print("FINISHED!");
   key = 1;      
  }                                                                                   //  Buzzer
 if(key)                                                                                  
 {
  if(c==0)
  {
  a = millis();
  c=1;
  }
  b= millis();
  if((b-a)>=750)
  {
    ++h;
    a = b;
    digitalWrite(buzzerPin, HIGH);
  }
   if(h==2)
  {
    h=0;
    digitalWrite(buzzerPin , LOW);
  }
 }
  
  if(finish == 0)
  {
    if(sm<10)
    {
      lcd.setCursor(2,0);
    }
    else
    {
      lcd.setCursor(1,0);
    }
  lcd.print(sm);
  lcd.setCursor(4,0);
  lcd.print("min");
  lcd.setCursor(8,0);
  lcd.print("|");
  }
  
}

 
