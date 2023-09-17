#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h> 

const int PulseWire=0;
const int LED=13;
int Threshold=550;
                               
PulseSensorPlayground pulseSensor;

const int buttonPin=2;
int buttonState=0; 
int lastButtonState=0;
int count=0; 

unsigned long startTime=0;
const long interval=60000;

void setup() {
  pinMode(buttonPin,INPUT_PULLUP);
  Serial.begin(9600);
  startTime=millis();

  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);
  pulseSensor.setThreshold(Threshold);   

  pulseSensor.begin();
}

void loop(){
  buttonState=digitalRead(buttonPin);
  if(buttonState==LOW&&lastButtonState==HIGH) {
    count++;
  }
  lastButtonState=buttonState;
  if (millis()-startTime>=interval) {
    startTime=millis();
    Serial.print("Last minute respiration is : ");
    Serial.println(count);
    count=0;
  }

  if (pulseSensor.sawStartOfBeat()) {            
  int myBPM=pulseSensor.getBeatsPerMinute();  

    Serial.print("BPM: ");                        
    Serial.println(myBPM);                        
  }

  delay(20);  
}
