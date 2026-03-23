/*
  WiFi Web Server LED Blink

  A simple web server that lets you blink an LED via the web. 
  This sketch will print the IP address of your WiFi Shield (once 
  connected to the Serial monitor, From there you can open that address 
  in a web browser to turn on an doff the LED on pin 5. 

  If the IP address of your shield is yourAddress: 
  http://yourAddress/H turns the LED on 
  http://yourAddress/L turns the LED off

  This code is written for a newtwork using wPA encryption for 
  WEP or WPA, change Wifi.begin() call accordingly. 

  Circuit: 
  *WiFi shield attached
  *LED attached to pin 5
  *
   
 */

 #include<WiFi.h>
 #include<WiFiClient.h> 
 #include<WiFiAP.h> 
  

 const char* ssid = "Shanto's ESP module"; 
 const char* password = "frozen Heart"; 

 #define ledPin 5


 WiFiServer server(80); 

 void setup()
 {
  Serial.begin(9600); 
  pinMode(ledPin, OUTPUT);   //set the LED pin mode

  delay(10); 

  //We start by connecting to a WiFi network

  Serial.println(); 
  Serial.println(); 
  Serial.println("Connecting to "); 
  Serial.println(ssid); 

  WiFi.begin(ssid, password); 

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500); 
    Serial.print("."); 
  }

  Serial.println(""); 
  Serial.println("Wifi connected."); 
  Serial.println("IP address: "); 
  

  
 }
 
