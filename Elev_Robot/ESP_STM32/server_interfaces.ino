#include "server_configs.h"

void server_setup(){
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    DEBUG_SERIAL.println("Connecting to WiFi...");
  }
  DEBUG_SERIAL.println("Connected to WiFi");


}
bool server_status_check(){
  // connected or not?

  return false;
}
char server_check_request(){
  // server read
  // check msg received
  // return msg 
  return NULL;
}
void server_disconnect(){
  // off
}


int server_read_RobotState()
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


void server_update_RobotState(int new_robot2_state)
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


void server_receive(){
  // cleint read?
}
void server_send(){
  // client send?
}
