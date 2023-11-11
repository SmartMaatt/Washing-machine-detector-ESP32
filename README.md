<h1 align="center">
    Alarm Amplifier Project
</h1>

<p align="center">
  <a href="#overview">Overview</a> •
  <a href="#hardware">Hardware</a> •
  <a href="#software">Software</a> •
  <a href="#usage-guide">Usage Guide</a> •
  <a href="#testing-and-troubleshooting">Testing and Troubleshooting</a> •
  <a href="#license">License</a>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg" />
  <img src="https://img.shields.io/badge/Authors-SmartMatt-blue" />
</p>

## Overview

This project involves the development of an alarm amplifier system designed to monitor the light status of household appliances using photoresistors. It reacts to changes in light with an audio alarm and Bluetooth console notifications. The system is built around the ESP32 microcontroller, incorporating features like Wi-Fi and Bluetooth connectivity.

## Hardware

### Components

- **ESP32 Microcontroller**: Central processing unit of the system, equipped with Wi-Fi and Bluetooth modules.
- **MAX99357 Audio Amplifier**: Converts digital signals into analog sound for the speaker.
- **Photoresistors**: Detects the light status from household appliances.
- **10kOhm Resistors**: Used in conjunction with the photoresistors to create a voltage divider.
- **B3F-1000S Button**: Manual reset button for the alarm system.

![Hardware Components Image](https://smartmatt.pl/github/alarm-amplifier/alarm-amplifier-hardware-components.png)
*Hardware Components*

### Circuit Diagram

The following is the circuit diagram of the alarm amplifier system:

![Circuit Diagram Image](https://smartmatt.pl/github/alarm-amplifier/alarm-amplifier-circuit-diagram.png)
*Circuit Diagram*

## Software

### Source Code

The project's source code is written in C and utilizes the Arduino IDE for development. Key libraries include:

- `AudioOutputI2S.h`
- `AudioFileSourcePROGMEM.h`
- `AudioGeneratorFLAC.h`
- `BluetoothSerial.h`

### Main Functionalities

- **Initial Setup**: Initializes the system and sets up Bluetooth and audio configurations.
- **Loop Function**: Manages the reading of sensor data, Bluetooth inputs, and alarm triggering.
- **Alarm Management**: Handles the audio alarm based on sensor input and allows manual reset.

### Bluetooth Commands

- `input1`, `input2`, `input3`: Activate/deactivate specific sensors.
- `ShowData`: Display current sensor data and status.
- `stop`: Stop the current alarm.

## Installation and Setup

To install and set up the software on your ESP32 microcontroller, follow these steps:

1. **Software Requirements**:
   - Ensure you have the latest version of the Arduino IDE installed on your computer. It can be downloaded from the [Arduino website](https://www.arduino.cc/en/software).

2. **ESP32 Board Manager Installation**:
   - Open the Arduino IDE.
   - Go to File > Preferences and in the "Additional Board Manager URLs" field, add the following URL: `https://dl.espressif.com/dl/package_esp32_index.json`.
   - Open the Board Manager by going to Tools > Board > Boards Manager, search for ESP32, and install the latest version.

3. **Connect the ESP32 to Your Computer**:
   - Using a micro USB cable, connect the ESP32 to your computer. Ensure that the ESP32 is powered on.

4. **Select the Correct Board and Port**:
   - In the Arduino IDE, go to Tools > Board and select the appropriate ESP32 board (e.g., ESP32 Dev Module).
   - Go to Tools > Port and select the COM port that the ESP32 is connected to.

5. **Load the Software**:
   - Open the project source code in the Arduino IDE.
   - If any additional libraries are required (as mentioned in the Software section), make sure they are installed.

6. **Compile and Upload**:
   - Click the "Upload" button in the Arduino IDE to compile the code and upload it to the ESP32.
   - Wait for the message "Done uploading" to appear in the IDE's console window.

7. **Verify Operation**:
   - After the code is successfully uploaded, the ESP32 should start running the program.
   - Monitor the Serial Monitor in the Arduino IDE for any debug information or confirmation messages.

8. **Bluetooth Pairing**:
   - On your smartphone or Bluetooth-enabled device, turn on Bluetooth and search for new devices.
   - Find the "Washing Machine Detector" and pair with it.
   - Once paired, you can use Bluetooth terminal applications to send commands to the ESP32.

If you encounter any issues during installation, refer to the Troubleshooting section for guidance.

## Usage Guide

To effectively utilize the alarm amplifier system, follow these steps:

1. **Power Connection**: Connect the system to a power source using the micro USB port on the ESP32.
2. **Mounting**: Attach the system near your chosen appliance, ensuring the photoresistors are positioned to accurately detect the appliance's light status.
3. **Bluetooth Connection**: Use a smartphone or computer with Bluetooth to connect to the system. The default Bluetooth name is "Washing Machine Detector".
4. **Sensor Configuration**: Via the Bluetooth terminal, send commands to activate or deactivate the sensors based on your needs. Use `input1`, `input2`, and `input3` commands to control respective sensors.
5. **Monitoring**: The system will now monitor the light signals from the appliance and trigger the alarm when specific conditions are met.
6. **Responding to Alarms**: When the alarm sounds, indicating the completion of an appliance's cycle, you can turn it off using the manual button on the system or through the Bluetooth command `stop`.
7. **Resetting the System**: After stopping the alarm, the system will reset to its initial state with all sensors deactivated. Reactivate the desired sensors to continue monitoring.

## Testing and Troubleshooting

### Testing Process

1. **Functional Testing**: Each component (microcontroller, audio amplifier, photoresistors) was individually tested for functionality before integration.
2. **Integration Testing**: The complete system was tested to ensure all components worked together seamlessly.
3. **Scenario Testing**: Simulated various appliance statuses (light on/off) to test the system's response and the accuracy of sensor readings.
4. **Usability Testing**: Non-technical users tested the system to ensure user-friendliness and ease of setup and operation.
5. **Longevity Testing**: Operated the system over extended periods to ensure durability and consistent performance.

### Troubleshooting

- **Bluetooth Connectivity Issues**: Ensure the device is within range and the ESP32 is powered correctly. Restart the Bluetooth connection if necessary.
- **False Alarms**: Check the positioning of the photoresistors. Ensure they accurately detect the appliance's light without interference from external light sources.
- **System Not Responding**: Verify the power supply and connections. Check for any loose connections in the circuit.

## Conclusions

1. **Functionality**: The system successfully detects the light status from appliances and triggers an alarm, demonstrating effective integration of hardware and software components.
2. **User-Friendly Design**: Testing with non-technical users highlighted the system's user-friendly design and easy setup process.
3. **Challenges Overcome**: Initially faced challenges with integrating sound playback and Bluetooth connectivity. These were resolved through software modifications, improving the system's reliability.
4. **Technical Skills Enhanced**: Gained significant experience in microprocessor systems, circuit design, and practical problem-solving.
5. **Future Improvements**: Potential enhancements include refining the user interface for Bluetooth control and expanding compatibility with a wider range of appliances.

This project has been a comprehensive learning journey, enhancing both technical skills and practical problem-solving abilities in the field of microprocessor systems and IoT applications.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
&copy; 2023 Mateusz Płonka (SmartMatt). All rights reserved.
<a href="https://smartmatt.pl/">
    <img src="https://smartmatt.pl/github/smartmatt-logo.png" title="SmartMatt Logo" align="right" width="60" />
</a>

<p align="left">
  <a href="https://smartmatt.pl/">Portfolio</a> •
  <a href="https://github.com/SmartMaatt">GitHub</a> •
  <a href="https://www.linkedin.com/in/mateusz-p%C5%82onka-328a48214/">LinkedIn</a> •
  <a href="https://www.youtube.com/user/SmartHDesigner">YouTube</a> •
  <a href="https://www.tiktok.com/@smartmaatt">TikTok</a>
</p>

