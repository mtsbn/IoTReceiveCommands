/**********************************************
 *
 *  Develop by Matheus Nascimento
 *  github.com/mtsbn 
 *
 * *******************************************/


#include <FS.h>          // this needs to be first, or it all crashes and burns...
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson (version = 5.X)
#include <PubSubClient.h> 

#ifdef ESP32
  #include <SPIFFS.h>
#endif

//comment this line if not debugging 
#define DEBUG

//define your default values of mqtt server here, 
//if there are different values in config.json, they are overwritten.
char mqtt_server[40]    = ""; //put your mqtt server address here
char mqtt_port[6]       = ""; //put the port of your mqtt server here
char mqtt_user[20]      = ""; //put your mqtt user here
char mqtt_password[20]  = ""; //put the password of your user here
char mqtt_topic[30]     = ""; //put here the topic you want to subscribe
char mqtt_client[30]    = ""; //must be unique in mqtt broker


//wifi manager portal settings
char wifi_ssid[30] = "IoTDevice"; //put here the ssid you want in your smart device
char wifi_password[15] = "1q2w3e4r"; //put here the password to connect in your smart device
bool alwaysStartPortal = false; //if true, always show the portal for a while

//flag for saving data
bool shouldSaveConfig = false;

WiFiClient wifiClient;
PubSubClient MQTT(wifiClient); 

void sLog(String message, bool line = true);

void setup() {  
  initOutput();
  initSerial();
  setupSpiffs();
  initWifiManager();
  initMQTT();
}

void loop() {
  checkWifiAndMqtt();
  MQTT.loop();
}
