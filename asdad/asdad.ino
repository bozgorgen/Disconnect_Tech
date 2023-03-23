int ledpin = 6;
int y;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorValue = analogRead(A0);
Serial.println(sensorValue);
int y=map(sensorValue,0,1023,0,255);
analogWrite(6,y);
delay(10);
}
