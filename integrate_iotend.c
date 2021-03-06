#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
const char ssid[] = "";  // your network SSID (name)
const char pass[] = "";   // your network password         
WiFiClient  client;

//---------Channel Details---------//
unsigned long counterChannelNumber = 1398193;            // Channel ID
const char * myCounterReadAPIKey = "L2SEQTDRF7RP5JM0"; // Read API Key
const int FieldNumber1 = 1;  // The field you wish to read



void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop()
{
  //Serial.print("Connecting to ");
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
  }
 

  //---------------- Channel 1 ----------------//
  long temp = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  int statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.print("Predicted value : ");
    Serial.println(temp);
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
  }
  delay(10000);
}
