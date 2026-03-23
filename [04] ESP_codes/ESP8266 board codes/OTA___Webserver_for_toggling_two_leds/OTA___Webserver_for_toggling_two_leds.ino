#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include  <ESP8266WebServer.h> //Webserver capability
#include "WiFi_credentials.h"  //Custom header file having WiFi credentials. 



#ifndef STASSID
#define STASSID mySSID
#define STAPSK myPASSWORD
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


ESP8266WebServer server(80);
uint8_t LED1pin = D7;
bool LED1status = LOW;

uint8_t LED2pin = D6;
bool LED2status = LOW;  


//Functionality for our code
#define ledPin D0
unsigned long preMillis = 0; 
const long interval1 = 700; 
const long interval2 = 100; 
int ledState = HIGH; 
//Objective: The led will glow in the pattern 700-700-700-200-200-200 //these are the delays between two successive blinks. 
int switchings = 0; //The number of times we've switched the ledState . switchings/2 = number of blinks. 


void setup() {
   lcd.begin(16,2);
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT); 
  
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
                       lcd.cursor(); 
                       lcd.blink(); 
                       delay(2000);
                       lcd.clear(); 

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

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


  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.onNotFound(handle_NotFound); 



  

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

   if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW); }

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
  lcd.print("void loop()"); 
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
   lcd.setCursor(0,1); 
      lcd.print(loopcount); 
}


  void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
}


void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status)); 
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status)); 
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("GPIO6 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
    ptr +="<h3>Using Station(STA) Mode</h3>\n";
    //ptr +="<h4>The OTA capability has been added to this sketch</h4>\n"; 
  
   if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
