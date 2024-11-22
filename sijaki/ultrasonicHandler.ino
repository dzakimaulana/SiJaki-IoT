void getFullnessLevel(float* fullnessLevel) {

    digitalWrite(TP, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(TP, HIGH);
    delayMicroseconds(10);
    digitalWrite(TP, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(EP, HIGH);
    float distance = (duration * SOUND_VELOCITY) / 2.0; // Calculate distance in cm

    Serial.printf("[*] Distance : %f cm\n", distance);
    // Bound the distance within the range of 18 cm (full) and 26 cm (empty)
    if (distance > 26.0) {
        distance = 26.0;
    } else if (distance < 18.0) {
        distance = 18.0;
    }

    float percentage = ((26.0 - distance) / (26.0 - 18.0)) * 100.0;
    Serial.printf("[*] Percentage : %f %\n", percentage);
    if (percentage < 0) {
        percentage = 0;
    } else if (percentage > 100) {
        percentage = 100;
    }

    *fullnessLevel = percentage;
    delay(200);
}