#include <LiquidCrystal_I2C.h>
#include "Countimer.h"
#include <EEPROM.h>
#include <Stepper.h>

#define bt_set A3
#define bt_up A2
#define bt_down A1
#define bt_start A0

Countimer tdown;

LiquidCrystal_I2C lcd(0x27,16,2);
const int stepsPerRevolution=2040;

int time_s=0;
int time_m=0;
int time_h=0;

int set=0;
int flag1=0,flag2=0;


Stepper steppername1=Stepper(stepsPerRevolution,8,10,9,11);
Stepper steppername2=Stepper(stepsPerRevolution,3,5,4,6);

void setup(){
  Serial.begin(9600);

  steppername1.setSpeed(15);
  steppername2.setSpeed(15);

  pinMode(bt_set,INPUT_PULLUP);
  pinMode(bt_up,INPUT_PULLUP);
  pinMode(bt_down,INPUT_PULLUP);
  pinMode(bt_start,INPUT_PULLUP);


  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Welcome     ");
  lcd.setCursor(0,1);
  lcd.print("   Cow Dung   ");
  tdown.setInterval(print_time,999);
  eeprom_read();
  delay(1000);
  lcd.clear();
}

void print_time(){
  time_s=time_s-1;
  if(time_s<0){
    time_s=59;
    time_m=time_m-1;
  }
  if (time_m<0){
    time_m=59;
    time_h=time_h-1;
  }
}

void tdownComplete(){
  Serial.print("All ok");
}


void loop(){
  tdown.run();

  if(digitalRead(bt_set)==0){
    if(flag1==0&&flag2==0){
      flag1=1;
      set=set+1;
      if(set>3){set=0;}
      delay(100);
    }
  }else{
    flag1=0;
  }

  if(digitalRead(bt_up)==0){
    if(set==0){
      tdown.start();
      flag2=1;
    }
    if(set==1){time_s++;}
    if(set==2) {time_m++;}
    if(set==3) {time_h++;}
    if(time_s>59){time_s=0;}
    if(time_m>59){time_m=0;}
    if(time_h>99){time_h=0;}
    if(set>0){eeprom_write();}
    delay(200);
  }

  if(digitalRead(bt_down)==0){
    if(set==0){
      tdown.stop();
      flag2=0;
    }
    if(set==1){time_s--;}
    if(set==2){time_m--;}
    if(set==3){time_h--;}
    if(time_s<0){time_s=59;}
    if(time_m<0){time_m=59;}
    if(time_h<0){time_h=99;}
    if(set>0){eeprom_write();}
    delay(200);
  }

  if(digitalRead(bt_start)==0){
    flag2=1;
    eeprom_read();
    tdown.restart();
    tdown.start();
  }

  lcd.setCursor(0,0);
  if(set==0){lcd.print("      Timer     ");}
  if(set==1){lcd.print("  Set Timer SS  ");}
  if(set==2){lcd.print("  Set Timer MM  ");}
  if(set==3){lcd.print("  Set Timer HH  ");}

  lcd.setCursor(4,1);
  if(time_h<=9){lcd.print("0");}
  lcd.print(time_h);
  lcd.print(":");
  if(time_m<=9){lcd.print("0");}
  lcd.print(time_m);
  lcd.print(":");
  if(time_s<=9){lcd.print("0");}
  lcd.print(time_s);
  lcd.print("   ");

  if(time_s==0 && time_m==0 && time_h==0 && flag2==1){
    flag2=0;
    tdown.stop();
    delay(200);
    for(int x=0;x<6;x++){
      steppername1.step(stepsPerRevolution);
    }
    delay(200);
    for(int x=0;x<6;x++){
      steppername1.step(-stepsPerRevolution);
    }
    delay(1000);
    for(int x=0;x<4;x++){
      steppername2.step(-stepsPerRevolution);
    }
    delay(300);
    for(int x=0;x<4;x++){
      steppername2.step(stepsPerRevolution);
    }
    delay(300);
    
  }

  delay(1);
}

void eeprom_write() {
  EEPROM.write(1, time_s);
  EEPROM.write(2, time_m);
  EEPROM.write(3, time_h);
}

void eeprom_read() {
  time_s = EEPROM.read(1);
  time_m = EEPROM.read(2);
  time_h = EEPROM.read(3);
}
