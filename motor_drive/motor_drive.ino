void setup() {
  // put your setup code here, to run once:
pinMode(6,OUTPUT);
pinMode(3,OUTPUT);
pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(3,HIGH);
analogWrite(6,0);
analogWrite(5,255);
}
