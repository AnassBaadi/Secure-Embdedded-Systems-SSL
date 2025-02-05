#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "DHTesp.h"

const char* ssid = "Wokwi-GUEST";        // Wi-Fi SSID
const char* password = "";               // Wi-Fi Password (Wokwi-GUEST has none)
const char* mqttServer = "broker.hivemq.com"; // Public MQTT broker
const int mqttPort = 8883;               // Secure MQTT port (SSL/TLS)

// Root CA Certificate
const char* rootCACertificate = R"EOF(
-----BEGIN CERTIFICATE-----
MIIEkjCCA3qgAwIBAgITBn+USionzfP6wq4rAfkI7rnExjANBgkqhkiG9w0BAQsF
ADCBmDELMAkGA1UEBhMCVVMxEDAOBgNVBAgTB0FyaXpvbmExEzARBgNVBAcTClNj
b3R0c2RhbGUxJTAjBgNVBAoTHFN0YXJmaWVsZCBUZWNobm9sb2dpZXMsIEluYy4x
OzA5BgNVBAMTMlN0YXJmaWVsZCBTZXJ2aWNlcyBSb290IENlcnRpZmljYXRlIEF1
dGhvcml0eSAtIEcyMB4XDTE1MDUyNTEyMDAwMFoXDTM3MTIzMTAxMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaOCATEwggEtMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/
BAQDAgGGMB0GA1UdDgQWBBSEGMyFNOy8DJSULghZnMeyEE4KCDAfBgNVHSMEGDAW
gBScXwDfqgHXMCs4iKK4bUqc8hGRgzB4BggrBgEFBQcBAQRsMGowLgYIKwYBBQUH
MAGGImh0dHA6Ly9vY3NwLnJvb3RnMi5hbWF6b250cnVzdC5jb20wOAYIKwYBBQUH
MAKGLGh0dHA6Ly9jcnQucm9vdGcyLmFtYXpvbnRydXN0LmNvbS9yb290ZzIuY2Vy
MD0GA1UdHwQ2MDQwMqAwoC6GLGh0dHA6Ly9jcmwucm9vdGcyLmFtYXpvbnRydXN0
LmNvbS9yb290ZzIuY3JsMBEGA1UdIAQKMAgwBgYEVR0gADANBgkqhkiG9w0BAQsF
AAOCAQEAYjdCXLwQtT6LLOkMm2xF4gcAevnFWAu5CIw+7bMlPLVvUOTNNWqnkzSW
MiGpSESrnO09tKpzbeR/FoCJbM8oAxiDR3mjEH4wW6w7sGDgd9QIpuEdfF7Au/ma
eyKdpwAJfqxGF4PcnCZXmTA5YpaP7dreqsXMGz7KQ2hsVxa81Q4gLv7/wmpdLqBK
bRRYh5TmOTFffHPLkIhqhBGWJ6bt2YFGpn6jcgAKUj6DiAdjd4lpFw85hdKrCEVN
0FE6/V1dN2RMfjCyVSRCnTawXZwXgWHxyvkQAiSr6w10kY17RSlQOYiypok1JR4U
akcjMS9cmvqtmg5iUaQqqcT5NJ0hGA==
-----END CERTIFICATE-----
)EOF";

WiFiClientSecure wifiClientSecure;       // Secure WiFi client
PubSubClient mqttClient(wifiClientSecure);

const char* topic = "esp32/chat"; // Shared topic for both ESPs
const char* topic2 = "esp32/data";  

const int DHT_PIN = 22;
DHTesp dhtSensor;
String t;
String h;

String clientId;                         // Unique identifier for each ESP

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Ignore messages published by this ESP
  if (message.startsWith(clientId)) return;

  // Display received message
  Serial.println("Received: " + message);
  Serial.println("---");
  digitalWrite(16, HIGH);
  delay(2800);
  digitalWrite(16, LOW);
}


void setup() {
  Serial.begin(115200);
  pinMode(14, OUTPUT);
  pinMode(16, OUTPUT);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  // Generate a unique client ID based on ESP's MAC address
  clientId = "ESP32-#1 ";
  Serial.println("Client ID: " + clientId);

  // Connect to Wi-Fi
  connectToWiFi();

  // Configure MQTT client with SSL/TLS
  wifiClientSecure.setCACert(rootCACertificate);
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setKeepAlive(600); // Increase keep-alive interval
  mqttClient.setCallback(callback);

  // Connect to the MQTT broker
  connectToMQTT();
}

void loop() {
  ensureWiFiConnected();
  ensureMQTTConnected();
  mqttClient.loop();
  sendTempHum();

  // Check for user input from Serial Monitor
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    message.trim(); // Remove any trailing newline or spaces

    // Publish the message with the client ID prefix
    String fullMessage = clientId + ": " + message;
    mqttClient.publish(topic, fullMessage.c_str());
    Serial.println("Published: " + fullMessage);
    Serial.println("---");
    digitalWrite(14, HIGH);
    delay(2800);
    digitalWrite(14, LOW);
  }
}

void sendTempHum(){
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  t=String(data.temperature, 2);
  h=String(data.humidity, 1);
  String fullMessage = "{\"Temperature\":"+ t +",\"Humidite\":"+h+"}" ;
  mqttClient.publish(topic2, fullMessage.c_str());
  delay(2200);
  // Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  // Serial.println("Humidity: " + String(data.humidity, 1) + "%");
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

void connectToMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT broker...");
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("Connected to MQTT broker!");
      mqttClient.subscribe(topic);
      Serial.println("Subscribed to topic: " + String(topic));
      mqttClient.publish(topic, (clientId + " connected!").c_str());
    } else {
      Serial.print("Failed, rc=");
      Serial.println(mqttClient.state());
      delay(2000);
    }
  }
}

void ensureWiFiConnected() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconnecting to WiFi...");
    connectToWiFi();
  }
}

void ensureMQTTConnected() {
  if (!mqttClient.connected()) {
    Serial.println("Disconnected from MQTT broker. Reconnecting...");
    connectToMQTT();
  }
}
