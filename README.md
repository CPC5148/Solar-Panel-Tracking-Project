# Solar-Panel-Tracking-Project
# Solar Panel Tracking Project

This project implements a dual-axis solar tracker using Arduino to maximize solar energy capture. The system uses LDR sensors for light detection, servo motors to orient the panel, a DHT11 sensor for environmental monitoring, and LabVIEW to visualize power output in real time.


Components Used
- Arduino Uno
- 4x LDRs (Light Dependent Resistors)
- 2x Servo Motors (horizontal & vertical rotation)
- DHT11 Temperature & Humidity Sensor
- Voltage Divider Circuit (for measuring solar panel output)
- LabVIEW (for real-time data visualization via serial communication)

Features
- **Dual-Axis Tracking**: Moves panel to follow the sun using LDRs.
- **Environmental Monitoring**: Reports temperature and humidity.
- **Power Calculation**: Calculates power output in milliwatts.
- **Real-Time Serial Output**: Outputs CSV-formatted data for LabVIEW parsing:
  ```
  Temperature (°F), Humidity (%), Servo H Angle, Servo V Angle, Panel Voltage (mV), Power (mW)
  ```
Simulation Mode (LabVIEW): Option to simulate sun angle and light intensity without hardware.

LabVIEW Visualization
LabVIEW VI reads serial data from Arduino and:
- Plots Power vs Time.
- Displays live temperature, humidity, servo angles, and panel voltage.
- Includes a simulation mode toggle to test system without physical hardware.

How It Works
- LDRs detect the brightest direction of the light source.
- Arduino compares light intensities and adjusts servo angles accordingly.
- A voltage sensor monitors the panel’s output.
- Power is calculated using a fixed estimated current (`0.4A`).
- Data is sent over serial every 2 seconds.

How to Run
1. Upload the Arduino code to your board.
2. Open LabVIEW VI or Serial Monitor.
3. Ensure baud rate is set to `9600`.
4. Watch data stream live or simulate input using LabVIEW controls.
