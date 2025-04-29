# 🔥 Fire and Gas Detector System

An IoT-based hazard monitoring system built with an ESP32 microcontroller to detect fire and gas leaks. The system sends real-time alerts through the **Blynk IoT app** and provides on-site warnings using LEDs and a buzzer.

> Developed as a course project for **SWE 466 – Embedded Systems & IoT Lab** at **Metropolitan University, Sylhet**.

---

## 📌 Project Goals

- Monitor fire and gas levels in real time.
- Notify users remotely via Blynk mobile app.
- Activate local alarms using a buzzer and LED indicators.
- Deliver an affordable and expandable safety solution.

---

## 🛠️ Hardware Used

| Component         | Description                            |
|------------------|----------------------------------------|
| ESP32            | Wi-Fi-enabled microcontroller          |
| MQ2 Sensor       | Detects smoke, LPG, and methane gases  |
| Flame Sensor     | Detects infrared light from fire       |
| LEDs             | Red (Danger), Yellow (Warning), Green (Safe) |
| Buzzer           | Emits sound when fire/gas is detected  |
| Breadboard & Wires | Used for prototyping connections      |
| USB Cable/Battery| Power supply for ESP32                 |

---

## 🧠 Features

- 🔥 Dual Hazard Detection: Flame and gas.
- 📲 Real-Time Alerts: Notifications through Blynk IoT.
- 🔊 Visual + Audio Alerts: LEDs and buzzer for local warning.
- 📶 Wi-Fi Enabled: ESP32 handles cloud communication.

---

## 🧪 System Workflow

1. Sensors (MQ2 + Flame) monitor the environment.
2. Sensor readings are sent to the ESP32.
3. If a fire or high gas concentration is detected:
   - LEDs change to red or yellow.
   - The buzzer activates.
   - A mobile alert is pushed via the Blynk app.
4. If conditions are safe, the green LED remains on.

---

## 📲 Blynk Integration

| Virtual Pin | Function         |
|-------------|------------------|
| V1          | Smoke level (%)  |
| V2          | Flame status     |
| V3          | Alert toggle     |

- BlynkTimer is used for non-blocking operations.
- The app UI displays sensor status and triggers push alerts.

---

## 🧩 Circuit Pin Mapping

| Component        | ESP32 GPIO |
|------------------|------------|
| MQ2 Sensor       | GPIO 36 (Analog) |
| Flame Sensor     | GPIO 34 (Digital) |
| Red LED          | GPIO 25     |
| Green LED        | GPIO 26     |
| Yellow LED       | GPIO 27     |
| Buzzer           | GPIO 33     |
| Onboard LED      | GPIO 2      |

---

## 🧑‍💻 Team Contributions

- **Circuit Design** – Marjana Begum, Moumita Das Mou  
- **Flame Sensor Calibration** – Tahmid Samin  
- **Gas Sensor Tuning** – Tanvir Mahmud Ove  
- **Code & Blynk Integration** – Shafat Alam

---

## 📄 Full Report

📘 [Download Full Report (PDF)](link-to-pdf-report)

Includes:
- Objective & Team Info
- Development Procedure
- Problem-Solving Section
- Hardware List
- Final Notes

---

## 📎 How to Run

1. Clone this repository
2. Open the code in Arduino IDE
3. Install the **ESP32 board support** and **Blynk library**
4. Add your:
   - Wi-Fi credentials
   - Blynk Auth Token
5. Upload to ESP32 and open your Blynk mobile app

---

## 📜 License

This project is released for academic and non-commercial use under the **MIT License**.

---

## 👨‍🏫 Instructor

**Nawshad Ahmed Chowdhury**  
Head, Department of EEE  
Metropolitan University, Sylhet

---

## 🎓 Institution

**Metropolitan University, Sylhet**  
Department of B.Sc. in Software Engineering  
