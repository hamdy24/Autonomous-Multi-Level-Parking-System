#ifndef APP_CONFIGS_H
#define APP_CONFIGS_H


#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h> // Include ArduinoJson library



int charToInt(char a);
char intToChar(int b);


// ------------------- Robot 1&2 States ---------------------------------
#define START_PARKING       'U'
#define FINISH_PARKING        'B'

#define RECEIVED_OK         'C'

#define PARKING_REQUEST       'D'

#define FIRST_REKEB         'F'
#define FIRST_HOME          'G'

#define ARRIVED_INFRONTOF_SLOT    'H'
#define ARRIVED_AT_ENTRY      'I'
#define DONE_PARKING        'J'

#define IM_DONE               'K'

#define RETRIEVAL_REQUEST     'E'
#define START_RETRIEVING       'L'
#define FINISH_RETRIEVING        'M'
#define DONE_RETREIVING     'N'


#define DEBUG_SERIAL          Serial
#define STM_SERIAL          mySerial

// --------------------- Software Serial configuration --------------------

#define RX_PIN 14  // ---> D5
#define TX_PIN 12  // ---> D6

bool isParking = false, isRetreiving = false;
SoftwareSerial mySerial(RX_PIN, TX_PIN);


#endif //APP_CONFIGS_H
