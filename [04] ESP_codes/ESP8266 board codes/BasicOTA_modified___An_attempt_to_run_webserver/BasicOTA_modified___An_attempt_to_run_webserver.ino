#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include  <ESP8266WebServer.h> //Webserver capability
#include "WiFi_credentials.h"  //Custom header file having WiFi credentials. 
#include "webpageCode.h"


#ifndef STASSID
#define STASSID mySSID
#define STAPSK myPASSWORD
#endif

const char* ssid = "HEATWAVE";
const char* password = "GRANDPABBIE";
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


ESP8266WebServer server(80);

//Functionality for our code
#define ledPin D0
unsigned long preMillis = 0; 
const long interval1 = 700; 
const long interval2 = 100; 
int ledState = HIGH; 
//Objective: The led will glow in the pattern 700-700-700-200-200-200 //these are the delays between two successive blinks. 
int switchings = 0; //The number of times we've switched the ledState . switchings/2 = number of blinks. 

void webpage()
{
  server.send(200, "text/html", webpageCode); 
}


void setup() {
   lcd.begin(16,2);
  pinMode(LED_BUILTIN, OUTPUT); 
                        Serial.begin(115200);
                        Serial.println("Booting");
                        lcd.setCursor(0,0); 
                        lcd.print("Booting"); 
                        delay(500); //For showing the text
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(1000);
    ESP.restart();
  }
                       lcd.setCursor(0, 0); 
                       lcd.print("WiFi connected"); 
                       delay(500); 
                       lcd.clear(); 
                       lcd.setCursor(0,0); 
                       lcd.print("Got IP: "); 
                       lcd.setCursor(0,1); 
                       lcd.print(WiFi.localIP());
                       delay(2000);
                       lcd.clear(); 

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
   //ArduinoOTA.setHostname("ESP8266_1");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


server.on("/", webpage); 
server.begin(); 

  

  server.begin(); 
  Serial.println("HTTP server started"); 
  lcd.home();  
  lcd.print("Server started"); 
  delay(1000);
  lcd.clear();  
 
  lcd.setCursor(0,0); 
  lcd.print("setup done"); 
  delay(1000); 
}

long loopcount = 0; 
short tenLoop = 0; 


void loop() {
  ArduinoOTA.handle();
  server.handleClient(); 

  if(switchings < 6)
  {
  if(millis() - preMillis >= interval1)
  {
    preMillis = millis(); 
    ledState = not(ledState); 
    digitalWrite(LED_BUILTIN, ledState); 
    switchings++; 
    
  }
  }
  else if(switchings < 12)
  {
    if(millis() - preMillis >= interval2)
    {
      preMillis = millis(); 
      ledState = not(ledState); 
      digitalWrite(LED_BUILTIN, ledState); 
      switchings++; 
    }
  }
  else 
  {
    switchings = 0; 
  }
  lcd.setCursor(0,0); 
  lcd.print("#loop 100x"); 
  tenLoop++; 
  if(tenLoop==100)
  {
    tenLoop = 0; 
    loopcount++; 
    if(loopcount%10==0)
    {
      lcd.setCursor(0,1); 
      lcd.print("                "); 
     
    }
  }
   lcd.setCursor(11, 0); 
   lcd.print(loopcount); 
   lcd.setCursor(0,1); 
   lcd.print(WiFi.localIP());
}
