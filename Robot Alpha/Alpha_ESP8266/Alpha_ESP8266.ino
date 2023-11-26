#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "pain";
const char* password = "pain1234";
const char* serverUrl = "http://192.168.1.4/my-api/gate.php";
const int ledPin = 5;  // Change this to the appropriate GPIO pin

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (checkGateStatus()) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    delay(5000);                 // Keep the LED on for 5 seconds
    digitalWrite(ledPin, LOW);   // Turn off the LED
  }
  delay(500);  // Delay between requests
}

bool checkGateStatus() {
  WiFiClient client;
  HTTPClient http;
  // Create the URL with the action parameter
  String url = String(serverUrl) + "?action=gate1";

  // Send GET request to the server
  if (http.begin(client, url)) {
    int httpResponseCode = http.GET();

    if (httpResponseCode == HTTP_CODE_OK) {
      String response = http.getString();
      Serial.println("Response: " + response);

      if (response == "true") {
        
        return true;
      }
    }
    http.end();
  }
  return false;
}