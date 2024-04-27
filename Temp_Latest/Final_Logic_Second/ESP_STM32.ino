#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h> // Include ArduinoJson library

// --------------------- Wifi configuration ----------------------------

const char* ssid = "Bruuuuhhhhhhhhh";
const char* password = "Suiiiiiiiiiiii";
const char* api_url = "http://192.168.1.2/my-api/amdy.php";

WiFiClient client;
HTTPClient http;


// ------------------- Robot 1&2 States ---------------------------------

#define START_PARKING       '4'
#define FINISH_PARKING        '2'

#define RECEIVED_OK         '2'

#define PARKING_REQUEST       '5'
#define RETRIEVAL_REQUEST     '6'

#define FIRST_REKEB         '3'
#define FIRST_HOME          '3'

#define ARRIVED_INFRONTOF_SLOT    '7'
#define ARRIVED_AT_ENTRY      '4'
#define DONE_PARKING        '9'

#define IM_DONE               '8'

#define DEBUG_SERIAL          Serial
#define STM_SERIAL          mySerial

// --------------------- Software Serial configuration --------------------

#define RX_PIN 14  // ---> D5
#define TX_PIN 12  // ---> D6

SoftwareSerial mySerial(RX_PIN, TX_PIN);


// ----------------------- Prototypes -------------------------------------

// ------------- Functions to get & update data from database 

int Http_Read_FirstRobotStatus(void);
void Http_Update_Robot2_Status(int new_robot2_state);
void Http_Update_Robot1_Status(int new_robot1_state);

// -------------- Helper Functions

int charToInt(char a);
char intToChar(int b);

// --------------- Setup

void setup() {
  // Initialize serial communication
  DEBUG_SERIAL.begin(115200);
  STM_SERIAL.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    DEBUG_SERIAL.println("Connecting to WiFi...");
  }
  DEBUG_SERIAL.println("Connected to WiFi");
}



// ------------ Main loop

void loop() {
  // Check if the STM is available for sending & receciving
  while (STM_SERIAL.available()) {
    // Should be updated from server
    STM_SERIAL.write(PARKING_REQUEST);
    DEBUG_SERIAL.print(PARKING_REQUEST);
    char c = STM_SERIAL.read();
    while(c != RECEIVED_OK){    // Wait till receiveing el ok
      STM_SERIAL.write(PARKING_REQUEST);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [RECEIVED_OK]");
      delay(100);
    }


    DEBUG_SERIAL.print("Sending a [FIRST_REKEB] Signal");
    DEBUG_SERIAL.println(FIRST_REKEB);

    Http_Update_Robot1_Status(charToInt(FIRST_REKEB));   // As a simulation that this change done by the first robot

    char r = intToChar(Http_Read_FirstRobotStatus());     // Get First Robot state from Database
    while(r != FIRST_REKEB)
    {
      r = intToChar(Http_Read_FirstRobotStatus());
      delay(100);
    }
    STM_SERIAL.write(FIRST_REKEB);

    c = STM_SERIAL.read();
    while(c != START_PARKING){    // Wait till receiveing el ok
      STM_SERIAL.write(FIRST_REKEB);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [START_PARKING]");
      delay(100);
    }
    Http_Update_Robot2_Status(charToInt(START_PARKING));

    delay(800);   // Delay for waiting to arrive the desired slot
    
    c = STM_SERIAL.read();
    while(c != ARRIVED_INFRONTOF_SLOT){    // Wait till receiveing el ok
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [ARRIVED_INFRONTOF_SLOT]");
      delay(100);
    }
    Http_Update_Robot2_Status(charToInt(ARRIVED_INFRONTOF_SLOT));


    delay(1000);   // Simulation of time taking to park the car
    DEBUG_SERIAL.print("Sending a [DONE_PARKING] Signal");
    DEBUG_SERIAL.println(DONE_PARKING);

    Http_Update_Robot1_Status(charToInt(DONE_PARKING));   // As a simulation that this change done by the first robot

    r = intToChar(Http_Read_FirstRobotStatus());
    while(r != DONE_PARKING)
    {
      r = intToChar(Http_Read_FirstRobotStatus());
      delay(100);
    }     
    STM_SERIAL.write(DONE_PARKING);  

    delay(1300);   // Delay for waiting to back to entry
    c = STM_SERIAL.read();
    while(c != ARRIVED_AT_ENTRY){    // Wait till receiveing el ok
      STM_SERIAL.write(DONE_PARKING);  
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [ARRIVED_AT_ENTRY]");
      delay(100);
    }
    Http_Update_Robot2_Status(charToInt(ARRIVED_AT_ENTRY));
    
    delay(1000);   // Delay to simulate first robot time to back to its home
    DEBUG_SERIAL.print("Sending a [FIRST_HOME] Signal");
    DEBUG_SERIAL.println(FIRST_HOME);

    Http_Update_Robot1_Status(charToInt(FIRST_HOME));   // As a simulation that this change done by the first robot

    r = intToChar(Http_Read_FirstRobotStatus());
    while(r != FIRST_HOME)
    {
      r = intToChar(Http_Read_FirstRobotStatus());
      delay(100);
    }    
    STM_SERIAL.write(FIRST_HOME); 

    c = STM_SERIAL.read();
    while(c != FINISH_PARKING){    // Wait till receiveing el ok
      STM_SERIAL.write(FIRST_HOME); 
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [FINISH_PARKING]");
      delay(100);
    }
    Http_Update_Robot2_Status(charToInt(FINISH_PARKING));

    Http_Update_Robot1_Status(charToInt(IM_DONE));   // As a simulation that this change done by the first robot

    r = intToChar(Http_Read_FirstRobotStatus());
    while(r != IM_DONE)
    {
      r = intToChar(Http_Read_FirstRobotStatus());
      delay(100);
    }   
    STM_SERIAL.write(IM_DONE);
    DEBUG_SERIAL.println("Celebrating Done parking");

    delay(2000); 
  }
}


int Http_Read_FirstRobotStatus()
{
  String action = "get_data";
  String payload = "action=" + action;

  http.begin(client, api_url);
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
    http.end();
  }

  return robot1_state;
}


void Http_Update_Robot2_Status(int new_robot2_state)
{
  String action = "update_robot2";
  String payload = "action=" + action + "&robot2_state=" + String(new_robot2_state) + "&version=" + String(3);

  http.begin(client, api_url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send the POST request
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();
    Serial.print("Response: ");
    Serial.println(response);
  }

  http.end();
}




void Http_Update_Robot1_Status(int new_robot1_state)
{
  String action = "update_robot1";
  String payload = "action=" + action + "&robot1_state=" + String(new_robot1_state) + "&version=" + String(3);

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
  return (a - '0');
}


char intToChar(int b)
{
  return (b + '0');
}
