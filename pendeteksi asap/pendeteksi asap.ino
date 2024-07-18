#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "https://iot-pendeteksi-asap-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "hCxLUW9Dy4IvKLQZWolD88KXOKr5KBBqKSItg4GW"
#define WIFI_SSID "#"
#define WIFI_PASSWORD "00000000"

#define asap D0
#define buzzer D1
#define LED D3
#define fan D4

FirebaseData firebaseData;

String path = "/Asap";

int nilaiasap = 1;

void setup() {
  Serial.begin(115200);
  pinMode(asap, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(fan, OUTPUT);

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
  nilaiasap = digitalRead(asap);

if (nilaiasap==0){
  Firebase.setString(firebaseData, path, "Ada Asap");
  tone(buzzer, 1000); 
  digitalWrite(LED, HIGH);
  digitalWrite(fan, LOW);
} else {
  Firebase.setString(firebaseData, path, "Tidak Ada Asap");
  noTone(buzzer); 
  digitalWrite(LED, LOW);
  digitalWrite(fan, HIGH);
} 
}