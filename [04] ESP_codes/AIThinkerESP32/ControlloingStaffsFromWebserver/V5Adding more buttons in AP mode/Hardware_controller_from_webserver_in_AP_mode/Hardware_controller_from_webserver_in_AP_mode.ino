//Jump to VersionNote.h tab to know the preface and background. 


#include <ESP8266WiFi.h>
#include "HTML_code.h"

#ifndef APSSID
#define APSSID "ESP8266 board 1"
#define APPSK "PERSEVERANCEisthekey"
#endif

//Credentials for WiFi network
const char* ssid = APSSID;
const char* password = APPSK;

#define wtd 0 
// Wtd = Want to Debug . Whether we want to get other infos 
// on the serial monitor except the commands
//for multifunctional robot car.  

                       

//Set web server port number to 80
WiFiServer server(80); 

//Variable to store the HTTP request
String Header; 

//Auxiliary variables to store the current output state. 
String output5State = "off"; 
String output4State = "off"; 

//Assign output variables to GPIO pins
const int output5 = 2; 
const int output4 = 4; 

#define FBLRspeed ":200." //Forward, backward, left, right speed. 
String command = ""; //This string will contain the final command 
// of the format "x:y.: after concatenating the command type and 
//command value FBLRspeed

void setup()
{
   delay(1000);
  Serial.begin(9600);
  if(wtd)
  {
  Serial.println();
  Serial.print("Configuring access point...");
  }

  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  
  
  if(wtd)
  { 
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println(WiFi.localIP()); 
  }
  server.begin(); 
  
}


void loop()
{
      WiFiClient client = server.available();   // Listen for incoming clients

      if(client)                                // If a new client connects. 
      {                                        // print a message out in the serial port.
            client.println(webpageCode);       //This part has been moved here for experimental purpose. 
            if(wtd)
            {
            Serial.println("New Client."); 
            }  
            String currentLine = "";            // make a string to hold incoming data from the client
            
            while(client.connected())           // loop while the client is connected
            {
                if(client.available())          // if there's bytes to read from the client, 
                {
                    char c = client.read();     //read a byte, then
                   if(wtd)
                   {
                   Serial.write(c);          //print it out the Serial monitor
                   }
                    Header+=c;                  //appending the character at the end of header
                    if(c == '\n')               // if the byte is a newline character    
                    {                          
                          // if the current line is blank, you got two newline 
                          // in a row, that's the end of the client HTTP request, so send a response: 
                          if(currentLine.length() == 0)
                          {
                              //HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                              //and a content-type so the client knows what's coming, then a blank line: 
                              client.println("HTTP/1.1 200 OK"); 
                              client.println("Content-type: text/html"); 
                              client.println("Connection: close"); 
                              client.println(); 

                              //turns the GPIOs on and off
                              //For example, if you’ve pressed the GPIO 5 ON button, the URL changes to
                              //the ESP IP address followed by /5/ON, and we receive that information on
                              //the HTTP header. So, we can check if the header contains the expression GET /5/on.
                              //MainString.indexOf("targetString") The String object indexOf() method gives you 
                              //the ability to search for the first instance of a particular character value in a String.
                              
                                if(Header.indexOf("forward") >= 0)
                                {
                                  command = "f" + FBLRspeed; 
                                  Serial.print(command); 
                                  digitalWrite(output5, HIGH); 
                                }
                                else if (Header.indexOf("backward") >= 0)
                                {
                                  Serial.print("b:120."); 
                                  digitalWrite(output5, LOW); 
                                }
                                else if(Header.indexOf("right") >=0)
                                {
                                  Serial.print("r:120."); 
                                  output4State = "on"; 
                                  analogWrite(output5, 100); 
                                }
                                else if(Header.indexOf("left") >=0)
                                {
                                  Serial.println("l:120."); 
                                  output4State = "off"; 
                                  analogWrite(output5, 200); 
                                }

                                //  client.println(webpageCode); //instead of printing each time of request, 
                                                                  //we've printed the whole webpage once, when the
                                                                  //client connects. 

                                // The HTTP response ends with another blank line
                                client.println();
                                // Break out of the while loop
                                break;
                          }
                          else  //if you got a newline, then clear currentline
                          {
                            currentLine = ""; 
                          }
                    }
                    else if(c!='\r')  //if you got anything else but a carriage return character,  
                    {                 //add it to the end of the currentline
                      currentLine+=c; 
                    }
                    
                }
            }
      //Clear the header variable
      Header = ""; 
      // Close the connection
      client.stop(); 
      if(wtd)
      {
      Serial.println("Client disconnected."); 
      Serial.print(""); 
      }
      }
}
