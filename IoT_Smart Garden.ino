#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "https://tubes-prak-ppi-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "d1Mgv818WIhDzzLvYvXUL0Nj4UgHhRcC1AlK0Ml9"
#define WIFI_SSID "#"
#define WIFI_PASSWORD "00000000"

#define pump D4
int SoilSensor = A0;
String pompa, keadaan;

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  pinMode(SoilSensor, INPUT);
  pinMode(pump, OUTPUT);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.reconnectWiFi(true);
}

void loop() {
  float kelembabanTanah;
  int hasilPembacaan = analogRead(SoilSensor);
  kelembabanTanah = (100 - ((hasilPembacaan / 1024.0) * 100));
  Firebase.setString(firebaseData, "/Kelembaban", kelembabanTanah);

  Serial.print("Persentase Kelembaban Tanah = ");
  Serial.print(kelembabanTanah);
  Serial.println("%");

  if (Firebase.getString(firebaseData, "/keadaan")) {
    keadaan = firebaseData.stringData();
    if (keadaan == "1") {
      if (kelembabanTanah <= 35) {
        digitalWrite(pump, LOW);
        Serial.println("Pompa Menyala");
        Firebase.setString(firebaseData, "/pump", "ON");
      } else {
        digitalWrite(pump, HIGH);
        Serial.println("Pompa Mati");
        Firebase.setString(firebaseData, "/pump", "OFF");
      }
    } else if (keadaan == "0") {
      if (Firebase.getString(firebaseData, "/pb")) {
        pompa = firebaseData.stringData();
        if (pompa == "1") {
          digitalWrite(pump, LOW);
          Serial.println("Pompa Menyala");
          Firebase.setString(firebaseData, "/pump", "ON");
        } else if (pompa == "0") {
          digitalWrite(pump, HIGH);
          Serial.println("Pompa Mati");
          Firebase.setString(firebaseData, "/pump", "OFF");
        }
      }
    }
  }
}