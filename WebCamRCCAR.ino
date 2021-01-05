// https://github.com/heets-silver/esp32cam-car.git
#include "esp_camera.h"
#include <WiFi.h>

//
// WARNING!!! Make sure that you have either selected ESP32 Wrover Module,
//            or another board which has PSRAM enabled
//
// Adafruit ESP32 Feather

// Select camera model
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_M5STACK_PSRAM
#define CAMERA_MODEL_AI_THINKER

const char* ssid = "enter-your-ssid";
const char* password = "enter-your-password";

#if defined(CAMERA_MODEL_WROVER_KIT)
#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    21
#define SIOD_GPIO_NUM    26
#define SIOC_GPIO_NUM    27

#define Y9_GPIO_NUM      35
#define Y8_GPIO_NUM      34
#define Y7_GPIO_NUM      39
#define Y6_GPIO_NUM      36
#define Y5_GPIO_NUM      19
#define Y4_GPIO_NUM      18
#define Y3_GPIO_NUM       5
#define Y2_GPIO_NUM       4
#define VSYNC_GPIO_NUM   25
#define HREF_GPIO_NUM    23
#define PCLK_GPIO_NUM    22


#elif defined(CAMERA_MODEL_AI_THINKER)
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

#else
#error "Camera model not selected"
#endif

// GPIO Setting
extern const int gpLb =  2; // Left Wheel Back
extern const int gpLf = 12; // Left Wheel Forward
extern const int gpRb = 16; // Right Wheel Back
extern const int gpRf = 13; // Right Wheel Forward
extern const int gpLed =  4; // Light
extern const int gpCharging = 14;
extern const int gpLowBatt  = 15;
extern String WiFiAddr ="";

void startCameraServer();

void blink_led(int times)
{
  int cmsDelay = 100;
  
  while (times-- > 0) {
    digitalWrite(gpLed, HIGH);
    delay(cmsDelay);
    digitalWrite(gpLed, LOW);
    if (times > 0) {
      delay(cmsDelay*2);
    }
  }
}

void print_reset_reason()
{
  esp_reset_reason_t reason = esp_reset_reason();
  char *sz;
  switch (reason)
  {
    case ESP_RST_UNKNOWN: sz = "Reset reason can not be determined."; break;
    case ESP_RST_POWERON: sz = "Reset due to power-on event."; break;
    case ESP_RST_EXT:     sz = "Reset by external pin (not applicable for ESP32)"; break;
    case ESP_RST_SW:      sz = "Software reset via esp_restart."; break;
    case ESP_RST_PANIC:   sz = "Software reset due to exception/panic."; break;
    case ESP_RST_INT_WDT: sz = "Reset (software or hardware) due to interrupt watchdog."; break;
    case ESP_RST_TASK_WDT: sz= "Reset due to task watchdog."; break;
    case ESP_RST_WDT:     sz = "Reset due to other watchdogs."; break;
    case ESP_RST_DEEPSLEEP: sz = "Reset after exiting deep sleep mode."; break;
    case ESP_RST_BROWNOUT: sz = "Brownout reset (software or hardware)"; break;
    case ESP_RST_SDIO:     sz = "Reset over SDIO."; break;
    default:               sz = "Unknown"; break;
  }
  Serial.printf("Reset reason: %s\n", sz);
}


void setup() {
  int cFails = 0;
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  print_reset_reason();

  pinMode(gpLb, OUTPUT); //Left Backward
  pinMode(gpLf, OUTPUT); //Left Forward
  pinMode(gpRb, OUTPUT); //Right Forward
  pinMode(gpRf, OUTPUT); //Right Backward
  pinMode(gpLed, OUTPUT); //Light
  pinMode(gpLowBatt, INPUT);
  pinMode(gpCharging, INPUT);

  //initialize
  digitalWrite(gpLb, LOW);
  digitalWrite(gpLf, LOW);
  digitalWrite(gpRb, LOW);
  digitalWrite(gpRf, LOW);
  digitalWrite(gpLed, LOW);

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
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    blink_led(3);
    esp_restart();
    return;
  }
  
  //drop down frame size for higher initial frame rate
  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_CIF);
 
  WiFi.begin(ssid, password);

  blink_led(1);

  while (WiFi.localIP().toString() == "0.0.0.0") {
    delay(500);
    Serial.println(WiFi.status());
    cFails++;
    if (cFails > 9) {
      Serial.println("Giving up waiting for WiFi");
      esp_restart();
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");

  blink_led(2);

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  WiFiAddr = WiFi.localIP().toString();
  Serial.println("' to connect");
}

void loop() {
  // put your main code here, to run repeatedly:

}
