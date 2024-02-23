#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define RX_PIN 14  // Define RX pin
#define TX_PIN 12  // Define TX pin

SoftwareSerial espSerial(RX_PIN, TX_PIN,false); // Create a SoftwareSerial object


const char* ssid = "Hamdy";
const char* password = "Hamdy24@wifi";
const char* serverIP = "192.168.1.6"; // IP address of your local server
const int serverPort = 8001;

WiFiClient client;
// #define SERIAL_PORT Serial1 // Assuming your device is connected to Serial1

bool sequenceDetected = false;

uint8_t Buffer[200] ;

void setup() {
    Serial.begin(115200);
    espSerial.begin(115200); // Initialize Serial communication with your device

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(1000);

    if (client.connect(serverIP, serverPort)) {
        Serial.println("Connected to server");
        // Client will receive data from server
        while (client.connected() ) {
            while (client.available() > 0) {
              // while (!sequenceDetected) {
                // Read data from the server
                client.read(Buffer,6);
    
                for(int i =0; i<6;i++){
                  //  client.read(Buffer,1); 
                   espSerial.println(Buffer[i]);
                   Serial.println(Buffer[i]);
                }


                // Wait for response from the device
                while (espSerial.available() == 0) {
                    delay(10);
                }
                // Read response from the device
                if (espSerial.available()) { // Check if data is available from STM32 Bluepill
                    while (espSerial.available()) {
                      int responseFromDevice = espSerial.read(); // Read data from STM32 Bluepill
                       // Send response to the server
                      client.println(responseFromDevice);
                    }
                }
                // String responseFromDevice = (const char*)SERIAL_PORT.read();
               

            }
        }
        client.stop();
    } else {
        // Serial.println("Connection failed");
    }
}

void loop() {
    // Not used in this example
}


// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>

// const char* ssid = "pain";
// const char* password = "pain1234";
// const char* serverUrl = "http://192.168.1.4/my-api/gate.php";
// const int ledPin = 2;  // Change this to the appropriate GPIO pin

// uint8_t temp=0;


// void setup() {
//   pinMode(ledPin, OUTPUT);
//   Serial.begin(115200);
//   // // Connect to Wi-Fi
//   // WiFi.begin(ssid, password);
//   // while (WiFi.status() != WL_CONNECTED) {
//   //   delay(1000);
//   //   Serial.println("Connecting to WiFi...");
//   // }
//   // Serial.println("Connected to WiFi");
// }

// void loop() {

//   temp = Serial.read();
//   if((temp != -1 ) && (temp != 255)){
//     Serial.print((char)temp);
//   }

//   // if (checkGateStatus()) {
//     // digitalWrite(ledPin, HIGH);  // Turn on the LED
//     // delay(1000);                 // Keep the LED on for 5 seconds
//     // digitalWrite(ledPin, LOW);   // Turn off the LED
//     // delay(1000); 
//   // }
//   // delay(500);  // Delay between requests 
// }

// bool checkGateStatus() {
//   WiFiClient client;
//   HTTPClient http;
//   // Create the URL with the action parameter
//   String url = String(serverUrl) + "?action=gate1";

//   // Send GET request to the server
//   if (http.begin(client, url)) {
//     int httpResponseCode = http.GET();

//     if (httpResponseCode == HTTP_CODE_OK) {
//       String response = http.getString();
//       Serial.println("Response: " + response);

//       if (response == "true") {
        
//         return true;
//       }
//     }
//     http.end();
//   }
//   return false;
// }