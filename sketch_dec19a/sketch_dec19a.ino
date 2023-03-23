#include <SoftwareSerial.h>
SoftwareSerial ard(8,7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ard.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(ard.available()>0){
    int val = ard.parseInt();
    Serial.println(val);
  }
  
  delay(1000);
}
