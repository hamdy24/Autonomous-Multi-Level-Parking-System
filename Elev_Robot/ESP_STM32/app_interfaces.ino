

void app_setup(){

   // Initialize serial communication
  DEBUG_SERIAL.begin(115200);
  STM_SERIAL.begin(115200);

  server_setup();
}


int charToInt(char a)
{
  return (a - '0');
}


char intToChar(int b)
{
  return (b + '0');
}



// sudo code
// setup

// in loop:
//      check server request?
//      if fota
//      ///// handle script
//      else
//      ///// 
//          check server request
//          if parking
//          ///// handle parking seq
//          else
//          ///// handle retrieve seq











