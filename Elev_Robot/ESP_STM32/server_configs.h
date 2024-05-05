#ifndef SERVER_CONFIGS_H
#define SERVER_CONFIGS_H


int server_read_RobotState(void);

void server_update_RobotState(int new_robot2_state);


const char* ssid = "Suiiiii";
const char* password = "754764834Suiiiiiiii";
const char* api_url = "http://192.168.1.5/my-api/amdy.php";

WiFiClient client;
HTTPClient http;


#endif //SERVER_CONFIGS_H









