//callback notifying us of the need to save config
void saveConfigCallback () {
  sLog("Should save config");
  shouldSaveConfig = true;
}

void initWifiManager() {

  WiFiManager wm;

  //set config save notify callback
  wm.setSaveConfigCallback(saveConfigCallback);

  // setup custom parameters
  // name / placeholder / default value / length
  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 6);
  WiFiManagerParameter custom_mqtt_user("user", "mqtt user", mqtt_user, 20);
  WiFiManagerParameter custom_mqtt_pass("pass", "mqtt password", mqtt_password, 20);
  WiFiManagerParameter custom_mqtt_topic("topic_sub", "mqtt topic", mqtt_topic, 30);
   
  wm.addParameter(&custom_mqtt_server);
  wm.addParameter(&custom_mqtt_port);
  wm.addParameter(&custom_mqtt_user);
  wm.addParameter(&custom_mqtt_pass);
  wm.addParameter(&custom_mqtt_topic);  

  //reset settings - wipe credentials for testing
  //wm.resetSettings();

  //automatically connect using saved credentials if they exist
  //If connection fails it starts an access point
  if (!wm.autoConnect(wifi_ssid, wifi_password)) {
    sLog("failed to connect and hit timeout");
    delay(3000);
    // if we still have not connected restart and try all over again
    ESP.restart();
    delay(5000);
  }

  // always start configportal for a little while
  if (alwaysStartPortal) {
    wm.setConfigPortalTimeout(60);
    wm.startConfigPortal(wifi_ssid, wifi_password);
  }
  

  //if you get here you have connected to the WiFi
  sLog("wifi connected...");

  //read updated parameters
  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(mqtt_user, custom_mqtt_user.getValue());
  strcpy(mqtt_password, custom_mqtt_pass.getValue());
  strcpy(mqtt_topic, custom_mqtt_topic.getValue());

  //save the custom parameters to FS
  if (shouldSaveConfig) {
    sLog("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"]   = mqtt_server;
    json["mqtt_port"]     = mqtt_port;
    json["mqtt_user"]     = mqtt_user;  
    json["mqtt_password"] = mqtt_password;  
    json["mqtt_topic"]    = mqtt_topic;  
    
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      sLog("failed to open config file for writing");
    }

    json.prettyPrintTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
    shouldSaveConfig = false;
  }

  Serial.println("local ip");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.subnetMask());
}
