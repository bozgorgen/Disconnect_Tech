int clk=0;
int dt=0;

int counter_right=0;
int counter_left=0;
int dt_temp=0;
int clk_temp=0;
int turns_r=0;
int turns_l=0;
//sağa çevirince data önce atıyor
void setup() {
  // put your setup code here, to run once:
  //DT pin7 CLK pin 6
pinMode(7,INPUT);
pinMode(6,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
dt_temp=dt;
clk_temp=clk;
dt=digitalRead(7);
clk=digitalRead(6);

if(dt>clk){
//right turn
  if(dt_temp!=dt){
    counter_right+=1;
  }
  if(counter_right==15){
    turns_r+=1;
  counter_right=0;
  }
}

else if(clk>dt){
  //left turn
  if(clk_temp!=clk){
    counter_left+=1;
  }
  if(counter_left==15){
    turns_l+=1;
  counter_left=0;
  }
}
//Serial.print("Right turns");/
Serial.println(turns_r);
///Serial.print(",");
//Serial.println(counter_right);
Serial.print(",");
//Serial.print("Left turns");
Serial.println(turns_l);
//Serial.println(dt);
//Serial.print(",");
//Serial.println(clk);
//Serial.print(",");
//Serial.println(counter_left);
}
