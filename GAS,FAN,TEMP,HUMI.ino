#define BLYNK_TEMPLATE_ID "TMPL6YDlIlUOZ"
#define BLYNK_TEMPLATE_NAME "FanGas"
#define BLYNK_AUTH_TOKEN "pkV9u7yZY_3xGveDRSd_kliqrtbjEOrR"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <DHT.h>


DHT dht(D3,DHT11); 
#define MQ2 A0

char auth[]= LYNK_AUTH_TOKEN;
char ssid[]="Muu";  
char pass[]="12345678";

BlynkTimer timer;
int enA=D8;
int in1=D7;
int in2=D6;

void sendSensor() {
  float h=dht.readHumidity();
  float t=dht.readTemperature();

  if(isnan(h)||isnan(t)){
    Serial.println("Failed!");
    return;
  }

  if(t>33&&t<37){
      analogWrite(enA,100);
      delay(20);
    	digitalWrite(in1,HIGH);
	    digitalWrite(in2,LOW);
      delay(2000);
  }else if(t>37&&t<40){
    analogWrite(enA,170);
    digitalWrite(in1,HIGH);
	    digitalWrite(in2,LOW);
      delay(2000);
  }else if(t>40){
    analogWrite(enA,250);
    digitalWrite(in1,HIGH);
	    digitalWrite(in2,LOW);
      delay(2000);
  }
  else{
    digitalWrite(in1,LOW);
	    digitalWrite(in2,LOW);
  }
  

  Blynk.virtualWrite(V0,h);
  Blynk.virtualWrite(V1,t);
}
void gassensor() {
  int value=analogRead(MQ2);
  Serial.println(value);
  value=map(value,0,1024,0,100);
  Blynk.virtualWrite(V2, value);

}
void setup() {
  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);
	pinMode(in2,OUTPUT);
  Blynk.begin(auth,ssid,pass);
  dht.begin();
  timer.setInterval(100L,gassensor);
  timer.setInterval(100L,sendSensor);
  digitalWrite(in1,LOW);
	digitalWrite(in2,LOW);
}

void loop() {
  Blynk.run();
  timer.run();
}