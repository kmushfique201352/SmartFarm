#include <Servo.h>
#include <Stepper.h>

const int leftButton=2;
const int rightButton=3;
const int redLed=4;
const int whiteLed=5;
const int servoPin=6;
const int rtnbtn=7;
const int stepsPerRevolution=2040;
Servo myservo;
volatile int count=0;
bool leftButtonPreviouslyPressed=false;
bool rightButtonPreviouslyPressed=false;
Stepper steppername1=Stepper(stepsPerRevolution,8,10,9,11);

int LDRInput=A0;  
int LED=12;
int laserPin=13;
int onButton=14;  
int offButton=15;
bool systemState=false; 

void setup() {
  pinMode(leftButton,INPUT_PULLUP);
  pinMode(rightButton,INPUT_PULLUP);
  pinMode(redLed,OUTPUT);
  pinMode(whiteLed,OUTPUT);
  pinMode(rtnbtn,INPUT_PULLUP);
  steppername1.setSpeed(15);
  myservo.attach(servoPin);
  myservo.write(0); 
  digitalWrite(redLed,HIGH);
  digitalWrite(whiteLed,LOW);
  
  pinMode(LDRInput,INPUT);
  pinMode(LED,OUTPUT);
  pinMode(laserPin,OUTPUT);
  pinMode(onButton,INPUT_PULLUP);
  pinMode(offButton,INPUT_PULLUP);
  digitalWrite(laserPin,LOW);  
  digitalWrite(LED,LOW); 
  
}

void loop() {
  bool leftButtonPressed=!digitalRead(leftButton);
  bool rightButtonPressed=!digitalRead(rightButton);
  int rtnbtnstate=digitalRead(rtnbtn);
  if(leftButtonPressed && !leftButtonPreviouslyPressed){
    if(count==0){
      digitalWrite(redLed,LOW);
    }else{
      startServoMovement();
    }
  }
  if(rightButtonPressed && !rightButtonPreviouslyPressed){
    count++;
    flashWhiteLed();
  }
  leftButtonPreviouslyPressed=leftButtonPressed;
  rightButtonPreviouslyPressed=rightButtonPressed;
  if(rtnbtnstate==LOW){
    rtn();
  }

  if(digitalRead(onButton)==LOW){
    systemState=true;
    while(digitalRead(onButton)==LOW); 
  }
  if(digitalRead(offButton)==LOW){
    systemState=false;
    while(digitalRead(offButton)==LOW);
  }
  if(systemState){
    digitalWrite(laserPin,HIGH); 
    int value=analogRead(LDRInput);
    if(value<300){
      for(int i=0;i<=5;i++){
        digitalWrite(LED,HIGH);
        delay(500);
        digitalWrite(LED,LOW);
        delay(500);
      }
    }else{
      digitalWrite(LED,LOW);
      delay(5000);
    }
  }else{
    digitalWrite(laserPin,LOW);
    digitalWrite(LED,LOW);
  }
}

void startServoMovement(){
  digitalWrite(redLed,HIGH);
  digitalWrite(whiteLed,HIGH);
  for(int i=0;i<count;i++){
    myservo.write(6); 
    steppername1.step(stepsPerRevolution);
    delay(1000); 
    myservo.write(0); 
    for(int j=0;j<6;j++){
      steppername1.step(stepsPerRevolution);
    }
    delay(10);     
  }
  myservo.write(0);
  count=0;
  digitalWrite(whiteLed,LOW);
  digitalWrite(redLed,HIGH);
}

void flashWhiteLed(){
  digitalWrite(whiteLed,HIGH);
  delay(500); 
  digitalWrite(whiteLed,LOW);
}

void rtn(){
  myservo.write(10); 
  delay(10);
  for(int j=0;j<6;j++){
      steppername1.step(-stepsPerRevolution);
  }
  delay(10);
  myservo.write(0); 
}
