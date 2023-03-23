#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(10, 9); // RX, TX
int LED = LED_BUILTIN; // the on-board LED
int Data; // the data received
 
void setup() {
  Serial.begin(9600);
  //Serial.println("Waiting for command...");
  pinMode(LED,OUTPUT);
}
 
void loop() {
  if (Serial.available()){ //wait for data received
    Data=Serial.read();
    if(Data=='1'){  
      digitalWrite(LED,HIGH);
      Serial.println("LED On!");
      
    }
    else if(Data=='0'){
       digitalWrite(LED,LOW);
       Serial.println("LED Off!");
       
    }
    else{;}
  }
delay(10);
}