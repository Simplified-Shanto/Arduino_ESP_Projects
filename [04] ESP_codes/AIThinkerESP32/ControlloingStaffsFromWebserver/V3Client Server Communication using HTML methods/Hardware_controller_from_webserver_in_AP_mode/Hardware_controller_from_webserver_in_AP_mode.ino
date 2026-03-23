/*
 *   
 * Version: V3 10-25-2023 Client Server Communication using HTML methods
 * Modification starts: 10/24/2023. 
 * Modifications ends:  
 * Targeted board: Node MCU ESP8266
 * Modified by: Md. Nayeem Islam Shanto (islamshafiul283@gmail.com)
 *
 *How to use? 
 *1. Upload code to ESP8266 board. 
 *2. Enter the IP address from the Serial Monitor to the browser 
 *3. Interact/View the website
 *  
 * 
 * This code was initially adapted from https://randomnerdtutorials.com/esp8266-web-server/
 * Later modified to know how the web-communication works
 * between the webpage and the ESP8266. In Version 3, we did the same task 
 * keeping the NodeMCU in STATION mode, but we are doing here the task 
 * in STATION mode. If you wish to see the html code in a separate 
 * header, check Version 2. 
 * 
 * 
 */

#include <ESP8266WiFi.h>

#ifndef APSSID
#define APSSID "ESP8266 board 1"
#define APPSK "PERSEVERANCEisthekey"
#endif

//Credentials for WiFi network
const char* ssid = APSSID;
const char* password = APPSK;

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

void setup()
{
   delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  Serial.println(WiFi.localIP()); 
  server.begin(); 
  
}


void loop()
{
      WiFiClient client = server.available();   // Listen for incoming clients

      if(client)                                // If a new client connects. 
      {                                         // print a message out in the serial port. 
            Serial.println("New Client.");   
            String currentLine = "";            // make a string to hold incoming data from the client
            
            while(client.connected())           // loop while the client is connected
            {
                if(client.available())          // if there's bytes to read from the client, 
                {
                    char c = client.read();     //read a byte, then
                   Serial.write(c);          //print it out the Serial monitor
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
                              
                                if(Header.indexOf("GET /5/on") >= 0)
                                {
                                  Serial.println("GPIO 5 on"); 
                                  output5State = "on"; 
                                  digitalWrite(output5, HIGH); 
                                }
                                else if (Header.indexOf("GET /5/off") >= 0)
                                {
                                  Serial.println("GPIO 5 off"); 
                                  output5State = "off"; 
                                  digitalWrite(output5, LOW); 
                                }
                                else if(Header.indexOf("GET /4/on") >=0)
                                {
                                  Serial.println("GPIO 4 on"); 
                                  output4State = "on"; 
                                 // digitalWrite(output4, HIGH);
                                 analogWrite(output5, 100); 
                                }
                                else if(Header.indexOf("GET /4/off") >=0)
                                {
                                  Serial.println("GPIO 4 off"); 
                                  output4State = "off"; 
                                 // digitalWrite(output4, LOW); 
                                 analogWrite(output5, 200); 
                                }

                                                     // Display the HTML web page
                                client.println("<!DOCTYPE html><html>");
                                client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                                client.println("<link rel=\"icon\" href=\"data:,\">");
                                // CSS to style the on/off buttons 
                                // Feel free to change the background-color and font-size attributes to fit your preferences
                                client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                                client.println(".button { background-color: #191B6A; border: none; color: white; padding: 16px 40px;");
                                client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                                client.println(".button2 {background-color: #77878A;}</style></head>");
                                
                                // Web Page Heading
                                client.println("<body><h1>ESP8266 Web Server</h1>");
                                
                                // Display current state, and ON/OFF buttons for GPIO 5  
                                client.println("<p>GPIO 5 - State " + output5State + "</p>");
                                // If the output5State is off, it displays the ON button       
                                if (output5State=="off") 
                                {
                                  client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
                                } 
                                else 
                                {
                                  client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
                                } 
                                   
                                // Display current state, and ON/OFF buttons for GPIO 4  
                                client.println("<p>GPIO 4 - State " + output4State + "</p>");
                                // If the output4State is off, it displays the ON button       
                                if (output4State=="off") 
                                {
                                  client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
                                } 
                                else
                                {
                                  client.println("<p>    <a href=\"/4/off\">   <button class=\"button button2\">    OFF      </button>    </a>     </p>");
                                }
                                client.println("</body></html>");
                                
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
      Serial.println("Client disconnected."); 
      Serial.print(""); 
      }
}
