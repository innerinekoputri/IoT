#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

const char* ssid = "kucingsanto"; //nama hospot
const char* password = "kucingkuning2022"; //Password hospot atau wifi
int val;
int sensorApi = A0; 
WiFiClient client;

unsigned long myChannelNumber = 2050017;
const char * myWriteAPIKey = "5U2K0QBJP6TRNL7O"; 

void setup()
{
 Serial.begin(9600);
 delay(10);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}

void loop()
{
  val = analogRead(sensorApi); 
  Serial.println("Nilai Api=  "); 
  Serial.println(val); 
  delay(10);
  ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey); //Update in ThingSpeak
}
