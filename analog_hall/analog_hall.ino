#define rate 30
#define rate_double 30.0
int i,j;
 int data[rate];
int data_sum;
int ctr;
void setup() {
  // put your setup code here, to run once:
Serial.begin(500000);
i=0;
j=0;
data_sum=0;
ctr=0;
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);

 if(i%100==0)
  {
    
    ctr=0;
  } 

if(sensorValue<520)
{
  ctr++;
}


  Serial.print("Variable_1:");
  Serial.print(ctr);
  Serial.print(",");
  Serial.print("Variable_2:");
  Serial.println(sensorValue);
/*
data[i%rate]=sensorValue;
data_sum=0;
for(j=0;j<rate;j++)
{
  data_sum+=data[j];
}
//Serial.println(data_sum/rate_double);
*/
i++;
delay(5);
}
