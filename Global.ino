void checkWifiAndMqtt() {
  
  if (WiFi.status() != WL_CONNECTED) {
    ESP.restart();
  }
  
  if (!MQTT.connected()) {
    connectMQTT();
  }
            
}
 
void setupSpiffs(){
  //clean FS, for testing
   SPIFFS.format();

  //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    sLog("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      sLog("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        sLog("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          sLog("\nparsed json");

          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_port, json["mqtt_port"]);
          strcpy(mqtt_user, json["mqtt_user"]);
          strcpy(mqtt_password, json["mqtt_password"]);
          strcpy(mqtt_topic, json["mqtt_topic"]);         

        } else {
          sLog("failed to load json config");
        }
      }
    }
  } else {
    sLog("failed to mount FS");
  }
  //end read
}
