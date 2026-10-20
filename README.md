# Smart Parking System Using Arduino

## 📌 Project Overview
The Smart Parking System is an Arduino-based project that automates vehicle entry and exit using IR sensors and a servo motor-controlled gate. It helps manage parking capacity and monitor available parking slots.

## ✨ Features
- Automatic vehicle detection using IR sensors.
- Servo motor-based automatic gate control.
- Parking capacity of up to four vehicles.
- Automatic entry and exit monitoring.
- LCD-free design.

## 🛠️ Hardware Components
- Arduino board
- 2 IR sensors
- Servo motor
- Jumper wires
- Breadboard
- USB cable and suitable power supply

## 🔌 Pin Connections

| Component | Arduino Pin |
|---|---|
| Entry IR Sensor | D2 |
| Exit IR Sensor | D3 |
| Servo Motor Signal | D9 |

## ⚙️ Working Principle
1. The entry IR sensor detects an incoming vehicle.
2. The Arduino checks whether parking space is available.
3. If space is available, the servo motor opens the gate.
4. The exit IR sensor detects a vehicle leaving the parking area.
5. The available parking count is updated.

## 💻 Software Used
- Arduino IDE
- Embedded C/C++

## 🚀 Future Improvements
- Live web dashboard for parking availability.
- IoT-based monitoring.
- Real-time parking status updates.

## 👩‍💻 Project Information
**Project:** Smart Parking System Using Arduino  
**Domain:** Embedded Systems and Automation  
**Author:** Gayatri Patil
