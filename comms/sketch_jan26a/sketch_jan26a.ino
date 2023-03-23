#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(10, 9); // RX, TX
int LED = LED_BUILTIN; // the on-board LED
int Data; // the data received
 
void setup() {
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("Waiting for command...");
  Bluetooth.println("Send 1 to turn on the LED. Send 0 to turn Off");
  pinMode(LED,OUTPUT);
 
}
 
void loop() {
  if (Bluetooth.available()){ //wait for data received
    Data=Bluetooth.read();
    if(Data=='a'){  
      digitalWrite(LED,HIGH);
      Serial.println("LED On!");
      Bluetooth.println("LED On!");
    }
    else if(Data=='b'){
       digitalWrite(LED,LOW);
       Serial.println("LED Off!");
       Bluetooth.println("LED Off ! ");
    }
    else{;}
  }
delay(100);
}