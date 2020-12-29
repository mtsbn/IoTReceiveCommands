
void initMQTT () {
  int convertedPort = atoi(mqtt_port);
  MQTT.setServer(mqtt_server, convertedPort); 
  MQTT.setCallback(mqtt_callback); 
}

void connectMQTT () {
  while (!MQTT.connected()) 
    {
        sLog("trying connect to mqtt broker... ", false);
        sLog(mqtt_server);
        bool mqttConnected = strlen(mqtt_user) > 0 ? MQTT.connect(mqtt_client, mqtt_user, mqtt_password) : MQTT.connect(mqtt_client);
        if (mqttConnected) 
        {
            sLog("successfully connect to mqtt broker");
            MQTT.subscribe (mqtt_topic); 
            sLog("subscribed to topic: ", false);
            sLog(mqtt_topic);
        } 
        else
        {
            sLog("fail in connect to mqtt broker");
            sLog("trying again in 2 seconds");
            delay(2000);
        }
    }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
 
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }

    sLog("New message received...");
    sLog("Topic: ", false);
    sLog(topic);
    sLog("Message: ", false);
    sLog(msg);      

    //put the code for execute when receive mqtt message...
}
