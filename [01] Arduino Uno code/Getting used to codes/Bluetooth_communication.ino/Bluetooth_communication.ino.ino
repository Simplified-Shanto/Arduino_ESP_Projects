#include<LiquidCrystal.h>
#include<math.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  lcd.begin(16, 2);
  pinMode(10,OUTPUT);
  pinMode(6,INPUT);  //ONE-1 BUTTON
  pinMode(7,INPUT);  //ZERO-0 BUTTON
  pinMode(8,INPUT);  //SEND BUTTON
  pinMode(9,INPUT);  //CLEAR BUTTON
  Serial.begin(9600);

}
const int one = 6;
const int zero = 7;
const int sen = 8;
const int del = 9;

int a,b,c,d,e,bd=150;
int base;

String j ;
char com;
void loop() {
  if(millis()%7000==0){             //Data sending to keep the bluetooth module connected.
    Serial.println("Carry on!");
  }
  
  if(digitalRead(one)!=0){
    digitalWrite(10,HIGH);
    j+='1';
    delay(bd);
    digitalWrite(10, LOW);
  }
  
  if(digitalRead(zero)!=0){
    digitalWrite(10, HIGH);
    j+='0';
    delay(bd);
    digitalWrite(10, LOW);
  }
  
  if(digitalRead(sen)!=0){
    digitalWrite(10,HIGH);
    Serial.println(j);
    lcd.setCursor(4,1);
    lcd.print("Sent!");
    delay(200);
    lcd.clear();
    digitalWrite(10,LOW);
  }
  
  if(digitalRead(del)!=0){
    digitalWrite(10, HIGH);
     lcd.clear();    
       j = "";
    delay(100);
    digitalWrite(10,LOW);
  }
  
 if(Serial.available()!=0){
com = Serial.read();
 }
 base = 0;
  for(int i = j.length()-1, k = 0; i>=0; i--, k++){
    if(j[i]=='1'){
      base+=pow(2,k);
    }
  }
  lcd.setCursor(0,0);
  lcd.print(j);
  lcd.setCursor(0,1);
  lcd.print("Dec: ");
  lcd.setCursor(4,1);
  lcd.print(base);

}
