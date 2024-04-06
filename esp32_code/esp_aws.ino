#include <Arduino_BuiltIn.h>
#include "utils.h"
#include <PubSubClient.h>

void setup() {
    Serial.begin(115200);
    connectAWS();   // in utils.h: connect to wifi then AWS IoT
}

void loop() {
  // load metric with random number
  int metricsValue = random(1, 100);
  Serial.print(F("metrics: ")); // print metric locally (Arduino IDE output)
  Serial.print(metricsValue);
  // publish message at a one-per-second rate.
  publishMessage(metricsValue); // function at end of utils.h
  client.loop();
  delay(1000);
}