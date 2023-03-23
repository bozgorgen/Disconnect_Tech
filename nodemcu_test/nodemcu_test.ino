
//ENCODER 
#define RIGHT_CH_1 5
#define RIGHT_CH_2 6


bool right_channel1_prev=0;
bool right_channel2_prev=0;
bool right_channel1_curr=0;
bool right_channel2_curr=0;
bool right_rotation; //CW=1, CCW=0
long right_counter=0;
bool is_right_turning=0;

bool left_channel1_prev=0;
bool left_channel2_prev=0;
bool left_channel1_curr=0;
bool left_channel2_curr=0;
bool left_rotation; //CW=1, CCW=0
long left_counter=0;
bool is_left_turning=0;
//ENCODER

//VELOCITY MEASUREMENT
long currT;
long prevT=0;
float deltaT;
float velocity_right;
float velocity_right_prev=0;
float velocity_right_filt=0;
float velocity_left;
float velocity_left_prev=0;
float velocity_left_filt=0;
long right_counter_prev=0;
long left_counter_prev=0;
//VELOCITY MEASUREMENT

//CONTROLLER
float set_velocity_right = 0;
float set_velocity_left = 0;
float kp=10;
float ki=0.05;
float error_left;
float error_left_sum;
float error_right;
float error_right_sum;
float actuator_left;
float actuator_left_dir;
float actuator_right;
float actuator_right_dir;
//CONTROLLER


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //ENCODER
  pinMode(RIGHT_CH_1,INPUT);
  pinMode(RIGHT_CH_2,INPUT);
  right_channel1_prev=0;
  right_channel2_prev=0;


  //ENCODER

//MOTOR ACTUATOR

}


void loop() {
{
  //ENCODER
  //right starts
  right_channel1_curr=digitalRead(RIGHT_CH_1);
  right_channel2_curr=digitalRead(RIGHT_CH_2);

  //turning CW
  if(!right_channel1_prev&&!right_channel2_prev&&!right_channel1_curr&&right_channel2_curr)
  {
    right_rotation=1;
    is_right_turning=1;
  }
  else if(!right_channel1_prev&&right_channel2_prev&&right_channel1_curr&&right_channel2_curr)
  {
    right_rotation=1;
    is_right_turning=1;  
  }
  else if(right_channel1_prev&&!right_channel2_prev&&!right_channel1_curr&&!right_channel2_curr)
  {
    right_rotation=1;
    is_right_turning=1;  
  }
  else if(right_channel1_prev&&right_channel2_prev&&right_channel1_curr&&!right_channel2_curr)
  {
    right_rotation=1;
    is_right_turning=1;  
  }

  //Turning CCW
  else if(!right_channel1_prev&&!right_channel2_prev&&right_channel1_curr&&!right_channel2_curr)
  {
    right_rotation=0;
    is_right_turning=1;
  }
  else if(!right_channel1_prev&&right_channel2_prev&&!right_channel1_curr&&!right_channel2_curr)
  {
    right_rotation=0;
    is_right_turning=1;  
  }
  else if(right_channel1_prev&&!right_channel2_prev&&right_channel1_curr&&right_channel2_curr)
  {
    right_rotation=0;
    is_right_turning=1;  
  }
  else if(right_channel1_prev&&right_channel2_prev&&!right_channel1_curr&&right_channel2_curr)
  {
    right_rotation=0;
    is_right_turning=1;  
  }
  else
    is_right_turning=0;

  //CW is positive
  if(right_rotation)
    right_counter+=is_right_turning;
  else
    right_counter-=is_right_turning;

  right_channel1_prev=right_channel1_curr;
  right_channel2_prev=right_channel2_curr;
  //right ends

}
//VELOCITY MEASUREMENT
currT = micros();
deltaT = ((float) (currT-prevT))/1.0e6;
velocity_right = (right_counter - right_counter_prev)/deltaT;
right_counter_prev=right_counter;


prevT = currT;

//conversion to cm/s (circumference is 21.67cm)
velocity_right=velocity_right/3000.0*21.67*10;


  
velocity_right_filt= 0.9691*velocity_right_filt + 0.01547*velocity_right + 0.01547*velocity_right_prev;
velocity_right_prev=velocity_right;
//VELOCITY MEASUREMENT

//CONTROLLER
set_velocity_right=30;
set_velocity_left=30;

error_right=set_velocity_right-velocity_right_filt;
if(actuator_right!=255)
  error_right_sum+=error_right;

error_left=set_velocity_left-velocity_left_filt;
if(actuator_left!=255)
  error_left_sum+=error_left;

actuator_right = kp*error_right + ki*error_right_sum;

actuator_left = kp*error_left + ki*error_left_sum;

if(actuator_right < 0)
{
  actuator_right_dir=1;
  actuator_right*=-1;      
}
else
{
  actuator_right_dir=0;
}

if(actuator_right>255)
{
  actuator_right=255;
}

if(actuator_left < 0)
{
  actuator_left_dir=1;
  actuator_left*=-1;      
}
else
{
  actuator_left_dir=0;
}

if(actuator_left>255)
{
  actuator_left=255;
}





Serial.print(velocity_right_filt);
Serial.println();
}
