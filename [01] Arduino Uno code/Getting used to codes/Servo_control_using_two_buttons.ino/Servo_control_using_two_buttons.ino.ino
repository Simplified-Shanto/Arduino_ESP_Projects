#include<Servo.h>
Servo x;
Servo y;

void setup(){
pinMode(2,INPUT);//down;
pinMode(3,INPUT);//up
pinMode(4,INPUT);//right
pinMode(5,INPUT);//left
pinMode(6,INPUT);//fire
pinMode(8,OUTPUT);//Laser
x.attach(9);//x axis
y.attach(10);//y axis
Serial.begin(9600);
}

int a,b,xr=90,yr=112,e,c,d,f,w=5;

void loop(){
a = digitalRead(2);
b = digitalRead(3);
c = digitalRead(4);
d = digitalRead(5);
f = digitalRead(6);



if(b!=0){
  if(yr<180){
    yr++;
  }
}
if(a!=0){
  if(yr>0){
    yr--;
  }
}
y.write(yr);
delay(w);



if(c!=0){
  if(xr<180){
    xr++;
  }
}
if(d!=0){
  if(xr>0){
    xr--;
  }
}
x.write(xr);
delay(w);

if(f!=0){
  digitalWrite(8,HIGH);
 delay(10);
  digitalWrite(8,LOW);
  Serial.write("\nFiring\n");
  }

}
