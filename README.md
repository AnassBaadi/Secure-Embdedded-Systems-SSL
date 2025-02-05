Securing Communications in Embedded Systems: Integrating SSL/TLS onto MQTT for Two-Way Communication
This project explores how to secure communications between embedded systems using SSL/TLS encryption in conjunction with the MQTT protocol. The goal is to demonstrate the ability to securely transmit data between devices while providing real-time feedback and analysis of the traffic. The project integrates the MQTT messaging protocol with SSL/TLS encryption to ensure secure two-way communication between devices.

Table of Contents
Project Overview
Hardware Setup
Software Setup
System Architecture
Communication Protocol
Traffic Analysis
Tools and Libraries Used
Key Features
Running the Project
License
Acknowledgments
Project Overview
In this project, I used ESP32 microcontroller boards to implement both secure and unsecure communication using the MQTT protocol. By integrating SSL/TLS encryption, I was able to ensure the security of data transmission over the network.

The system includes two sets of devices:

Two ESP32 devices without SSL: These devices communicate over unencrypted MQTT (using port 1883).
Two ESP32 devices with SSL: These devices use SSL/TLS encryption to communicate securely (using port 8883).
The embedded devices collect and transmit temperature and humidity data from a DHT22 sensor, and the data is sent to an MQTT broker for real-time visualization. The project also enables two-way communication, where messages can be sent from the client to the devices, and network traffic can be monitored using Wireshark.

Hardware Setup
The hardware setup consists of four ESP32 development boards:

ESP32 with C++ (without SSL): This device is programmed with C++ using the Arduino IDE. It is equipped with a DHT22 sensor to measure temperature and humidity. The device transmits sensor data to an MQTT topic at regular intervals.

ESP32 with MicroPython (without SSL): This device is programmed with MicroPython. It subscribes to the same MQTT topic as the first device and visualizes the received data.

ESP32 with C++ (with SSL): Another device is programmed with C++ and is configured to communicate over an encrypted MQTT channel using SSL/TLS (port 8883).

ESP32 with MicroPython (with SSL): This device also uses MicroPython and communicates securely using SSL/TLS encryption.

DHT22 Sensor
The DHT22 is used to measure temperature and humidity. It provides digital output, which is read by the ESP32 and transmitted via MQTT to the broker.

Software Setup
The system relies on several software components to ensure smooth operation. Here's the breakdown:

Arduino IDE: Used to program the ESP32 devices with C++ for non-SSL communication. The MQTT library and the DHT sensor library are used to gather and send the data.

MicroPython: Used to program the ESP32 devices with MicroPython for both non-SSL and SSL communications. The umqtt.simple library is used to handle the MQTT communication.

MQTT Broker: An MQTT broker (such as Mosquitto) is used to facilitate the communication between the devices. It handles both encrypted and unencrypted MQTT connections.

Wireshark: Used to analyze the network traffic to monitor unencrypted and encrypted MQTT messages. It captures the packets for both port 1883 (non-SSL) and port 8883 (SSL).

MQTT Explorer: A powerful MQTT client used to visualize and interact with MQTT topics. It provides an intuitive interface for subscribing to topics and publishing messages to the broker.

Wokwi: An online simulator used to emulate the ESP32 devices. This tool also allows you to download PCAP files for offline traffic analysis.

System Architecture
The architecture of the system is as follows:

pgsql
Copier
+---------------------+           +---------------------+           +---------------------+
|  ESP32 (C++ - No SSL)  |<-------->|    MQTT Broker      |<-------->| ESP32 (MicroPython - No SSL) |
+---------------------+           +---------------------+           +---------------------+
       |                               |                                 |
       |                               |                                 |
       v                               v                                 v
+---------------------+           +---------------------+           +---------------------+
| ESP32 (C++ - SSL)   |<-------->|    MQTT Broker      |<-------->| ESP32 (MicroPython - SSL)   |
+---------------------+           +---------------------+           +---------------------+
The MQTT Broker serves as the central communication hub between all ESP32 devices.
Data from the DHT22 sensor is sent to an MQTT topic by the C++ (non-SSL) device and can be read by the other devices using MQTT.
Two-way communication allows clients to publish messages to the ESP32 devices.
Communication Protocol
The devices communicate using the MQTT protocol with the following settings:

Non-SSL Communication (Port 1883): This is the default MQTT protocol for unencrypted communication. It is used by the ESP32 devices programmed in C++ and MicroPython (without SSL).

SSL Communication (Port 8883): The ESP32 devices with SSL/TLS encryption communicate over port 8883 to ensure secure communication. This encrypted channel provides data privacy and integrity during transmission.

Traffic Analysis
Network traffic analysis is an important part of this project to observe how data is transmitted between the devices and how encryption impacts the traffic.

Wireshark Analysis: Using Wireshark, I capture and analyze the network traffic for both non-SSL (port 1883) and SSL (port 8883) communications.

For non-SSL communication, Wireshark will display clear, readable MQTT packets.
For SSL communication, the packets will appear encrypted, and no readable data can be observed without decrypting the SSL/TLS connection.
PCAP Files: You can also download PCAP files generated by Wokwi, a simulation platform for the ESP32. These files can be loaded into Wireshark for offline analysis of the network traffic.

Key Features
Real-Time Monitoring: Visualize real-time temperature and humidity data from the DHT22 sensor using MQTT Explorer.
Secure Communication: Demonstrates secure communication between devices by using SSL/TLS encryption with the MQTT protocol.
Two-Way Communication: Send and receive messages from the ESP32 devices to interact with the system.
Network Traffic Analysis: Use Wireshark to analyze both encrypted and unencrypted MQTT traffic.
Cross-Platform Development: The project uses both C++ and MicroPython programming languages to showcase flexibility and compatibility across different development environments.
Offline PCAP Analysis: Download PCAP files from Wokwi for offline traffic analysis.
Running the Project
To run this project on your local machine:

Set up the MQTT Broker:

You can use a local MQTT broker like Mosquitto or an online broker (e.g., CloudMQTT).
Make sure the broker is configured to support both unencrypted (port 1883) and encrypted (port 8883) MQTT connections.
Program the ESP32 Devices:

Install Arduino IDE and MicroPython on your ESP32 devices.
Load the corresponding code (C++ for non-SSL and MicroPython for both SSL and non-SSL) onto the ESP32 devices.
Monitor Communication:

Open MQTT Explorer and connect it to your MQTT broker to visualize the data being sent by the ESP32 devices.
You can also send test messages from the client to the devices.
Analyze Network Traffic:

Use Wireshark to capture the traffic from your network.
Specify port 1883 for unencrypted MQTT traffic and port 8883 for SSL-encrypted traffic.
Alternatively, download the PCAP files from Wokwi and analyze the captured data.
Tools and Libraries Used
ESP32 Development Boards
Arduino IDE (for C++ programming)
MicroPython (for MicroPython programming)
MQTT Protocol (for communication)
Wireshark (for network traffic analysis)
MQTT Explorer (for visualizing MQTT topics)
Mosquitto (for MQTT broker)
Wokwi (for simulation and PCAP file generation)
DHT22 Sensor Library (for reading sensor data)
License
This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgments
Thanks to the ESP32 community for the open-source tools and libraries.
Special thanks to Wokwi for providing a fantastic ESP32 simulation platform.
Credit to Wireshark for being a powerful tool in analyzing network traffic.
Let me know if you want any further adjustments!
