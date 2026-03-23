# Arduino_ESP_Projects

Arduino_ESP_Projects is a personal archive of embedded systems, robotics, sensor, display, and creative-coding experiments. It combines Arduino Uno and Nano sketches, ESP32 and ESP8266 projects, Processing sketches, and PictoBlox files in one workspace.

This repository is closer to a running lab notebook than a polished library. Many folders are date-stamped snapshots, versioned attempts, tutorial adaptations, hardware tests, and working prototypes saved as the projects evolved.

## What Is In Here

- 199 Arduino/ESP `.ino` sketches
- 91 Processing `.pde` sketches
- 7 PictoBlox `.sb3` projects
- Supporting headers, HTML/CSS/JS files, images, audio assets, archives, and a few Windows metadata files

Common themes across the repo include:

- Servo, motor, and stepper control
- Line followers, rovers, robotic arms, and WRO-style vehicle experiments
- Sonar, radar, and distance-sensing projects
- OLED dashboards, weather/sensor displays, and environmental monitoring
- DS3231 RTC clock projects with rotary encoders and menu systems
- ESP32-CAM streaming, photo capture, and timelapse experiments
- Wi-Fi web servers, access points, and OTA update attempts
- RFID access-control and smart-home style menu interfaces
- Processing games, physics demos, UI widgets, and "Nature of Code" exercises

## Folder Guide

### `[01] Arduino Uno code`

Mostly Arduino Uno sketches and companion experiments. This section includes projects such as a mini CNC/plotter, line followers, radar/sonar visualizations, keypad and piano builds, SD-card servo recording, light tracking, blind-stick prototypes, sensor-combination tests, and a small ROS serial communication example.

### `[02] Arduino Nano Codes`

Arduino Nano projects focused on compact robot and sensor builds. Examples include WRO vehicle steering code, weather-station and OLED sensor displays, servo testers, a fan speed controller, RFID/OLED sensor experiments, voltage/current testing, and extension-board demo sketches.

### `[03] Arduino Mega Codes`

This folder exists as a placeholder but is currently empty.

### `[04] ESP_codes`

The largest section of the repo. It includes:

- ESP32 clock and RTC projects using OLED displays, DS3231 modules, and rotary encoders
- Robodemy smart-home experiments with menu navigation, LEDs, relays, sensors, and RFID
- AI Thinker ESP32-CAM examples for camera streaming, photo storage, and timelapse
- ESP8266 web server, access point, OTA, OLED, EEPROM, and sensor dashboard experiments
- A mix of custom code and tutorial-derived reference projects

### `[05] Processing-PDE`

Processing sketches used for visualization, learning, and companion desktop interfaces. This folder contains simple games, animations, slider/toggle UI components, image demos, drawing/layout sketches, and many physics-style exercises inspired by The Nature of Code.

### `[09] Pictoblox codes`

PictoBlox projects related to rover control, object detection, face detection, motion sensing, and ESP32 command interpretation via PWM.

## What This Repo Is

This repo is best understood as a broad personal project collection covering:

- Embedded firmware experiments
- Robotics and automation prototypes
- Sensor and display demos
- Desktop visualizations and learning sketches
- Saved reference material from external tutorials and example projects

It is not organized as a single application, library, or finished product line.

## Working With The Projects

- Open each sketch in its own folder with the Arduino IDE, Processing IDE, or PictoBlox as appropriate.
- Check the target board before uploading. The repo mixes Arduino Uno, Arduino Nano, ESP32, ESP8266, and ESP32-CAM projects.
- Install the libraries required by each sketch's `#include` list. Common ones in this repo include `Wire`, `Adafruit_SSD1306`, `Adafruit_GFX`, `Servo`, `Adafruit_BMP280`, `DHT`, `MQUnifiedsensor`, `DS3231`, `RTClib`, `ESP8266WiFi`, `ArduinoOTA`, and ESP32 camera libraries.
- Review pin mappings and hardware notes inside each sketch before wiring.
- Some networked sketches contain local Wi-Fi credentials or expect a local `WiFi_credentials.h` file. Clean those up before reuse or sharing.

## Notes

- Several folders contain multiple iterations of the same idea saved by date or version number.
- Some code is clearly marked as under development, buggy, experimental, or copied from tutorials for learning/reference purposes.
- The repo also includes assets and artifacts such as images, audio, ZIP archives, a compiled `.bin` file, `desktop.ini`, and a Windows shortcut.
