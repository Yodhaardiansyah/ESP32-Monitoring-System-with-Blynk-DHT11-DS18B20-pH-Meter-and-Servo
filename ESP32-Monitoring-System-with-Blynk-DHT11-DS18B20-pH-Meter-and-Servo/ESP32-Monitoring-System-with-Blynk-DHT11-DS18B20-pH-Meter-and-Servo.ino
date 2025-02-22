/***************************************************
 * ESP32 Monitoring System with Blynk, DHT11, DS18B20, pH Meter, and Servo
 * Author: Yodha Ardiansyah
 * Website: https://arunovasi.my.id
 * License: Open-source (MIT)
 * 
 * Description:
 * - Reads temperature and humidity from DHT11.
 * - Reads water temperature from DS18B20.
 * - Measures pH level using an analog pH meter.
 * - Controls a servo motor via Blynk.
 * - Sends data to Blynk for remote monitoring.
 ***************************************************/

/* Replace with your Blynk Device Info */
#define BLYNK_TEMPLATE_ID "HIDDEN"
#define BLYNK_TEMPLATE_NAME "MonitoringSystem"
#define BLYNK_AUTH_TOKEN "HIDDEN"

/* Uncomment to enable serial debugging */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP32Servo.h>

// WiFi Credentials (Hidden for Security)
char ssid[] = "HIDDEN";
char pass[] = "HIDDEN";

// DHT11 Configuration
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// DS18B20 Configuration
#define ONE_WIRE_BUS 14
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// pH Meter Configuration
#define PH_PIN 35
#define VOLTAGE_REF 3.3
#define ADC_RESOLUTION 4095

// Calibration Values (Adjust if needed)
float voltage1 = 2.6;
float pH1 = 6.86;
float voltage2 = 2.2;
float pH2 = 9.18;

float slope, offset;

// Servo Configuration
Servo servo;
const int servoPin = 15;
const int servoOnAngle = 180;
const int servoOffAngle = 90;

// Blynk Virtual Pins
#define VPIN_HUMIDITY V2
#define VPIN_TEMP_DHT V1
#define VPIN_TEMP_DS18B20 V3
#define VPIN_PH V5
#define VPIN_SERVO V4

BlynkTimer timer;

// Function to Convert Voltage to pH
float voltageToPH(float voltage) {
  return slope * voltage + offset;
}

// Function to Read Sensor Data
void sendSensorData() {
  // Read DHT11 Data
  float humidity = dht.readHumidity();
  float tempDHT = dht.readTemperature();

  if (!isnan(humidity) && !isnan(tempDHT)) {
    Blynk.virtualWrite(VPIN_HUMIDITY, humidity);
    Blynk.virtualWrite(VPIN_TEMP_DHT, tempDHT);
    Serial.print("DHT11 - Temp: ");
    Serial.print(tempDHT);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }

  // Read DS18B20 Data
  sensors.requestTemperatures();
  float tempDS18B20 = sensors.getTempCByIndex(0);

  if (tempDS18B20 != DEVICE_DISCONNECTED_C) {
    Blynk.virtualWrite(VPIN_TEMP_DS18B20, tempDS18B20);
    Serial.print("DS18B20 - Temp: ");
    Serial.print(tempDS18B20);
    Serial.println(" °C");
  } else {
    Serial.println("Failed to read from DS18B20 sensor!");
  }

  // Read pH Sensor Data
  int rawValue = analogRead(PH_PIN);
  float voltage = (rawValue / float(ADC_RESOLUTION)) * VOLTAGE_REF;
  float pHValue = voltageToPH(voltage);

  Blynk.virtualWrite(VPIN_PH, pHValue);
  Serial.print("pH Meter - Raw ADC Value: ");
  Serial.println(rawValue);
  Serial.print("Voltage: ");
  Serial.print(voltage, 2);
  Serial.println(" V");
  Serial.print("pH Value: ");
  Serial.println(pHValue);
}

// Blynk Callback to Control Servo Motor
BLYNK_WRITE(VPIN_SERVO) {
  int pinValue = param.asInt();

  if (pinValue == 1) {
    servo.write(servoOnAngle);
    Serial.println("Servo ON: Turning Right");
  } else {
    servo.write(servoOffAngle);
    Serial.println("Servo OFF: Returning to Center");
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initialize Sensors
  dht.begin();
  sensors.begin();

  // Initialize Servo
  servo.attach(servoPin);
  servo.write(servoOffAngle);

  // Calculate Calibration for pH Meter
  slope = (pH2 - pH1) / (voltage2 - voltage1);
  offset = pH1 - (slope * voltage1);

  Serial.println("Monitoring System Ready!");
  Serial.print("pH Meter Calibration - Slope: ");
  Serial.println(slope);
  Serial.print("Offset: ");
  Serial.println(offset);

  // Set Timer Interval for Sensor Reading (1s)
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
