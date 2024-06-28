#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define RX_PIN 14  // Define RX pin
#define TX_PIN 12  // Define TX pin


#define STM_SERIAL espSerial

SoftwareSerial STM_SERIAL(RX_PIN, TX_PIN, false);  // Create a SoftwareSerial object


const char* ssid = "Orange-9ptg";
const char* password = "75934821Aa@";
const char* serverIP = "192.168.1.9";  // IP address of your local server
const int serverPort = 8001;

WiFiClient client;





uint8_t Buffer[300];
uint8_t ServerDataLength[1];
uint8_t Payload_Terminator[1];
uint8_t STM_Response[300];
uint8_t Ack[1] = {0};
void setup() {

  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);

  Serial.begin(115200);
  STM_SERIAL.begin(115200);  // Initialize Serial communication with your device

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(1000);

}

// Data from server is correct only for the first iter



void loop() {
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Connected to server");

    while (client.connected()) {
      while (client.available() > 0) {

        // Read data length from the server
        client.read(ServerDataLength, 1);
        delay(10);

        while(ServerDataLength[0] == 0)
        {
          client.read(ServerDataLength, 1);
          delay(10);
        }

        // Fill the buffer with the data from the server (of length 'ServerDataLength[0]')
        client.read(Buffer, ServerDataLength[0]);
        Serial.println("Hello Outside While");

        // We (ServerDataLength[0] --------------------

        STM_SERIAL.print(1);   // Connection Initiate

        char c = STM_SERIAL.read();
        while(c != 1 && c != '1' && c != 49)
        {
          c = STM_SERIAL.read();
          delay(10);
        }
        
        STM_SERIAL.write(ServerDataLength[0]); // send length to STM
        Serial.println(ServerDataLength[0]);  // For Debugging NodeMCU
        // Serial.swap(12);

        for (int i = 0; i < 200; i++) {
          STM_SERIAL.write(Buffer[i]);  // Loop to send the Buffer data to STM

          Serial.printf("-> Buffer of [%d]= ", i);
          Serial.println(Buffer[i]);  // For Debugging NodeMCU
        }

        // Clear the buffer for further receive
        memset(Buffer, 0, sizeof(Buffer));


        for(int i=0; i<sizeof(Buffer); i++)
        {
          Buffer[i] = 0;
        }


                
        STM_SERIAL.read(STM_Response, 200);  // Read ACK from STM32 Bluepill
        
        for(int i=0; i<200; i++)
        {
          Serial.printf("STM_Response[%d]: ",i);
          Serial.println(STM_Response[i]);
        }

        delay(10);

        // STM_SERIAL.read(&STM_Response[0], 1);   // ACK, DataLength, Payload Status
        // while((int)(STM_Response[0]) != 205 && (int)(STM_Response[0]) != 171)
        // {
        //   STM_SERIAL.read(&STM_Response[0], 1); 
        //   delay(5);
        // }


        Serial.println("Passed STM_SERIAL Available");  // For Debugging NodeMCU
        Serial.println("Entered STM_SERIAL Loop to recieve");  // For Debugging NodeMCU


        // --------------------------
        STM_Response[0] = 205;   // This is Iftikasssssssssssssssaaaaaaaaaaaa

        if((int)(STM_Response[0]) == 205){   // 205 --> 0xCD
          // Serial.println("Received ACK");
          // STM_SERIAL.read(&STM_Response[1], 1);  // Read data length from STM32 Bluepill
          STM_Response[1] = 1;
          // Send response to the server which is usually of length 2 from bootloader
          // STM_SERIAL.read(&STM_Response[2],STM_Response[1]);  // Read data from STM32 Bluepill
          STM_Response[2] = 1;
          for (int i = 0; i < (STM_Response[1] + 2); i++) {
            Serial.println(STM_Response[i]);
          }

          // 2 --> Mimic ACK, Length
          client.write(STM_Response, STM_Response[1] + 2); // Send the byte array to the server
          }
          else if((int)(STM_Response[0]) == 171){
            client.print(STM_Response[0]);
            Serial.println("Received NACK");
          }else{

          }
          Serial.println(STM_Response[0]);
          for(int i=0; i<sizeof(STM_Response); i++)
          {
            STM_Response[i] = 0;
          }
          // client.read(Payload_Terminator, 1);
          // Serial.print("Payload_Terminator: ");
          // Serial.println(Payload_Terminator[0]);

          // if(Payload_Terminator[0] == '#')
          // {
          //   // Jump to the application
          //   STM_SERIAL.write(Payload_Terminator[0]);
          // }else if(Payload_Terminator[0] == '&')
          // {
          //   STM_SERIAL.write(Payload_Terminator[0]);
          // }else{
          //   Serial.println("Payload Fullllllll offfff Shittttttttttttt");
          //   STM_SERIAL.write(Payload_Terminator[0]);
          // }

      }
    }
    client.stop();
  } else {
    Serial.println("Connection failed");
  }
}







