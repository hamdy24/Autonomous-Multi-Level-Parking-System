#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h> 

// #include <Crypto.h>
// #include <AES.h>
// ------------------- Robot 1&2 States ---------------------------------

#define START_PARKING               'B'
#define FINISH_PARKING              'C'

#define RECEIVED_OK                 'D'

#define PARKING_REQUEST             'E'  

#define FIRST_REKEB                 'F'
#define FIRST_HOME                  'G'

#define ARRIVED_INFRONTOF_SLOT      'H'
#define ARRIVED_AT_ENTRY            'I'
#define DONE_PARKING                'J'

#define IM_DONE                     'K'

#define RETRIEVAL_REQUEST           'L'
#define START_RETRIEVING            'M'
#define FINISH_RETRIEVING           'N'
#define DONE_RETREIVING             'O'

#define LIFTING_INIT                'U'
#define ELEV_INIT                   'V'


#define IDLE_STATE                  'W'
#define PENDING_STATE               'X'


#define ACK_SLOT_NUMBER             'Y'


#define DEBUG_SERIAL                Serial
#define STM_SERIAL                  espSerial

#define RX_PIN                      14  // Define RX pin
#define TX_PIN                      12  // Define TX pin

// ------------- Functions to get & update data from database 

int Http_Read_FirstRobotStatus(void);
void Http_Update_Robot2_Status(int new_robot2_state);
int Http_Read_ServerRequest();
void Http_Update_ServerRequest(int new_request);
int Http_Read_Slot_Number();


bool isUpdateAvailabe();
void handle_BootingUpdates();
void run_MainApplication_ELEV();

// -------------- Helper Functions

int charToInt(char a);
char intToChar(int b);

int robot1_state = 0;

bool isParking = false, isRetreiving = false;

WiFiClient client;
HTTPClient http;
SoftwareSerial STM_SERIAL(RX_PIN, TX_PIN, false);  // Create a SoftwareSerial object


const char* ssid = "hamdy";
const char* password = "pass1234";

const char* api_url = "http://192.168.43.120/my-api/amdy.php";
const char* serverIP = "192.168.18.146";  // IP address of your local server

const int serverPort = 8001;

uint8_t Get_Version_Flag = 0;





uint8_t Buffer[300];
uint8_t ServerDataLength[1];
uint8_t Payload_Terminator[1];
uint8_t STM_Response[300];
uint8_t Ack[1] = {0};




// byte key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};  // 16-byte key for AES-128
// AES aes;
// void encrypt(uint8_t* data, size_t len) {
//   for (size_t i = 0; i < len; i += 16) {
//     aes.encencryptBlock(data + i, key);
//   }
// }
// void decrypt(uint8_t* data, size_t len) {
//   for (size_t i = 0; i < len; i += 16) {
//     aes.decryptBlock(data + i, key);
//   }
// }





void setup() {

  pinMode(RX_PIN, INPUT);
  pinMode(TX_PIN, OUTPUT);

  Serial.begin(115200);

// TWO OPTIONS >>>>>>>>>>> 9600 AND 115200 VV

  STM_SERIAL.begin(9600);  

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

void loop() {
  // problem to solve >>>>> setup baudrate
  // if(isUpdateAvailabe()){
  //   handle_BootingUpdates();
  // }else{
  //   run_MainApplication_ELEV();
  // }

  if (client.connect(serverIP, serverPort)) {
    Serial.println("Connected to server");

    while (client.connected()) {
      while (client.available() > 0) {

        // Read data length from the server
        client.read(ServerDataLength, 1);
        // decrypt(ServerDataLength, 1);  // Decrypt the received data

        delay(2);

        while(ServerDataLength[0] == 0)
        {
          client.read(ServerDataLength, 1);
          // decrypt(ServerDataLength, 1);  // Decrypt the received data

          delay(2);
        }
        // 0x10 >>> get ver >> 16 dec
        // 0x16 >> write >> 22 dec
        // Fill the buffer with the data from the server (of length 'ServerDataLength[0]')
        client.read(Buffer, ServerDataLength[0]);
        // decrypt(Buffer, ServerDataLength[0]);  // Decrypt the received data



        if(Buffer[0] == '16' || Buffer[0] == 16  ){

          // Get Version
          Get_Version_Flag = 1;

        }
        // else if(Buffer[0] == 22 || Buffer[0] == '22'){

        //   // Write

        // }
        Serial.println("Hello Outside While");

        // We (ServerDataLength[0] --------------------

        STM_SERIAL.print(1);   // Connection Initiate

        char c = STM_SERIAL.read();
        while(c != 1 && c != '1' && c != 49)
        {
          c = STM_SERIAL.read();
          delay(2);
        }
        
        STM_SERIAL.write(ServerDataLength[0]); // send length to STM
        Serial.println(ServerDataLength[0]);  // For Debugging NodeMCU

        for (int i = 0; i < 200; i++) {
          STM_SERIAL.write(Buffer[i]);  // Loop to send the Buffer data to STM

          Serial.printf("-> Buffer of [%d]= ", i);
          Serial.println(Buffer[i]);  // For Debugging NodeMCU
        }



        if(!Get_Version_Flag)
          STM_SERIAL.read(STM_Response, 200);  // Read ACK from STM32 Bluepill
        
        for(int i=0; i<200; i++)
        {
          Serial.printf("STM_Response[%d]: ",i);
          Serial.println(STM_Response[i]);
        }

        delay(2);

        


        if(Get_Version_Flag)
        {
          STM_SERIAL.read(&STM_Response[0], 1);   // ACK, DataLength, Payload Status
        }else{
          STM_Response[0] = 205;   // This is Iftikasssssssssssssssaaaaaaaaaaaa
        }
        // STM_SERIAL.read(&STM_Response[0], 1);   // ACK, DataLength, Payload Status
        // while((int)(STM_Response[0]) != 205 && (int)(STM_Response[0]) != 171)
        // {
        //   STM_SERIAL.read(&STM_Response[0], 1); 
        //   delay(5);
        // }


        Serial.println("Passed STM_SERIAL Available");  // For Debugging NodeMCU
        Serial.println("Entered STM_SERIAL Loop to recieve");  // For Debugging NodeMCU


        // --------------------------

        if((int)(STM_Response[0]) == 205){   // 205 --> 0xCD
          // Serial.println("Received ACK");
          if(Get_Version_Flag)
          {
            STM_SERIAL.read(&STM_Response[1], 1);  // Read data length from STM32 Bluepill
            STM_SERIAL.read(&STM_Response[2],STM_Response[1]);  // Read data from STM32 Bluepill

          }else{
            STM_Response[1] = 1;
            STM_Response[2] = 1;
          }
          // Send response to the server which is usually of length 2 from bootloader
          for (int i = 0; i < (STM_Response[1] + 2); i++) {
            Serial.println(STM_Response[i]);
          }

          // encrypt(STM_Response, STM_Response[1] + 2);  // Encrypt the response
          // 2 --> Mimic ACK, Length
          client.write(STM_Response, STM_Response[1] + 2); // Send the byte array to the server
          }
          else if((int)(STM_Response[0]) == 171){

            // encrypt(STM_Response[0], 1);  // Encrypt the response
            client.print(STM_Response[0]);
            Serial.println("Received NACK");
          }else{

          }
          Serial.println(STM_Response[0]);
          for(int i=0; i<sizeof(STM_Response); i++)
          {
            STM_Response[i] = 0;
          }
          Get_Version_Flag = 0;


        if(Buffer[4] == 129) 
        {
          while(STM_SERIAL.available())
          {
            char c = Serial.read();
            Serial.print(c);
            delay(10);
          // }
          if(c == 'd'){
            break;
          }
          }
        }

        // Clear the buffer for further receive
        memset(Buffer, 0, sizeof(Buffer));


        for(int i=0; i<sizeof(Buffer); i++)
        {
          Buffer[i] = 0;
        }



      }
    }
    client.stop();
  } else {
    Serial.println("Connection failed");
  }
}

bool isUpdateAvailabe(){
////////////// Damn Switch
  return true;
}

void handle_BootingUpdates(){
    if (client.connect(serverIP, serverPort)) {
    Serial.println("Connected to server");

    while (client.connected()) {
      while (client.available() > 0) {

        // Read data length from the server
        client.read(ServerDataLength, 1);
        // decrypt(ServerDataLength, 1);  // Decrypt the received data

        delay(2);

        while(ServerDataLength[0] == 0)
        {
          client.read(ServerDataLength, 1);
          // decrypt(ServerDataLength, 1);  // Decrypt the received data

          delay(2);
        }
        // 0x10 >>> get ver >> 16 dec
        // 0x16 >> write >> 22 dec
        // Fill the buffer with the data from the server (of length 'ServerDataLength[0]')
        client.read(Buffer, ServerDataLength[0]);
        // decrypt(Buffer, ServerDataLength[0]);  // Decrypt the received data



        if(Buffer[0] == '16' || Buffer[0] == 16  ){

          // Get Version
          Get_Version_Flag = 1;

        }
        // else if(Buffer[0] == 22 || Buffer[0] == '22'){

        //   // Write

        // }
        Serial.println("Hello Outside While");

        // We (ServerDataLength[0] --------------------

        STM_SERIAL.print(1);   // Connection Initiate

        char c = STM_SERIAL.read();
        while(c != 1 && c != '1' && c != 49)
        {
          c = STM_SERIAL.read();
          delay(2);
        }
        
        STM_SERIAL.write(ServerDataLength[0]); // send length to STM
        Serial.println(ServerDataLength[0]);  // For Debugging NodeMCU

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


        if(!Get_Version_Flag)
          STM_SERIAL.read(STM_Response, 200);  // Read ACK from STM32 Bluepill
        
        for(int i=0; i<200; i++)
        {
          Serial.printf("STM_Response[%d]: ",i);
          Serial.println(STM_Response[i]);
        }

        delay(2);


        if(Get_Version_Flag)
        {
          STM_SERIAL.read(&STM_Response[0], 1);   // ACK, DataLength, Payload Status
        }else{
          STM_Response[0] = 205;   // This is Iftikasssssssssssssssaaaaaaaaaaaa
        }
        // STM_SERIAL.read(&STM_Response[0], 1);   // ACK, DataLength, Payload Status
        // while((int)(STM_Response[0]) != 205 && (int)(STM_Response[0]) != 171)
        // {
        //   STM_SERIAL.read(&STM_Response[0], 1); 
        //   delay(5);
        // }


        Serial.println("Passed STM_SERIAL Available");  // For Debugging NodeMCU
        Serial.println("Entered STM_SERIAL Loop to recieve");  // For Debugging NodeMCU


        // --------------------------

        if((int)(STM_Response[0]) == 205){   // 205 --> 0xCD
          // Serial.println("Received ACK");
          if(Get_Version_Flag)
          {
            STM_SERIAL.read(&STM_Response[1], 1);  // Read data length from STM32 Bluepill
            STM_SERIAL.read(&STM_Response[2],STM_Response[1]);  // Read data from STM32 Bluepill

          }else{
            STM_Response[1] = 1;
            STM_Response[2] = 1;
          }
          // Send response to the server which is usually of length 2 from bootloader
          for (int i = 0; i < (STM_Response[1] + 2); i++) {
            Serial.println(STM_Response[i]);
          }

          // encrypt(STM_Response, STM_Response[1] + 2);  // Encrypt the response
          // 2 --> Mimic ACK, Length
          client.write(STM_Response, STM_Response[1] + 2); // Send the byte array to the server
          }
          else if((int)(STM_Response[0]) == 171){

            // encrypt(STM_Response[0], 1);  // Encrypt the response
            client.print(STM_Response[0]);
            Serial.println("Received NACK");
          }else{

          }
          Serial.println(STM_Response[0]);
          for(int i=0; i<sizeof(STM_Response); i++)
          {
            STM_Response[i] = 0;
          }
          Get_Version_Flag = 0;

      }
    }
    client.stop();
  } else {
    Serial.println("Connection failed");
  }
}

void run_MainApplication_ELEV(){
    // Check if the STM is available for sending & receciving
  while (STM_SERIAL.available()) {

    Http_Update_Robot2_Status(charToInt(ELEV_INIT));

    robot1_state = intToChar(Http_Read_FirstRobotStatus());


    while(robot1_state != LIFTING_INIT){
      robot1_state = intToChar(Http_Read_FirstRobotStatus());
      delay(100);
    }


    char ServerRequest = intToChar(Http_Read_ServerRequest());

  
    STM_SERIAL.write(ServerRequest);
    DEBUG_SERIAL.print(ServerRequest);
    DEBUG_SERIAL.print(PARKING_REQUEST);

    while((ServerRequest != PARKING_REQUEST) && (ServerRequest != RETRIEVAL_REQUEST))
    {
      ServerRequest = intToChar(Http_Read_ServerRequest());
      DEBUG_SERIAL.println("Waiting for [Valid Server Request]");
      delay(100);
    }

    char SlotNumber = (Http_Read_Slot_Number()) + '0';


    while((SlotNumber < '1') || (SlotNumber > '6'))
    {
      SlotNumber = (Http_Read_Slot_Number()) + '0';
      DEBUG_SERIAL.println("Waiting for [Valid Slot Number]");
      delay(100);
    }

    // Should be updated from server
    if(ServerRequest == PARKING_REQUEST)
      isParking = true;
    else if(ServerRequest == RETRIEVAL_REQUEST)
      isRetreiving = true;

    STM_SERIAL.write(ServerRequest);
    DEBUG_SERIAL.print(ServerRequest);

    char c = STM_SERIAL.read();
    while(c != RECEIVED_OK){    // Wait till receiveing el ok
      STM_SERIAL.write(ServerRequest);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [RECEIVED_OK]");
      delay(100);
    }


    STM_SERIAL.write(SlotNumber);
    DEBUG_SERIAL.print("Sending Slot no.: ");
    DEBUG_SERIAL.println(SlotNumber);

    c = STM_SERIAL.read();
    while(c != ACK_SLOT_NUMBER){    // Wait till receiveing el ok
      STM_SERIAL.write(SlotNumber);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [ACK_SLOT_NUMBER]");
      delay(100);
    }

    
    char r = intToChar(Http_Read_FirstRobotStatus());     // Get First Robot state from Database
    while(r != FIRST_REKEB)
    {
      DEBUG_SERIAL.print("Waiting a [FIRST_REKEB] from DB");
      r = intToChar(Http_Read_FirstRobotStatus());
      delay(100);
    }
    STM_SERIAL.write(FIRST_REKEB);

    c = STM_SERIAL.read();
    while((c != START_PARKING) && (c != START_RETRIEVING)){    // Wait till receiveing el ok
      DEBUG_SERIAL.print("Sending a [FIRST_REKEB] Signal");
      STM_SERIAL.write(FIRST_REKEB);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.print(c);
      if(isParking)
        DEBUG_SERIAL.println("Waiting for [START_PARKING]");
      else if(isRetreiving)
        DEBUG_SERIAL.println("Waiting for [START_RETRIEVING]");
      delay(100);
    }

    if(isParking)
      Http_Update_Robot2_Status(charToInt(START_PARKING));
    else if(isRetreiving)
      Http_Update_Robot2_Status(charToInt(START_RETRIEVING));

    delay(800);   // Delay for waiting to arrive the desired slot
    
    c = STM_SERIAL.read();
    while(c != ARRIVED_INFRONTOF_SLOT){    // Wait till receiveing el ok
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [ARRIVED_INFRONTOF_SLOT]");
      delay(100);
    }
    Http_Update_Robot2_Status(charToInt(ARRIVED_INFRONTOF_SLOT));


    // delay(1000);   // Simulation of time taking to park the car

    if(isParking){
      DEBUG_SERIAL.print("Sending a [DONE_PARKING] Signal");
      DEBUG_SERIAL.println(DONE_PARKING);

      //Http_Update_Robot1_Status(charToInt(DONE_PARKING));   // As a simulation that this change done by the first robot
    }else if(isRetreiving){
      DEBUG_SERIAL.print("Sending a [DONE_RETREIVING] Signal");
      DEBUG_SERIAL.println(DONE_RETREIVING);

     // Http_Update_Robot1_Status(charToInt(DONE_RETREIVING));   // As a simulation that this change done by the first robot
    }
    

    r = intToChar(Http_Read_FirstRobotStatus());
    while(r != DONE_PARKING && r != DONE_RETREIVING)
    {
      r = intToChar(Http_Read_FirstRobotStatus());
      delay(100);
    }

    if(isParking)     
      STM_SERIAL.write(DONE_PARKING);  
    else if(isRetreiving)
      STM_SERIAL.write(DONE_RETREIVING); 

    // delay(1300);   // Delay for waiting to back to entry
    c = STM_SERIAL.read();
    while(c != ARRIVED_AT_ENTRY){    // Wait till receiveing el ok
      if(isParking)
        STM_SERIAL.write(DONE_PARKING);  
      else if(isRetreiving)
        STM_SERIAL.write(DONE_RETREIVING);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [ARRIVED_AT_ENTRY]");
      delay(100);
    }
    Http_Update_Robot2_Status(charToInt(ARRIVED_AT_ENTRY));
    
    // delay(1000);   // Delay to simulate first robot time to back to its home
    DEBUG_SERIAL.print("Sending a [FIRST_HOME] Signal");
    DEBUG_SERIAL.println(FIRST_HOME);

   // Http_Update_Robot1_Status(charToInt(FIRST_HOME));   // As a simulation that this change done by the first robot

    r = intToChar(Http_Read_FirstRobotStatus());
    while(r != FIRST_HOME)
    {
      r = intToChar(Http_Read_FirstRobotStatus());
      delay(100);
    }    
    STM_SERIAL.write(FIRST_HOME); 

    c = STM_SERIAL.read();
    while(c != FINISH_PARKING && c != FINISH_RETRIEVING){    // Wait till receiveing el ok
      STM_SERIAL.write(FIRST_HOME); 
      c = STM_SERIAL.read();
      if(isParking)
        DEBUG_SERIAL.println("Waiting for [FINISH_PARKING]");
      else if(isRetreiving)
        DEBUG_SERIAL.println("Waiting for [FINISH_RETRIEVING]");
      delay(100);
    }
    
    if(isParking)
      Http_Update_Robot2_Status(charToInt(FINISH_PARKING));
    else if(isRetreiving)
      Http_Update_Robot2_Status(charToInt(FINISH_RETRIEVING));

    //Http_Update_Robot1_Status(charToInt(IM_DONE));   // As a simulation that this change done by the first robot

    r = intToChar(Http_Read_FirstRobotStatus());
    while(r != IM_DONE)
    {
      r = intToChar(Http_Read_FirstRobotStatus());
      delay(100);
    }   
    STM_SERIAL.write(IM_DONE);

    if(isParking)
      DEBUG_SERIAL.println("Celebrating Done parking");
    else if(isRetreiving)
      DEBUG_SERIAL.println("Celebrating Done retrieving");
      
      
    Http_Update_ServerRequest(charToInt(IDLE_STATE));


    delay(2000); 
    isParking = false;
    isRetreiving = false;
    http.end();  
  }
}


int Http_Read_FirstRobotStatus()
{
  String action = "get_data";
  String payload = "action=" + action;

  //http.begin(client, api_url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send the POST request
  int httpResponseCode = http.POST(payload);
  int robot1_state = 0;

  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();
    Serial.print("Response: ");
    Serial.println(response);

    // Parse JSON response
    DynamicJsonDocument doc(512); // Adjust the buffer size as needed
    deserializeJson(doc, response);

    // Extract robot1_state
    robot1_state = doc["robot1_state"];
    DEBUG_SERIAL.print("Robot1 State: ");
    DEBUG_SERIAL.println(robot1_state);
    //http.end();  
  }

  return robot1_state;
}




int Http_Read_ServerRequest()
{
  String action = "get_data";
  String payload = "action=" + action;

  http.begin(client, api_url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send the POST request
  int httpResponseCode = http.POST(payload);
  int request = 0;

  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();
    Serial.print("Response: ");
    Serial.println(response);

    // Parse JSON response
    DynamicJsonDocument doc(512); // Adjust the buffer size as needed
    deserializeJson(doc, response);

    // Extract robot1_state
    request = doc["request"];
    DEBUG_SERIAL.print("Server Request: ");
    DEBUG_SERIAL.println(request);
    http.end();  
  }

  return request;
}



int Http_Read_Slot_Number()
{
  String action = "get_data";
  String payload = "action=" + action;

  http.begin(client, api_url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send the POST request
  int httpResponseCode = http.POST(payload);
  int request = 0;

  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();
    Serial.print("Response: ");
    Serial.println(response);

    // Parse JSON response
    DynamicJsonDocument doc(512); // Adjust the buffer size as needed
    deserializeJson(doc, response);

    // Extract robot1_state
    request = doc["slot_number"];
    DEBUG_SERIAL.print("Slot Number: ");
    DEBUG_SERIAL.println(request);
    http.end();  
  }

  return request;
}


void Http_Update_Robot2_Status(int new_robot2_state)
{
  String action = "update_robot2";
  String payload = "action=" + action + "&robot2_state=" + String(new_robot2_state) + "&version=" + String(3);

  //http.begin(client, api_url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send the POST request
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();
    Serial.print("Response: ");
    Serial.println(response);
  }

  //http.end();
}


void Http_Update_ServerRequest(int new_request)
{
  String action = "update_server_Request";
  String payload = "action=" + action + "&request=" + String(new_request);

  http.begin(client, api_url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send the POST request
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();
    DEBUG_SERIAL.print("Response: ");
    DEBUG_SERIAL.println(response);
  }

  http.end();
}

int charToInt(char a)
{
  return (a - 'A');
}


char intToChar(int b)
{
  return (b + 'A');
}




