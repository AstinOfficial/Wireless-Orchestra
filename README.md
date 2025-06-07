
# 🎶 Wireless Orchestra

A unique musical interface using motion! This project transforms your hand movements into orchestral music notes using an MPU-6050 motion sensor and a NodeMCU ESP8266 board. The system communicates with a PC-based client using TCP in a client-server architecture.

---

## 📌 Project Overview

The **Wireless Orchestra** allows users to act as a conductor of an orchestra using a motion-controlled wand. The wand is created using an **MPU-6050 Triple-Axis Accelerometer & Gyroscope Module** connected to an **ESP8266 (NodeMCU)** board. 

The device captures real-time motion data (X, Y, Z axis) and maps it to corresponding orchestral musical notes. These notes are then transmitted over Wi-Fi using **TCP** to a PC client, which plays or visualizes the music.

---

## 📁 Note for Developers

📌 **This repository contains only the server-side code (ESP8266) implemented using ESP-IDF in PlatformIO.**  
Any developer can easily build a custom PC client application by referring to the structure and output format of the server code.

---

## 🛠️ Hardware Used

- **NodeMCU ESP8266** – Wi-Fi enabled microcontroller
- **MPU-6050** – Triple-Axis Accelerometer & Gyroscope
- **PC** – Running a client application to receive and process the musical notes

---

## 📡 Communication

The project uses **TCP sockets** for communication:

- **Server**: Implemented on the ESP8266 using **ESP-IDF** (in a PlatformIO environment)
- **Client**: Runs on a PC, listens for incoming note data and handles musical playback or visualization (not included in this repo)

---

## ⚙️ Getting Started

### 🔧 ESP8266 Setup (Server Side)
1. Connect your NodeMCU ESP8266 via USB.
2. Flash the code:
   ```bash
   pio run --target upload
   ```
3. Monitor the serial output:
   ```bash
   pio device monitor
   ```

---

## 🎵 How It Works

- The MPU-6050 sensor detects movement and orientation in 3D space.
- ESP8266 interprets this data and maps specific gestures or directions to musical notes.
- These notes are sent over Wi-Fi using TCP to a PC client.
- The PC client plays or visualizes the received notes as orchestral music.

---


## 🙌 Contribution
If you found this useful or improved it further, feel free to fork, clone, and submit a pull request.
```bash
https://github.com/AstinOfficial/Wireless-Orchestra.git
```
---
## 🙋‍♂️ Author
Astin Biju <br>
Feel free to connect on <a href="https://www.linkedin.com/in/astin-biju/">LinkedIn</a> or message me for questions or collaboration.


