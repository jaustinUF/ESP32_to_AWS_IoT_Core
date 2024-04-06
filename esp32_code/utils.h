#include <Arduino_BuiltIn.h>

#include "certs.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>  // from the Arduino PubSubClient library
#include <ArduinoJson.h>  
#include "WiFi.h"

#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

// message handler
void messageHandler(char* topic, byte* payload, unsigned int length) {
  Serial.print("incoming: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}

void connectAWS() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // from certs.h
 
  Serial.println("Connecting to Wi-Fi");
  // loop/print . while waiting for wifi connect
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials (from certs.h)
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier on port 8883
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler using the 'messageHandler' function above
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
  // while loop should time/count/terminate
  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }
  // 'connectAWS' function terminates
  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!!");
}
// Create the message to be published to the AWS MQTT broker:
//    Json {"metric":(value passed through 'metricsValue' )}
void publishMessage(int metricsValue) {
  StaticJsonDocument<200> doc;
  doc["metrics"] = metricsValue;

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}
