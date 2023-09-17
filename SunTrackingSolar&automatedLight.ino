#include <Servo.h> 

#define LDR_1 A0 
#define LDR_2 A1
#define LDR_3 A2

Servo servo;
int led=13;
int pos=127; 
int Resistance=20;  
  
void setup(){
pinMode(LDR_1,INPUT); 
pinMode(LDR_2,INPUT); 
pinMode(LDR_3,INPUT); 
pinMode(13,OUTPUT);

servo.attach(4); 
servo.write(pos); 
delay(1000); 
}

void loop(){      
int value_1=analogRead(LDR_1); 
int value_2=analogRead(LDR_2); 
int value_3=analogRead(LDR_3); 

if(value_3<100){
  digitalWrite(led,LOW);
}else{
  digitalWrite(led,HIGH);
}
      
if((abs(value_1-value_2)<=Resistance)||(abs(value_2-value_1)<=Resistance)){

}else {
if(value_1>value_2) 
{
pos=pos+1; 
}
if(value_1<value_2) 
{
pos=pos-1; 
}
}
     
if(pos>180){
  pos=180;
  } 
if(pos<75){
  pos=75;
  } 
servo.write(pos); 
delay(50);

}
