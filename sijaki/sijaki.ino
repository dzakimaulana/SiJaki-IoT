#include <Arduino.h>

/* Device */
#define ID "#SJ001"

/* GPS Neo */
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
SoftwareSerial gpsSerial(D1, D2);

double latitude = -7.7749199656522885;
double longitude = 110.37409902898972;
void getLocation(double* latitude, double* longitude);

/* Sensor Ultrasonic */
#define SOUND_VELOCITY 0.0343
#define TP D6
#define EP D5
float fullnessLevel;
void getFullnessLevel(float* fullnessLevel);

/* WiFi */
#include <ESP8266WiFi.h>
const char ssid[] = "Galaxy";
const char password[] = "emang gaada kuota?";
void connectToWiFi(const char* ssid, const char* password);

/* MQTT */
#include <PubSubClient.h> 
const char* mqttServer = "54.255.193.69";
const int mqttPort = 1883;                 
const char mqttUser[] = "sijaki";
const char mqttPassword[] = "sijaki123";
const char topic[] = "sijaki/device/data";

/* Wi-Fi and MQTT client objects */
WiFiClient espClient;
PubSubClient client(espClient);

/* JSON data structure */
// https://randomnerdtutorials.com/decoding-and-encoding-json-with-arduino-or-esp8266/
#include <ArduinoJson.h>
struct Coordinates {
    double latitude;
    double longitude;
};

struct Fullness {
    float level;
};

struct Data {
    const char* id;
    struct Coordinates coordinates;
    struct Fullness fullness;
};


void setup() {
    // Serial
    Serial.begin(9600);
    gpsSerial.begin(9600);
    
    // WiFi
    connectToWiFi(ssid, password);

    // MQTT
    client.setServer(mqttServer, mqttPort);

    // Ultrasonic Sensor
    pinMode(TP, OUTPUT);
    pinMode(EP, INPUT);

    Serial.println("Device start...");
}

void loop() {
    // Check WiFi connection
    if (WiFi.status() != WL_CONNECTED) {
        reconnectWiFi(ssid, password);
    }

    // Check MQTT connection
    if (!client.connected()) {
        reconnectMQTT();
    }
    client.loop();

    // GPS
    getLocation(&latitude, &longitude);

    // Fulness
    getFullnessLevel(&fullnessLevel);

    delay(500);
}