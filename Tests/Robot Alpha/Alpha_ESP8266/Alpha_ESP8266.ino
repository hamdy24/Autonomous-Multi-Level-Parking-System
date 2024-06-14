#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define RX_PIN 14  // Define RX pin
#define TX_PIN 12  // Define TX pin

SoftwareSerial espSerial(RX_PIN, TX_PIN, false);  // Create a SoftwareSerial object


const char* ssid = "Hamdy";
const char* password = "Hamdy24@wifi";
const char* serverIP = "192.168.1.6";  // IP address of your local server
const int serverPort = 8001;

WiFiClient client;
// #define SERIAL_PORT Serial1 // Assuming your device is connected to Serial1

// bool sequenceDetected = false;

uint8_t Buffer[200];
uint8_t ServerDataLength[1];
uint8_t STM_Response[200];
uint8_t Ack[1] = {0};
void setup() {

  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);

  Serial.begin(115200);
  espSerial.begin(115200);  // Initialize Serial communication with your device

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(1000);

  espSerial.print(1);
  // while (espSerial.available() == 0) {
  // }

  // while(  (Ack[0] != 1)  || (Ack[0] != '1') ){
  //   espSerial.read(Ack , 1);
  // }
}

void loop() {

  if (client.connect(serverIP, serverPort)) {
    Serial.println("Connected to server");
  // while(espSerial.available() == 0){
  //   // nothing
  // }

  // if(espSerial.available()){
  // while(((Ack[0] != 1)  || (Ack[0] != '1')) ){
  //   espSerial.read(Ack , 1);
  // }
  // }
    // Client will receive data from server
    while (client.connected()) {
      while (client.available() > 0) {

        // Read data length from the server
        client.read(ServerDataLength, 1);
        delay(10);

        // Fill the buffer with the data from the server (of length 'ServerDataLength[0]')
        client.read(Buffer, ServerDataLength[0]);

        
        espSerial.write(ServerDataLength[0]); // send length to STM
        Serial.println(ServerDataLength[0]);  // For Debugging NodeMCU
        // Serial.swap(12);

        for (int i = 0; i < 5; i++) {
          
          espSerial.write(Buffer[i]);  // Loop to send the Buffer data to STM

          Serial.printf("-> Buffer of [%d]= ", i);
          Serial.println(Buffer[i]);  // For Debugging NodeMCU
        }

        delay(10);
        //Wait for response from the device
        while (espSerial.available() == 0) {
            // delay(10);
            // Serial.println("Wait for response from the device"); // For Debugging NodeMCU
        }
        // Read response from the device
        // if (espSerial.available()) {  // Check if data is available from STM32 Bluepill

          Serial.println("Passed espSerial Available");  // For Debugging NodeMCU

          // while (espSerial.available()) {

            Serial.println("Entered espSerial Loop to recieve");  // For Debugging NodeMCU

            espSerial.read(STM_Response, 1);  // Read ACK from STM32 Bluepill

            if((int)(STM_Response[0]) == 205){
              Serial.println("Received ACK");
              espSerial.read(&STM_Response[1], 1);  // Read data length from STM32 Bluepill
              // Send response to the server which is usually of length 2 from bootloader
              for (int i = 0; i < STM_Response[1]; i++) {
                espSerial.read(&STM_Response[2],STM_Response[1] );  // Read data from STM32 Bluepill

                Serial.println(STM_Response[i]);
                client.print(STM_Response[i]);
              }

            }
            else if((int)(STM_Response[0]) == 171){
              client.print(STM_Response[0]);
              Serial.println("Received NACK");
            }
            Serial.println(STM_Response[0]);
          // }
          // }
        // }
      }
    }
    client.stop();
  } else {
    Serial.println("Connection failed");
  }
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