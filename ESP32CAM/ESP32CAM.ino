
// ==================================== Includes ========================================== //

#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"

// ====================== CAMERA_MODEL_AI_THINKER GPIO Configuration ====================== //

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22


// LED Flash PIN (GPIO 4)
#define FLASH_LED_PIN     4             


// ==================================== Variables ========================================== //

// Network Credentials
const char* ssid = "Orange-9ptg";
const char* password = "75934821Aa@";

// Variables for Timer/Millis.
unsigned long previousMillis = 0; 
const int Interval = 20000; //--> Photo capture every 20 seconds.

// Server Address or Server IP.
String serverName = "192.168.1.3";  // IPV4 using ipconfig from command line.

// The file path "upload_img.php" on the server folder.
String serverPath = "/ESP32CAM/upload_img.php";
// Server Port.
const int serverPort = 80;

// Lighting up when capturing photo.
bool LED_Flash_ON = true;

// Initialize WiFiClient.
WiFiClient client;


/*******************************************************************************************
 @breif: Sending a photo taken by camera to server
 @params: none
 @return: none
*******************************************************************************************/

void sendPhotoToServer() {
  String AllData;
  String DataBody;

  Serial.println();
  Serial.println("-----------");
 
  // ====================================== Taking A photo ================================== //

  Serial.println("Taking a photo...");

  if (LED_Flash_ON == true) {
    digitalWrite(FLASH_LED_PIN, HIGH);
    delay(1000);
  }
  
  // ============================== Pre capture for accurate timing ========================= //

  // Captures frames from the camera to ensure accurate timing before the actual capture.
  // This ensures that the camera is ready and properly initialized before the main capture.
  for (int i = 0; i <= 3; i++) {
    camera_fb_t * fb = NULL;    // Camera frame buffer
    fb = esp_camera_fb_get();
     if(!fb) {
        Serial.println("Camera capture failed");
        Serial.println("Restarting the ESP32 CAM.");
        delay(1000);
        ESP.restart();   // Reboot ESP32 CAM
        return;
      } 
    esp_camera_fb_return(fb);     // Return the frame buffer to be reused again
    delay(200);
  }
  

  // ===================================== Actual Capture =================================== //
  
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  if(!fb) {
    Serial.println("Camera capture failed");
    Serial.println("Restarting the ESP32 CAM.");
    delay(1000);
    ESP.restart();
    return;
  } 

  // Turning off the LED
  if (LED_Flash_ON == true) digitalWrite(FLASH_LED_PIN, LOW);
  
  Serial.println("Taking a photo was successful.");
  

  // =============================== Connection to Server ===================================== //

  Serial.println("Connecting to server: " + serverName);

  // .c_str() --> convert a String object named serverName into a null-terminated character array.

  if (client.connect(serverName.c_str(), serverPort)) {   
    Serial.println("Connection successful!");   
     
    // Constructing the POST Request using multipart/form-data encoding
    String post_data = "--dataMarker\r\nContent-Disposition: form-data; name=\"imageFile\"; filename=\"ESP32CAMCap.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
    String head =  post_data;
    String boundary = "\r\n--dataMarker--\r\n";
    
    uint32_t imageLen = fb->len;
    uint32_t dataLen = head.length() + boundary.length();
    uint32_t totalLen = imageLen + dataLen;
    
    // Sending the Request Headers
    client.println("POST " + serverPath + " HTTP/1.1");
    client.println("Host: " + serverName);
    client.println("Content-Length: " + String(totalLen));
    client.println("Content-Type: multipart/form-data; boundary=dataMarker");
    client.println();
    client.print(head);
  
    // Sending Image Data in chunks of <= 1024 bytes to the server 
    uint8_t *fbBuf = fb->buf;
    size_t fbLen = fb->len;
    for (size_t n=0; n<fbLen; n=n+1024) {
      if (n+1024 < fbLen) {
        client.write(fbBuf, 1024);
        fbBuf += 1024;
      }
      else if (fbLen%1024>0) {
        size_t remainder = fbLen%1024;
        client.write(fbBuf, remainder);
      }
    }   
    client.print(boundary);
    
    esp_camera_fb_return(fb);   // Return the frame buffer to be reused again

    // It waits for the server's response and stores it in the AllData and DataBody strings.
    // AllData is used to skip the HTTP headers, and DataBody stores the response body.
   
    int timoutTimer = 10000;
    long startTimer = millis();
    boolean state = false;
    Serial.println("Response : ");
    while ((startTimer + timoutTimer) > millis()) {
      Serial.print(".");
      delay(200);
         
      // Skip HTTP headers   
      while (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (AllData.length()==0) { state=true; }
          AllData = "";
        }
        else if (c != '\r') { AllData += String(c); }
        if (state==true) { DataBody += String(c); }
        startTimer = millis();
      }
      if (DataBody.length()>0) { break; }
    }
    client.stop();
    Serial.println(DataBody);
    Serial.println("-----------");
    Serial.println();
    
  }
  else {
    client.stop();
    DataBody = "Connection to " + serverName +  " failed.";
    Serial.println(DataBody);
    Serial.println("-----------");
  }
}

                                
// ======================================== Setup ================================================ //

void setup() {

  // Disable brownout detector.
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  
  Serial.begin(115200);
  Serial.println();

  pinMode(FLASH_LED_PIN, OUTPUT);

  // Setting the ESP32 WiFi to station mode
  // This mode allows the ESP32 to join an existing network and communicate with other devices on that network
  WiFi.mode(WIFI_STA);
  Serial.println();

  // Connecting ESP32 CAM to WiFi.
  Serial.println();
  Serial.print("Connecting to : ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  // The process timeout of connecting ESP32 CAM to WiFi is 20 seconds.
  // If within 20 seconds the ESP32 CAM has not been successfully connected to WiFi, the ESP32 CAM will restart.
  int connecting_process_timed_out = 20; 
  connecting_process_timed_out = connecting_process_timed_out * 2;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    if(connecting_process_timed_out > 0) connecting_process_timed_out--;
    if(connecting_process_timed_out == 0) {
      Serial.println();
      Serial.print("Failed to connect to ");
      Serial.println(ssid);
      Serial.println("Restarting the ESP32 CAM.");
      delay(1000);
      ESP.restart();
    }
  }

  Serial.println();
  Serial.print("Successfully connected to ");
  Serial.println(ssid);
  
  // Setting ESP32 CAM configuration
  Serial.println();
  Serial.print("Set the camera ESP32 CAM...");
  
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // Initialization with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;  //--> 0-63 lower number means higher quality
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 8;  //--> 0-63 lower number means higher quality
    config.fb_count = 1;
  }
  
  // Camera initialization
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    Serial.println();
    Serial.println("Restarting the ESP32 CAM.");
    delay(1000);
    ESP.restart();
  }

  sensor_t * s = esp_camera_sensor_get();   // A pointer to the image sensor control structure

  // Selectable camera resolution details :
  // -UXGA   = 1600 x 1200 pixels
  // -SXGA   = 1280 x 1024 pixels
  // -XGA    = 1024 x 768  pixels
  // -SVGA   = 800 x 600   pixels
  // -VGA    = 640 x 480   pixels
  // -CIF    = 352 x 288   pixels
  // -QVGA   = 320 x 240   pixels
  // -HQVGA  = 240 x 160   pixels
  // -QQVGA  = 160 x 120   pixels

  s->set_framesize(s, FRAMESIZE_SXGA); 

  Serial.println();
  Serial.println("Set camera ESP32 CAM successfully.");
  //---------------------------------------- 

  Serial.println();
  Serial.print("ESP32-CAM captures and sends photos to the server every 20 seconds.");
}




void loop() {

  // Timer/Millis to capture and send photos to server every 20 seconds (see Interval variable).
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= Interval) {
    previousMillis = currentMillis;
    
    sendPhotoToServer();
  }
}
