/*
 * WebSocketClientSSL.ino
 *
 *  Created on: 10.12.2015
 *
 *  note SSL is only possible with the ESP8266
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>
  #include "user_interface.h" //for timer purpose

#include <Hash.h>

const char* fingerprint = "6B 40 98 95 B7 8C BB E7 E5 DE 0D 17 D1 DB 21 67 70 FF 5A 5A";
const char* protocol= "arduino";
unsigned long lastDisco;

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
  os_timer_t myTimer;
    bool tick;



#define USE_SERIAL Serial

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {


    switch(type) {
        case WStype_DISCONNECTED:
            USE_SERIAL.printf("[WSc] Disconnected!\n");
            lastDisco=millis();
            break;
        case WStype_CONNECTED:
            {
                USE_SERIAL.printf("[WSc] Connected to url: %s\n",  payload);
        
          // send message to server when Connected
        webSocket.sendTXT("Connected");
            }
            break;
        case WStype_TEXT:
            USE_SERIAL.printf("[WSc] get text: %s\n", payload);

      // send message to server
      // webSocket.sendTXT("message here");
            break;
        case WStype_BIN:
            USE_SERIAL.printf("[WSc] get binary length: %u\n", length);
            hexdump(payload, length);

            // send data to server
            // webSocket.sendBIN(payload, length);
            break;
    }

}
  void timer(void *pArg) {
        tick = true;
  }
  
void setup() {
    // USE_SERIAL.begin(921600);
    USE_SERIAL.begin(115200);

    //Serial.setDebugOutput(true);
    USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

      for(uint8_t t = 4; t > 0; t--) {
          USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
          USE_SERIAL.flush();
          delay(1000);
      }

    WiFiMulti.addAP("Agwadada", "0984265620");

    //WiFi.disconnect();
    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

   
    //webSocket.beginSSL("78.218.62.97", 9001,"",fingerprint,protocol);
    webSocket.beginSSL("78.218.62.97", 9001);
    Serial.print("fingerprint P : ");
    Serial.println(fingerprint);
    webSocket.onEvent(webSocketEvent);

      tick = false;
  os_timer_setfn(&myTimer,timer, NULL);
  os_timer_arm(&myTimer, 5000, true); //kaka

}

void loop() {


  if (lastDisco==1 || lastDisco<millis()-5000){ // prevent esp from trying to connect at each loop and prevent form comapring millis at each loop when client is connected
    webSocket.loop(); //timeout before reconnection if disconnected
    lastDisco=1;
  }
      if (tick == true) {
        String millisStr = String(millis(), DEC); 
        webSocket.sendTXT("Hello : " + millisStr);
        tick=false;
}
}
