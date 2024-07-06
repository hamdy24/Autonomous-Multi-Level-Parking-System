#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h> // Include ArduinoJson library

// --------------------- Wifi configuration ----------------------------

const char* ssid = "ZagSystems";
const char* password = "0553664875";
const char* api_url = "http://192.168.0.103/my-api/amdy.php";

WiFiClient client;
HTTPClient http;

// commit

bool isParking = false, isRetreiving = false;


// ------------------- Robot 1&2 States ---------------------------------

#define START_PARKING       'B'
#define FINISH_PARKING        'C'

#define RECEIVED_OK         'D'

#define PARKING_REQUEST       'E'  // For now, mapping to 1 in DB.

#define FIRST_REKEB         'F'
#define FIRST_HOME          'G'

#define ARRIVED_INFRONTOF_SLOT    'H'
#define ARRIVED_AT_ENTRY      'I'
#define DONE_PARKING        'J'

#define IM_DONE               'K'

#define RETRIEVAL_REQUEST     'L'
#define START_RETRIEVING       'M'
#define FINISH_RETRIEVING        'N'
#define DONE_RETREIVING     'O'

#define LIFTING_INIT    'U'
#define ELEV_INIT     'V'


#define IDLE_STATE    'W'
#define PENDING_STATE    'X'


#define ACK_SLOT_NUMBER 'Y'


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
int Http_Read_ServerRequest();
void Http_Update_ServerRequest(int new_request);
int Http_Read_Slot_Number();
//void Http_Update_Robot1_Status(int new_robot1_state);

// -------------- Helper Functions

int charToInt(char a);
char intToChar(int b);

int robot1_state = 0;

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

  http.begin(client, api_url);

  

}



// ------------ Main loop

void loop() {
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




// void Http_Update_Robot1_Status(int new_robot1_state)
// {
//   String action = "update_robot1";
//   String payload = "action=" + action + "&robot1_state=" + String(new_robot1_state) + "&version=" + String(3);

//   http.begin(client, api_url);
//   http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
//   // Send the POST request
//   int httpResponseCode = http.POST(payload);

//   if (httpResponseCode == HTTP_CODE_OK) {
//     String response = http.getString();
//     DEBUG_SERIAL.print("Response: ");
//     DEBUG_SERIAL.println(response);
//   }

//   http.end();
// }



int charToInt(char a)
{
  return (a - 'A');
}


char intToChar(int b)
{
  return (b + 'A');
}



