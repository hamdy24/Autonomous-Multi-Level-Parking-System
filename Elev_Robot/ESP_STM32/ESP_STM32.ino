#include "app_configs.h"
#include "server_configs.h"


void Http_Update_Robot1_Status(int new_robot1_state); // currently for testing only and will be deleted

void setup() {
  app_setup();
}

void loop() {



  
  // Check if the STM is available for sending & receciving
  while (STM_SERIAL.available()) {
    // Should be updated from server
    char ServerRequest = RETRIEVAL_REQUEST;  // ---> Just change this in case of retrieving
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


    DEBUG_SERIAL.print("Sending a [FIRST_REKEB] Signal");
    DEBUG_SERIAL.println(FIRST_REKEB);

    Http_Update_Robot1_Status(charToInt(FIRST_REKEB));   // As a simulation that this change done by the first robot

    char r = intToChar(server_read_RobotState());     // Get First Robot state from Database
    while(r != FIRST_REKEB)
    {
      r = intToChar(server_read_RobotState());
      delay(100);
    }
    STM_SERIAL.write(FIRST_REKEB);

    c = STM_SERIAL.read();
    while((c != START_PARKING) && (c != START_RETRIEVING)){    // Wait till receiveing el ok
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
      server_update_RobotState(charToInt(START_PARKING));
    else if(isRetreiving)
      server_update_RobotState(charToInt(START_RETRIEVING));

    delay(800);   // Delay for waiting to arrive the desired slot
    
    c = STM_SERIAL.read();
    while(c != ARRIVED_INFRONTOF_SLOT){    // Wait till receiveing el ok
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [ARRIVED_INFRONTOF_SLOT]");
      delay(100);
    }
    server_update_RobotState(charToInt(ARRIVED_INFRONTOF_SLOT));


    delay(1000);   // Simulation of time taking to park the car

    if(isParking){
      DEBUG_SERIAL.print("Sending a [DONE_PARKING] Signal");
      DEBUG_SERIAL.println(DONE_PARKING);

      Http_Update_Robot1_Status(charToInt(DONE_PARKING));   // As a simulation that this change done by the first robot
    }else if(isRetreiving){
      DEBUG_SERIAL.print("Sending a [DONE_RETREIVING] Signal");
      DEBUG_SERIAL.println(DONE_RETREIVING);

      Http_Update_Robot1_Status(charToInt(DONE_RETREIVING));   // As a simulation that this change done by the first robot
    }
    

    r = intToChar(server_read_RobotState());
    while(r != DONE_PARKING && r != DONE_RETREIVING)
    {
      r = intToChar(server_read_RobotState());
      delay(100);
    }

    if(isParking)     
      STM_SERIAL.write(DONE_PARKING);  
    else if(isRetreiving)
      STM_SERIAL.write(DONE_RETREIVING); 

    delay(1300);   // Delay for waiting to back to entry
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
    server_update_RobotState(charToInt(ARRIVED_AT_ENTRY));
    
    delay(1000);   // Delay to simulate first robot time to back to its home
    DEBUG_SERIAL.print("Sending a [FIRST_HOME] Signal");
    DEBUG_SERIAL.println(FIRST_HOME);

    Http_Update_Robot1_Status(charToInt(FIRST_HOME));   // As a simulation that this change done by the first robot

    r = intToChar(server_read_RobotState());
    while(r != FIRST_HOME)
    {
      r = intToChar(server_read_RobotState());
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
      server_update_RobotState(charToInt(FINISH_PARKING));
    else if(isRetreiving)
      server_update_RobotState(charToInt(FINISH_RETRIEVING));

    Http_Update_Robot1_Status(charToInt(IM_DONE));   // As a simulation that this change done by the first robot

    r = intToChar(server_read_RobotState());
    while(r != IM_DONE)
    {
      r = intToChar(server_read_RobotState());
      delay(100);
    }   
    STM_SERIAL.write(IM_DONE);

    if(isParking)
      DEBUG_SERIAL.println("Celebrating Done parking");
    else if(isRetreiving)
      DEBUG_SERIAL.println("Celebrating Done retrieving");

    delay(2000); 
    isParking = false;
    isRetreiving = false;
  }
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

