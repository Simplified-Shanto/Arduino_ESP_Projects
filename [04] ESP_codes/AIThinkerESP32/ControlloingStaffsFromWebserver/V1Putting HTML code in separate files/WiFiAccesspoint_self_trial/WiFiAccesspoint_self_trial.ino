/*   
 *   
 * Version:  V1 10-24-2023 Putting HTML code in separate files
 * Modification starts: 10/24/2023. 
 * Modifications ends:  10/24/2023. 
 * Targeted board: Node MCU ESP8266
 * Modified by: Md. Nayeem Islam Shanto (islamshafiul283@gmail.com)
 *
 *How to use? 
 *1. Upload code to ESP8266 board. 
 *2. Connect to the network with the same name as APSSID
 *    with the password. 
 *3. Enter the IP address from the Serial Monitor to the browser 
 *4. Interact/View the website
 * 
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "webpageCode.h"

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK "thereisnospoon"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/


void webpage()
{
  server.send(200, "text/html", webpageCode); 
}
void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", webpage);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
