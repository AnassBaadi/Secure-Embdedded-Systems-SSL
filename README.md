# Securing Communications in Embedded Systems: SSL/TLS Integration with MQTT on ESP32

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

---

## Overview  
This project demonstrates how to secure communication in IoT/embedded systems by integrating SSL/TLS encryption with the MQTT protocol. It focuses on achieving secure two-way communication between ESP32 microcontrollers and an hiveMQ's MQTT broker, comparing unencrypted vs. encrypted MQTT traffic. Two ESP32 setups are used:  
1. **Non-SSL MQTT** (port `1883`) using C/C++ and MicroPython.  
2. **SSL/TLS-Enabled MQTT** (port `8883`) using C/C++ and MicroPython.  

The system includes real-time sensor data transmission (temperature/humidity via DHT22), message visualization with MQTT Explorer, and network traffic analysis using Wireshark and Wokwi-generated PCAP files.

---

## Key Features  
- 🔒 **SSL/TLS Integration**: Secure MQTT communication on port `8883` with certificate-based authentication.  
- ↔️ **Two-Way Communication**: Publish sensor data from ESP32 and subscribe to commands from clients (e.g., MQTT Explorer).  
- 💻 **Multi-Language Implementation**:  
  - **C/C++** (Arduino Framework): ESP32 with DHT22 sensor for environmental monitoring.  
  - **MicroPython**: Lightweight scripting for rapid prototyping.  
- 📡 **Traffic Analysis**: Compare encrypted vs. unencrypted MQTT packets using Wireshark (ports `1883`/`8883`).  
- 🎮 **Hardware & Simulation**: Tested on physical ESP32 devices and analyzed via Wokwi’s simulated PCAP captures.  

---

## Components  
### Hardware  
- **ESP32 Microcontrollers** (4 devices):  
  - 2x ESP32 (C/C++ + MicroPython) without SSL.  
  - 2x ESP32 (C/C++ + MicroPython) with SSL/TLS.  
- **DHT22 Sensor**: Measures temperature and humidity (connected to C/C++ ESP32).  

### Software  
- **MQTT Broker**: Mosquitto or cloud-based broker (e.g., HiveMQ).  
- **MQTT Explorer**: Desktop client for visualizing topics and messages.  
- **Wireshark**: Network protocol analyzer for inspecting MQTT traffic.  
- **Wokwi**: Embedded systems simulator for generating PCAP files.  

---

## Workflow  
1. **Data Transmission**:  
   - C/C++ ESP32 (with DHT22) publishes sensor data to an MQTT topic.  
   - MicroPython ESP32 publishes test messages.  
2. **Client Interaction**:  
   - MQTT Explorer subscribes to sensor topics and publishes control commands (e.g., LED triggers).  
3. **Security Analysis**:  
   - **Unencrypted Traffic**: Wireshark captures plaintext MQTT packets on port `1883`.  
   - **Encrypted Traffic**: SSL/TLS-secured traffic on port `8883` appears as encrypted data.  
   - **Wokwi PCAP**: Simulated traffic analysis for environments without physical hardware.  

---

## Setup Instructions  
### Hardware Configuration  
1. Connect the DHT22 sensor to the C/C++ ESP32 (e.g., GPIO pin 4).  
2. Configure all ESP32s to connect to Wi-Fi and your MQTT broker.  

### Software Setup  
1. **Non-SSL Setup**:  
   - Use port `1883` for MQTT communication.  
2. **SSL/TLS Setup**:  
   - Load CA certificates onto ESP32s (e.g., using `WiFiClientSecure` in C/C++).  
   - Use port `8883` for encrypted communication.  
3. **MQTT Explorer**:  
   - Install and connect to your broker (specify `1883` or `8883`).  

## Results & Analysis  
| **Metric**          | **Non-SSL (1883)**       | **SSL/TLS (8883)**       |
|----------------------|--------------------------|--------------------------|
| **Payload Visibility** | Plaintext (readable)     | Encrypted (unreadable)   |
| **Latency**          | Lower                    | Slightly Higher          |
| **Security**         | Vulnerable to eavesdropping | Secure against MITM attacks |

- **Wireshark Analysis**:  
  - Unencrypted traffic shows JSON payloads (e.g., `{"temp": 25.6, "humidity": 60}`).  
  - SSL/TLS traffic displays encrypted packets.  
- **Wokwi Simulation**: PCAP files validate traffic patterns without physical hardware.  

---
