

#include <PIDController.h>
PIDController pid;

#define True 1
#define False 0
double  error_array[100]={0};
int set_point=0;
double error=0;
double avg_speed=0;
int switchA = 12;
int switchB = 13;
int Rcounter = 0;
int Lcounter = 0;
int output;
int switchas;
int switchals; 
bool millisStarted = False;
bool measureTime   = False;
int arr[30];
int i = 0;
int PrevTime = 0;
int CurrTime = 0;
int TimeDiff = 0;
float speed = 0;
double speed_array[100];
int counter=0;
int  K_I=10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //
  /*
  pid.begin();
  pid.setpoint(60);
  pid.tune(1,0,0);
  pid.limit(0,255);
  */
  pinMode(switchA,INPUT);
  pinMode(switchB,INPUT);
  
  switchals =digitalRead(switchA);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  set_point=30;
  
error= set_point-speed;
error_array[counter]=error;
double error_avg=0;

for(int i=0;i<100;i++)
{
    error_avg+=error_array[counter];
}
error_avg/=100;

 counter++;
counter=counter%100;

double motor_input=20*error+K_I*error_avg;

if(motor_input>255)
  motor_input=255;
else if(motor_input<0)
  motor_input=0;
  
//motor_input=255;
analogWrite(6,motor_input);
analogWrite(5,0);
analogWrite(9,0);
analogWrite(10,255);
  switchas = digitalRead(switchA);
  if(switchas != switchals){
    if(digitalRead(switchB) != switchas){
      if (millisStarted == False){
        PrevTime = millis();
        millisStarted = True;
      }
      else{
        CurrTime = millis();
        TimeDiff = CurrTime - PrevTime; 
        speed = 680 / TimeDiff;
        millisStarted = False;
      }
      Rcounter++;
    }
    else{
      if (millisStarted == False){
        PrevTime = millis();
        millisStarted = True;
      }
      else{
        CurrTime = millis();
        TimeDiff = CurrTime - PrevTime;
        speed = 680/ TimeDiff;
        millisStarted = False;
      }
      Lcounter++;
      }
      
Serial.print("Speed: ");
    Serial.println(speed);

/*  

    Serial.print("Speed: ");
    Serial.println(speed);


  }

  switchals = switchas;
  */
 /* 
  output = pid.compute(avg_speed/10);    
  analogWrite(5,output);
  analogWrite(6,0);
  Serial.println(output);
  */

  }
}

