#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SS_PIN 5
#define RST_PIN 2
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

MFRC522 rfid(SS_PIN, RST_PIN);
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

String authorizedUID = "b3 53 59 28"; // Replace with your RFID card UID

void setup() {
  Serial.begin(115200);
  
  // Initialize RFID
  SPI.begin();
  rfid.PCD_Init();

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("RFID Access");
  display.display();
  
  Serial.println("Place your RFID card near the reader...");
}

byte identificationStatus = 0; 

void loop() {
  
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  String readUID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    readUID += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    readUID += String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) readUID += " ";
  }
  
  Serial.print("Card UID: ");
  Serial.println(readUID);

  display.clearDisplay();
  display.setCursor(0, 0);
  if (readUID.equalsIgnoreCase(authorizedUID)) {
    display.println("Access granted");
    Serial.println("Access granted");
  } else {
    display.println("Access denied");
    Serial.println("Access denied");
  }
  display.display();

  delay(2000);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
