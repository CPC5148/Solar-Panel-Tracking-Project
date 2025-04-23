#include <Servo.h>
#include "DHT.h"

// Pin Definitions
#define SERVOPINH 5
#define SERVOPINV 6
#define DHTPIN 2
#define DHTTYPE DHT11
#define VOLTAGE_SENSOR_PIN A4

// Servo Setup 
Servo horizontal;
Servo vertical;
int servoHPos = 90;
int servoVPos = 130;
const int servoHMin = 0, servoHMax = 180;
const int servoVMin = 90, servoVMax = 180;

// LDR Pins 
const int ldrTopLeft = A0;
const int ldrTopRight = A1;
const int ldrBottomLeft = A2;
const int ldrBottomRight = A3;
const int lightTolerance = 50;

// ----- DHT Sensor -----
DHT dht(DHTPIN, DHTTYPE);

// ----- Voltage & Power Sensing -----
const float voltageDividerRatio = 5.0; // Adjust based on your voltage divider
float panelVoltage = 0.0;               // Volts
float currentDraw = 0.4;                // Amps (assumed constant)
float powerOutput = 0.0;                // Watts

// Timing 
unsigned long lastPrintTime = 0;
const unsigned long printInterval = 2000; // ms

void setup() {
  Serial.begin(9600);
  dht.begin();

  horizontal.attach(SERVOPINH);
  vertical.attach(SERVOPINV);

  horizontal.write(servoHPos);
  vertical.write(servoVPos);
}

void loop() {
  //  LDR Readings 
  int lt = analogRead(ldrTopLeft);
  int rt = analogRead(ldrTopRight);
  int ld = analogRead(ldrBottomLeft);
  int rd = analogRead(ldrBottomRight);

  int avgTop = (lt + rt) / 2;
  int avgBottom = (ld + rd) / 2;
  int avgLeft = (lt + ld) / 2;
  int avgRight = (rt + rd) / 2;

  // ----- Vertical Tracking -----
  int diffV = avgTop - avgBottom;
  if (abs(diffV) > lightTolerance) {
    servoVPos += (diffV > 0) ? 1 : -1;
    servoVPos = constrain(servoVPos, servoVMin, servoVMax);
    vertical.write(servoVPos);

  // Horizontal Tracking 
  int diffH = avgLeft - avgRight;
  if (abs(diffH) > lightTolerance) {
    servoHPos += (diffH > 0) ? 1 : -1;
    servoHPos = constrain(servoHPos, servoHMin, servoHMax);
    horizontal.write(servoHPos);
  }

  // Print Data Every 2 Seconds
  if (millis() - lastPrintTime >= printInterval) {
    lastPrintTime = millis();

    float tempF = dht.readTemperature(true);
    float humidity = dht.readHumidity();

    // Voltage and Power Reading
    int rawADC = analogRead(VOLTAGE_SENSOR_PIN);
    panelVoltage = (rawADC * 5.0 / 1023.0) * voltageDividerRatio; // in Volts
    powerOutput = panelVoltage * currentDraw; // in Watts

    int panelMilliVolts = panelVoltage * 1000; // mV
    int powerMilliWatts = powerOutput * 1000;  // mW

    // Serial Output if neccessary
    

    // Optional: LabVIEW fpr better parsing
    Serial.print(tempF); Serial.print(",");
    Serial.print(humidity); Serial.print(",");
    Serial.print(servoHPos); Serial.print(",");
    Serial.print(servoVPos); Serial.print(",");
    Serial.print(panelMilliVolts); Serial.print(",");
    Serial.println(powerMilliWatts); 
  }

  delay(10); // Small delay for loop pacing
}
