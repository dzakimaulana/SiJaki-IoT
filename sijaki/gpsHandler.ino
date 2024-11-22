void getLocation(double* latitude, double* longitude) {
    while (gpsSerial.available() > 0) {
        if (gps.encode(gpsSerial.read())) {
            if (gps.location.isUpdated()) {
                *latitude = gps.location.lat();
                *longitude = gps.location.lng();
            }
        }
    }
  Serial.printf("[*] Latitude : %f\n", *latitude);
  Serial.printf("[*] Longitude : %f\n", *longitude);
  delay(200);
}