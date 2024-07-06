#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h> // Include ArduinoJson library

// Liftiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiinnnnnnnnnnnnnngggggggggg

#define START_PARKING       'B'
#define FINISH_PARKING        'C'

#define RECEIVED_OK         'D'

#define PARKING_REQUEST       'E'

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

#define CAR_ARRIVED       'P'

// commit


#define ACK_STARTING      'Q'
#define ACK_DONE        'R'
#define ACK_CAR_ARRIVED       'S'
#define ACK_ARIV_AT_SLOT    'T'


#define LIFTING_INIT    'U'
#define ELEV_INIT     'V'

#define IDLE_STATE    'W'
#define PENDING_STATE    'X'



int charToInt(char a);
char intToChar(int b);
int Http_Read_SecondRobotStatus();
void Http_Update_Robot1_Status(int new_robot1_state);
void Http_Update_ServerRequest(int new_request);
int Http_Read_ServerRequest();

#define RX_PIN 14  // ---> D5
#define TX_PIN 12  // ---> D6

SoftwareSerial mySerial(RX_PIN, TX_PIN);

#define DEBUG_SERIAL          Serial
#define STM_SERIAL          mySerial
char Buffer[22] = {0};

char c;
int i=0;
const char* ssid = "ZagSystems";
const char* password = "0553664875";
const char* api_url = "http://192.168.0.103/my-api/amdy.php";

// Thouggggggggggggggggggggggggggggggggggghhhhhhhhhhhhhhhhhhhtssss

// ------------- Make our process a critical section
// ------------- Reconsider delays in the esp codesssssssssss


const int ledPin = 5; 

int robot2_state = 0;

void setup() {
  // Initialize serial communication
  DEBUG_SERIAL.begin(115200);
  STM_SERIAL.begin(115200);
   pinMode(ledPin, OUTPUT); // Set the LED pin as an output

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    DEBUG_SERIAL.println("Connecting to WiFi...");
  }
  DEBUG_SERIAL.println("Connected to WiFi");


}
 WiFiClient client;
HTTPClient http;


void loop() {
  while (STM_SERIAL.available()) {

    Http_Update_Robot1_Status(charToInt(LIFTING_INIT));

    robot2_state = intToChar(Http_Read_SecondRobotStatus());

    while(robot2_state != ELEV_INIT){
      robot2_state = intToChar(Http_Read_SecondRobotStatus());
      delay(100);
    }

    char ServerRequest = intToChar(Http_Read_ServerRequest());

    DEBUG_SERIAL.print(ServerRequest);

    while((ServerRequest != PARKING_REQUEST) && (ServerRequest != RETRIEVAL_REQUEST))
    {
      ServerRequest = intToChar(Http_Read_ServerRequest());
      DEBUG_SERIAL.println("Waiting for [Valid Server Request]");
      delay(100);
    }

    STM_SERIAL.write(ServerRequest);

    c = STM_SERIAL.read();
    while(c != RECEIVED_OK){    // Wait till receiveing el ok
      STM_SERIAL.write(ServerRequest);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [RECEIVED_OK]");
      delay(100);    
    }
              
    c = STM_SERIAL.read();
    while(c != CAR_ARRIVED){    // Wait till receiveing el ok
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [CAR_ARRIVED]");
      delay(100);
    }
               
    DEBUG_SERIAL.print("Sending a [ACK_CAR_ARRIVED] Signal");
    STM_SERIAL.write(ACK_CAR_ARRIVED);

    c = STM_SERIAL.read();
    while(c != FIRST_REKEB){    // Wait till receiveing el ok
      STM_SERIAL.write(ACK_CAR_ARRIVED);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [FIRST_REKEB]");
      delay(100);
    }
                   
    Http_Update_Robot1_Status(charToInt(FIRST_REKEB));

    DEBUG_SERIAL.println("Sending a [START_PARKING] Signal");
    STM_SERIAL.write(START_PARKING);

    c = STM_SERIAL.read();
    while(c != ACK_STARTING){    // Wait till receiveing el ok
      STM_SERIAL.write(START_PARKING);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [ACK_STARTING]");
      delay(100);
    }

    delay(1300);

    robot2_state = intToChar(Http_Read_SecondRobotStatus());
    while(robot2_state != ARRIVED_INFRONTOF_SLOT)
    {
      robot2_state = intToChar(Http_Read_SecondRobotStatus());
      DEBUG_SERIAL.println("Waiting for [ARRIVED_INFRONTOF_SLOT]");
      delay(100);
    }

    DEBUG_SERIAL.println("Sending a [ARRIVED_INFRONTOF_SLOT] Signal");
    STM_SERIAL.write(ARRIVED_INFRONTOF_SLOT);

    c = STM_SERIAL.read();
    while(c != DONE_PARKING){    // Wait till receiveing el ok
      STM_SERIAL.write(ARRIVED_INFRONTOF_SLOT);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [DONE_PARKING]");
      delay(100);
    }
            
    Http_Update_Robot1_Status(charToInt(DONE_PARKING));
    
    delay(1000);

    robot2_state = intToChar(Http_Read_SecondRobotStatus());
    while(robot2_state != ARRIVED_AT_ENTRY)
    {
      robot2_state = intToChar(Http_Read_SecondRobotStatus());
      DEBUG_SERIAL.println("Waiting for [ARRIVED_AT_ENTRY]");
      delay(100);
    }
          
    DEBUG_SERIAL.println("Sending a [ARRIVED_AT_ENTRY] Signal");
    STM_SERIAL.write(ARRIVED_AT_ENTRY);

    c = STM_SERIAL.read();
    while(c != FIRST_HOME){    // Wait till receiveing el ok
      STM_SERIAL.write(ARRIVED_AT_ENTRY);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [FIRST_HOME]");
      delay(100);
    }

    Http_Update_Robot1_Status(charToInt(FIRST_HOME));
              
    robot2_state = intToChar(Http_Read_SecondRobotStatus());
    while(robot2_state != FINISH_PARKING)
    {
      robot2_state = intToChar(Http_Read_SecondRobotStatus());
      DEBUG_SERIAL.println("Waiting for [FINISH_PARKING]");
      delay(100);
    }

    DEBUG_SERIAL.println("Sending a [FINISH_PARKING] Signal");
    STM_SERIAL.write(FINISH_PARKING);

    c = STM_SERIAL.read();
    while(c != IM_DONE){    // Wait till receiveing el ok
      STM_SERIAL.write(FINISH_PARKING);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [IM_DONE]");
      delay(100);
    }

    Http_Update_Robot1_Status(charToInt(IM_DONE));

    STM_SERIAL.write(ACK_DONE);


    DEBUG_SERIAL.println("Celebrating Done parking");

    Http_Update_ServerRequest(charToInt(IDLE_STATE));

    delay(2000); 

    }
  
}


int Http_Read_SecondRobotStatus()
{
  String action = "get_data";
  String payload = "action=" + action;

  http.begin(client, api_url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send the POST request
  int httpResponseCode = http.POST(payload);
  int robot2_state = 0;

  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();
    Serial.print("Response: ");
    Serial.println(response);

    // Parse JSON response
    DynamicJsonDocument doc(512); // Adjust the buffer size as needed
    deserializeJson(doc, response);

    // Extract robot1_state
    robot2_state = doc["robot2_state"];
    DEBUG_SERIAL.print("Robot2 State: ");
    DEBUG_SERIAL.println(robot2_state);
    http.end();  
  }

  return robot2_state;
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
