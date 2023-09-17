const int trigger=9;
const int echo=10;

long duration;
int distance;

void setup(){
  // Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT); 
}
void loop() {
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);

  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);

  digitalWrite(trigger,LOW);

  duration=pulseIn(echo,HIGH);
  distance=duration*0.034/2;

  if(distance>=5){
    digitalWrite(3,LOW);
  }
  else{
    digitalWrite(3,HIGH);
  }
  // Serial.print("Distance: ");
  // Serial.println(distance);
}