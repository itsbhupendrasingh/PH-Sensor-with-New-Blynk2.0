/*
 * you need to select the board as NodeMCU 1.0(ESP12E Module). for this syou can watch our other tutorials in our channel. 
 * you can also take the help from this link. and also select the COM port to uplaod the program. 
 */
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLA-EAjMzt"
#define BLYNK_DEVICE_NAME "PH Value of Water "

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define USE_NODE_MCU_BOARD

#include "BlynkEdgent.h"

#define SensorPin A0          //pH meter Analog output to Arduino Analog Input 0
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;


int f;  // for float value to string converstion
float val; // also works with double. 
char buff2[10];
String valueString = "";
String Value = ""; 

void PH_Value()
{
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
  avgValue+=buf[i];
  float phValue=(float)avgValue*3.3/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  
  Value =  dtostrf(phValue, 4, 2, buff2);  //4 is mininum width, 6 is precision
  valueString = valueString + Value +","; 
  Serial.print(Value);
  Serial.print("    ");
  Serial.println(valueString);
  valueString = "";
  delay(1000);
  Blynk.virtualWrite(V0, Value);
}

void setup()
{
  Serial.begin(9600);
  BlynkEdgent.begin();
  delay(2000); 
}

void loop() 
{
  BlynkEdgent.run();
  PH_Value();
}
