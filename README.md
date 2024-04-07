# ESP32 microcontroller to AWS IoT Core
## Overview
This project uses an ESP32 microcontroller development board as the edge device. The AWS console setup is the same as in the *AWS IoT demo project.*
## ESP32
### Code installation
The three files in the esp32_code directory are the C++ code for the ESP32. The Arduino IDE compiles these files, loads the resulting object file into the esp32, and causes it to run. Using auth/cert credentials in certs.h the ESP32 code:
- connects to the wifi network,
- connects to the AWS IoT Core endpoinr,  
- connects to the briker topic,
- sends the json string message 'metric: (random number)' once a second.

The AWS IoT MQTT broker received the message, based on the MQTT topic set in utils.h.

Based on: https://www.youtube.com/watch?v=QctUfGqdR20&list=PL3wa9dpS-Ht6yCfYdUsw3WwoC08v8AU8E
