
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <WebServer.h>
#endif

#include <ElegantOTA.h>

#include"WiFi_credentials.h"
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

//Functionality for our code
#define ledPin D0
unsigned long preMillis = 0; 
const long interval1 = 700; 
const long interval2 = 100; 
int ledState = HIGH; 
//Objective: The led will glow in the pattern 700-700-700-200-200-200 //these are the delays between two successive blinks. 
int switchings = 0; //The number of times we've switched the ledState . switchings/2 = number of blinks. 


const char* ssid = mySSID;
const char* password = myPASSWORD;


#if defined(ESP8266)
  ESP8266WebServer server(80);
#elif defined(ESP32)
  WebServer server(80);
#endif


void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/plain", "Hi! I am ESP8266.");
  });

  ElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
  lcd.begin(16,2);
  lcd.setCursor(0,0); 
  lcd.print("setup done"); 
  delay(500); 
}

void loop(void) {
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
  lcd.print("void loop()"); 
}
