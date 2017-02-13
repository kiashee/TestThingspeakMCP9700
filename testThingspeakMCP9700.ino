#include <SPI.h>
#include <Ethernet.h>
#include <stdlib.h>     // required for dtostrf()

#include "ThingSpeak.h"

//fill this up with your own channel number and WriteAPIkey. 
//WriteAPI key is automatically generated when creating a channel in Thingspeak.
unsigned long myChannelNumber = 226192;
const char * myWriteAPIKey = "XXXXXX4R4HEXXXXX";

char temp_buffer[10]; // char field

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

EthernetClient client;

const int chipSelect = 27; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ethernet.begin(mac);
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
  
  ThingSpeak.begin(client);
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature = 0.0;   // stores the calculated temperature
  int sample;                // counts through ADC samples
  float ten_samples = 0.0;   // stores sum of 10 samples
  
  // take 10 samples from the MCP9700
  for (sample = 0; sample < 10; sample++) {
      // convert A0 value to temperature
      temperature = ((float)analogRead(A0) * 5.0 / 1024.0) - 0.5;
      temperature = temperature / 0.01;
      // sample every 0.1 seconds
      delay(100);
      // sum of all samples
      ten_samples = ten_samples + temperature;
  }
  // get the average value of 10 temperatures
    float TemperatureValue = ten_samples / 10.0;
    
  Serial.print("  Temperature = ");
  Serial.print(TemperatureValue);
  Serial.println(" C");
  

  dtostrf(TemperatureValue, 2, 2, temp_buffer);
  ThingSpeak.writeField(myChannelNumber, (unsigned int)1, String(temp_buffer), myWriteAPIKey);
  //add delay of 19 seconds to complete at least 20secs. Free Thingspeak can only be updated every 15 secs
  delay(19000);     
}

