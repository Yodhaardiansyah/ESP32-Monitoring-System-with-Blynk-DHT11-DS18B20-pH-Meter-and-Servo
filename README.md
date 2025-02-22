# **ESP32 Monitoring System with Blynk, DHT11, DS18B20, pH Meter, and Servo**  

### 🌟 **Introduction**  
This project is an **IoT-based environmental monitoring system** using an **ESP32**. It collects **temperature, humidity, and pH level data** and allows remote monitoring through **Blynk**. Additionally, it includes a **servo motor control** for automation.  

### 🔥 **Features**  
✅ **Temperature & Humidity Monitoring** with **DHT11**  
✅ **Water Temperature Measurement** using **DS18B20**  
✅ **pH Level Detection** for liquid solutions  
✅ **Remote Servo Motor Control** via **Blynk App**  
✅ **WiFi Connectivity** for real-time data updates  
✅ **User-friendly Serial Output** for debugging  

---

## ⚙️ **Hardware Requirements**  
To build this system, you need the following components:  

| Component        | Quantity | Description |
|-----------------|----------|-------------|
| ESP32           | 1        | Microcontroller with WiFi & Bluetooth |
| DHT11 Sensor    | 1        | Measures temperature & humidity |
| DS18B20 Sensor  | 1        | Waterproof temperature sensor |
| pH Meter Module | 1        | Measures pH level of liquids |
| Servo Motor (SG90/MG995) | 1 | Used for automation control |
| 10K Resistor    | 1        | Pull-up resistor for DS18B20 |
| Breadboard & Wires | - | For circuit connections |

---

## 📡 **Circuit Diagram**  
🛠 *Ensure you connect the sensors properly according to their datasheets!*  

### **Pin Configuration:**  

| Component        | ESP32 Pin |
|-----------------|----------|
| DHT11 Data Pin  | GPIO 13  |
| DS18B20 Data Pin | GPIO 14  |
| pH Meter Analog Output | GPIO 35 |
| Servo PWM Signal | GPIO 15 |

---

## 🛠 **Installation & Setup**  

### **1️⃣ Install Required Libraries**  
Before uploading the code, make sure you have these libraries installed in **Arduino IDE**:  

📌 **Install via Library Manager:**  
- **Blynk** (`Blynk` by Volodymyr Shymanskyy)  
- **DHT sensor library** (`DHT sensor library` by Adafruit)  
- **DallasTemperature** (`DallasTemperature` by Miles Burton)  
- **OneWire** (`OneWire` by Jim Studt, Paul Stoffregen)  
- **ESP32Servo** (`ESP32Servo` by John K. Bennett)  

### **2️⃣ Configure Blynk App**  
1. Create a **Blynk** account at [Blynk IoT](https://blynk.cloud/).  
2. Add a new device and **copy your BLYNK_AUTH_TOKEN**.  
3. Set up **Virtual Pins**:  
   - `V1` → Temperature (DHT11)  
   - `V2` → Humidity (DHT11)  
   - `V3` → Temperature (DS18B20)  
   - `V5` → pH Level  
   - `V4` → Servo Control  

4. Update **WiFi credentials & Blynk Token** in the code:  
   ```cpp
   #define BLYNK_AUTH_TOKEN "Your_Blynk_Token"
   char ssid[] = "Your_WiFi_SSID";
   char pass[] = "Your_WiFi_Password";
   ```
5. Upload the code and **start monitoring!** 📡📊

---

## 📌 **How It Works**  
1️⃣ **ESP32 connects to WiFi** and **Blynk Cloud**.  
2️⃣ **Sensors collect data** and **send updates to Blynk** every second.  
3️⃣ **Servo motor** can be remotely controlled from the **Blynk app**.  
4️⃣ **Serial Monitor** displays real-time sensor readings for debugging.  

---

## 🛠 **Troubleshooting**  
💡 **WiFi Not Connecting?**  
- Double-check **SSID and Password**.  
- Ensure your router **supports 2.4 GHz WiFi** (ESP32 doesn't support 5 GHz).  

💡 **No Data on Blynk?**  
- Make sure you **assigned the correct Virtual Pins** in Blynk.  
- Verify **your ESP32 is online** in the Blynk dashboard.  

💡 **Incorrect pH Readings?**  
- Perform **calibration** using buffer solutions.  
- Ensure **proper wiring and ADC resolution settings**.  

---

## 🚀 **Future Improvements**  
🔹 Add **MQTT support** for alternative cloud integration.  
🔹 Integrate **machine learning** to detect water quality trends.  
🔹 Expand with **additional sensors (TDS, EC, Turbidity, etc.)**.  

---

## 🏆 **Credits & License**  
💡 Developed by **Yodha Ardiansyah**  
🌍 Website: [arunovasi.my.id](https://arunovasi.my.id)  
📜 **License:** Open-source (MIT) – Feel free to modify and improve! 🚀  

---

This **README** is designed to be **informative, structured, and visually appealing**. Let me know if you want any further tweaks! 🚀😊
