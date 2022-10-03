/*
 * This program is property of SME Dehradun. for any query related to this program, 
 * contact us at www.smedehradn.com
 * if your want any solution related for any IoT Customized Boards and Sensor, 
 * then contact to www.nuttyengineer.com 
 */
// Replace/ Fill-in information from your Blynk Template here

#define BLYNK_TEMPLATE_ID "TMPL4yDpPzsU"
#define BLYNK_DEVICE_NAME "Smart Dustbin"

#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#include "BlynkEdgent.h"

#define SensorPin 13          //pH meter Analog output to Arduino Analog Input 
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
  Serial.print(Value);
  valueString = "";
  delay(1000);
  Blynk.virtualWrite(V0, 7.06);
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
