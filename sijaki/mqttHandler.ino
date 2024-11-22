void reconnectMQTT() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect(ID, mqttUser, mqttPassword)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void publishData(const char* topic, Data* data) {
    StaticJsonDocument<200> doc;

    doc["id"] = data->id;
    doc["coordinates"]["latitude"] = data->coordinates.latitude;
    doc["coordinates"]["longitude"] = data->coordinates.longitude;
    doc["fullness"]["level"] = data->fullness.level;

    char jsonBuffer[256];
    serializeJson(doc, jsonBuffer);

    client.publish(topic, jsonBuffer);
}