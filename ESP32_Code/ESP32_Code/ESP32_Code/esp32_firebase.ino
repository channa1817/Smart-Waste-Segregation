#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID "ChannaWifi"
#define WIFI_PASSWORD "12345678"

#define FIREBASE_HOST "smart-waste-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "abcd1234"

FirebaseData firebaseData;

String data = "";

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX2 = 16, TX2 = 17

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {

  while (Serial2.available()) {
    char c = Serial2.read();
    data += c;

    if (c == '\n') {

      int dryIndex = data.indexOf("DRY:");
      int wetIndex = data.indexOf("WET:");
      int metalIndex = data.indexOf("METAL:");

      if (dryIndex != -1 && wetIndex != -1 && metalIndex != -1) {

        int dry = data.substring(dryIndex + 4, data.indexOf(",", dryIndex)).toInt();
        int wet = data.substring(wetIndex + 4, data.indexOf(",", wetIndex)).toInt();
        int metal = data.substring(metalIndex + 6).toInt();

        Firebase.setInt(firebaseData, "/waste/dry", dry);
        Firebase.setInt(firebaseData, "/waste/wet", wet);
        Firebase.setInt(firebaseData, "/waste/metal", metal);

        Serial.println("Firebase Updated");
      }

      data = "";
    }
  }
}
