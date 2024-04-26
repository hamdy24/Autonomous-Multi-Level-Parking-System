#include <SoftwareSerial.h>

#define START_PARKING				'4'
#define FINISH_PARKING				'2'


#define RECEIVED_OK					'2'



#define PARKING_REQUEST				'5'
#define RETRIEVAL_REQUEST			'6'

#define FIRST_REKEB					'3'
#define FIRST_HOME					'3'

#define ARRIVED_INFRONTOF_SLOT		'7'
#define	ARRIVED_AT_ENTRY			'4'
#define DONE_PARKING				'9'

#define IM_DONE               '8'


/*
#define START_PARKING				'S'
#define FINISH_PARKING				'F'


#define RECEIVED_OK					'O'



#define PARKING_REQUEST				'P'
#define RETRIEVAL_REQUEST			'R'

#define FIRST_REKEB					'K'
#define FIRST_HOME					'H'

#define ARRIVED_INFRONTOF_SLOT		'A'
#define	ARRIVED_AT_ENTRY			'E'
#define DONE_PARKING				'D'

#define IM_DONE               'I'
*/

#define RX_PIN 14  // ---> D5
#define TX_PIN 12  // ---> D6

SoftwareSerial mySerial(RX_PIN, TX_PIN);


#define DEBUG_SERIAL          Serial
#define STM_SERIAL          mySerial


char Buffer[22] = {0};
int i=0;


void setup() {
  // Initialize serial communication
  DEBUG_SERIAL.begin(115200);
  STM_SERIAL.begin(115200);
}

void loop() {
  // Your main loop code here
  // This code will execute continuously
  while (STM_SERIAL.available()) {
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
    STM_SERIAL.write(FIRST_REKEB);

    c = STM_SERIAL.read();
    while(c != START_PARKING){    // Wait till receiveing el ok
      STM_SERIAL.write(FIRST_REKEB);
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [START_PARKING]");
      delay(100);
    }

    delay(800);   // Delay for waiting to arrive the desired slot
    
    c = STM_SERIAL.read();
    while(c != ARRIVED_INFRONTOF_SLOT){    // Wait till receiveing el ok
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [ARRIVED_INFRONTOF_SLOT]");
      delay(100);
    }

    delay(1000);   // Simulation of time taking to park the car
    DEBUG_SERIAL.print("Sending a [DONE_PARKING] Signal");
    DEBUG_SERIAL.println(DONE_PARKING);     
    STM_SERIAL.write(DONE_PARKING);  

    delay(1300);   // Delay for waiting to back to entry
    c = STM_SERIAL.read();
    while(c != ARRIVED_AT_ENTRY){    // Wait till receiveing el ok
      STM_SERIAL.write(DONE_PARKING);  
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [ARRIVED_AT_ENTRY]");
      delay(100);
    }
    delay(1000);   // Delay to simulate first robot time to back to its home
    DEBUG_SERIAL.print("Sending a [FIRST_HOME] Signal");
    DEBUG_SERIAL.println(FIRST_HOME);
    STM_SERIAL.write(FIRST_HOME); 

    c = STM_SERIAL.read();
    while(c != FINISH_PARKING){    // Wait till receiveing el ok
      STM_SERIAL.write(FIRST_HOME); 
      c = STM_SERIAL.read();
      DEBUG_SERIAL.println("Waiting for [FINISH_PARKING]");
      delay(100);
    }
    STM_SERIAL.write(IM_DONE);
    DEBUG_SERIAL.println("Celebrating Done parking");

    delay(2000); 
  }
}



// ----------------- Test Succeeded inside STM_SERIAL.available() inside loop()
/*void loop()
{
if(STM_SERIAL.available())
{
  STM_SERIAL.write('S');
  STM_SERIAL.write('H');
  char c = STM_SERIAL.read();
  while(c != 'Z'){
    c = STM_SERIAL.read();
    delay(100);
  }
  for(i=0; i<23; i++)
  {
    Buffer[i] = STM_SERIAL.read();
    DEBUG_SERIAL.print(Buffer[i]);
  }
  
  }
}*/

// --------------------------------------------------------------







