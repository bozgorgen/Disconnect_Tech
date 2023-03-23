#include <Encoder.h>
#include <SoftwareSerial.h>
#include <util/atomic.h>

SoftwareSerial Ard(8,7);

volatile int pos_i = 0;
volatile float velocity_i = 0;
volatile long prevT_i = 0;

volatile int pos_i_b = 0;
volatile float velocity_i_b = 0;
volatile long prevT_i_b = 0;

long prevT = 0;
int posPrev = 0;
float v1Filt = 0;
float v1Prev = 0;

long prevT_b = 0;
int posPrev_b = 0;
float v1Filt_b = 0;
float v1Prev_b = 0;

int prev_time = 0;
int curr_time = 0;

int dir=0;
int dir_b=0;
float u=0;
float u_b=0;
int count1=0;
int count2=0;
int vt=20;
int vt_b=20;
Encoder knobLeft(12, 13);
Encoder knobRight(2, 3);
  int k=-1;
int y=0;
int ctr=0;
float eintegral = 0;
float eintegral_b = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
Ard.begin(9600);  
  //Encdoer 1
pinMode(12,INPUT);
pinMode(13,INPUT);
//Encoder 2
pinMode(2,INPUT);
pinMode(3,INPUT);
//Motor1
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
//Motor 2
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
//attachInterrupt(digitalPinToInterrupt(ENCA),
 //                 readEncoder,RISING);
}
extern int val = 0;
long positionLeft  = -999;
long positionRight = -999;

void wifi_read()
{
    if(Ard.available() > 0)
      val = Ard.parseInt(); 
    Serial.println(val);
    //Serial.println("Wifi read success");    
    //Serial.println("Wifi read failed");    
}
void loop() { 
  
    curr_time = millis();
    prev_time = curr_time;
    //Serial.println(ctr);
    
    if(ctr++==100){
        wifi_read();     
        ctr = 0;
    }
  //MOTOR 1 
   int pos = 0;
   float velocity2 = 0;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    pos = pos_i;
    velocity2 = velocity_i;
    }
  //MOTOR 2
   int pos_b = 0;
   float velocity2_b = 0;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    pos_b = pos_i_b;
    velocity2_b = velocity_i_b;

  }
  // put your main code here, to run repeatedly:

long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  //MOTOR 1
  if (newLeft != positionLeft) {
    
    positionLeft = newLeft;
    
  }
  //MOTOR2
    if (newRight != positionRight) {
    
    positionRight = newRight;
    
  }
  
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }
// Compute velocity with method 1
  pos=newLeft;
  pos_b=newRight;
//MOTOR 1  
  long currT = micros();
  float deltaT = ((float) (currT-prevT))/1.0e6;
  float velocity1 = (pos - posPrev)/deltaT;
  posPrev = pos;
  prevT = currT;
//MOTOR 2
  long currT_b = micros();
  float deltaT_b = ((float) (currT_b-prevT_b))/1.0e6;
  float velocity1_b = (pos_b - posPrev_b)/deltaT_b;
  posPrev_b = pos_b;
  prevT_b = currT_b;

  // Convert count/s to RPM

  float v1=velocity1/30.0*20.42;
  float v1_b=velocity1_b/30.0*20.42;
  
  // Low-pass filter (25 Hz cutoff)
  v1Filt = 0.854*v1Filt + 0.0728*v1 + 0.0728*v1Prev;
  v1Prev = v1;
  v1Filt_b = 0.854*v1Filt_b + 0.0728*v1_b + 0.0728*v1Prev_b;
  v1Prev_b = v1_b;
  int x=0;
 /*
  if(ctr%10000==0)
  {   
     vt=5*2;
     vt_b=5*2;
     ctr=0;     
  }

  else if(ctr%10000==2000)
  {   
     vt=20*2;
     vt_b=20*2;   
  }
  
    else if(ctr%10000==4000)
  {   
     vt=30*2;
     vt_b=30*2;     
  }
    else if(ctr%10000==6000)
  {   
     vt=50*2;
     vt_b=50*2;
  }
    else if(ctr%10000==8000)
  {   
     vt=60*2;
     vt_b=60*2;
  }
  */
  vt=val*2;//sol
  vt_b=val*2;
 // Serial.println(vt);

 
   //vt=20*2;
  //vt_b=20*2;
  //float vt=30*2;
  
  // Compute the control signal u
  //MOTOR 1
  float kp = 5;
  float ki = 10;
  float e = vt-v1Filt;
  if(u!=255)
    eintegral = eintegral + e*deltaT;
  
  u = kp*e + ki*eintegral;
  //MOTOR 2
  float kp_b = 5;
  float ki_b = 10;
  float e_b = vt_b-v1Filt_b;
  if(u_b!=255)
  eintegral_b = eintegral_b + e_b*deltaT_b;
  
  u_b = kp_b*e_b + ki_b*eintegral_b;
  

/*
  if(ctr%200==0)
  {   
     k*=-1;
  }
  if(k<0)
  {
    y=0;
  }
  else
  {
    y=255;    
  }
    */
    /*****
  if (u<0){
    u = 0;
  }
  if (u>255){
    u = 255;
  }

  if (u_b<0){
    u_b = 0;
  }
  if (u_b>255){
    u_b = 255;
  }

  ***/
  if (u<0){
    dir=1;
    u*=-1;
  }
  else
  {
    dir=0;
  }
    
  if (u>255){
    u = 255;
  }

  if (u_b<0){
    dir_b=0;    
    u_b *=-1;
  }
  else
  {
    dir_b=1;
  }
  if (u_b>255){
    u_b = 255;
  }

  
  
  if(dir)
  {
    analogWrite(6,u);
    analogWrite(5,0);  
  }  
   else  
  {
    analogWrite(6,0);
    analogWrite(5,u);    
  }   
    
  if(dir_b)
  {
    analogWrite(9,u_b);  
    analogWrite(10,0);      
  } 
  
  else
  {
    analogWrite(9,0);  
    analogWrite(10,u_b);      
  }
  /*
      analogWrite(6,0);
    analogWrite(5,u);   
     analogWrite(9,u_b);  
    analogWrite(10,0);      
  */
  
  Serial.print(v1Filt);
  Serial.print(',');
  //Serial.print(vt);
  //Serial.print(',');
  //Serial.print(u/5);
  //Serial.print(',');
  
  Serial.print(v1Filt_b);
  Serial.print(',');
  //Serial.print(vt_b);
  //Serial.print(',');
  //Serial.print(u_b/5);
  //Serial.print(',');
  
  Serial.print(-50);
  Serial.print(',');
  Serial.print(150);

  Serial.println();
  
  //Serial.println(val);
}
/*void readEncoder(){
  // Read encoder B when ENCA rises
  int b = digitalRead(ENCB);
  int increment = 0;
  if(b>0){
    // If B is high, increment forward
    increment = 1;
  }
  else{
    // Otherwise, increment backward
    increment = -1;
  }
  pos_i = pos_i + increment;
  */
  
