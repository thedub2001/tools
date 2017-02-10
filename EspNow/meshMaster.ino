#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
}

#include "user_interface.h" //for timer purpose


os_timer_t myTimer1;
bool tick;

struct DATAS {
  uint16_t pot;
  uint32_t tmp;
};

uint8_t mac_addr[6] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};    


void timer1(void *pArg) {
  tick = true;
}

void setup() {

  Serial.begin(115200);
  Serial.println();

  if (esp_now_init()!=0) {
    Serial.println("*** ESP_Now init failed");
    ESP.restart();
    delay(1);
  }

  tick = false;
  os_timer_setfn(&myTimer1, timer1, NULL);
  os_timer_arm(&myTimer1, 2000, true);

  Serial.print("Access Point MAC of this ESP: "); 
  Serial.println(WiFi.softAPmacAddress());
  Serial.print("Station MAC of this ESP: "); 
  Serial.println(WiFi.macAddress());

  esp_now_set_self_role(1);   

  uint8_t role=2;  
  uint8_t channel=3;
    uint8_t key[0]={};   //means no key
    //uint8_t key[16] = {0,255,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    uint8_t key_len=sizeof(key);
    Serial.print("Key length:  "); 
    Serial.println(key_len);
    esp_now_add_peer(mac_addr,role,channel,key,key_len);

    delay(10);

    esp_now_register_send_cb([](uint8_t* mac, uint8_t status) {
      char MACslave[6];
      sprintf(MACslave,"%02X:%02X:%02X:%02X:%02X:%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
      Serial.print(". Sent to ESP MAC: "); 
      Serial.print(MACslave);
      Serial.print(". Reception (0=0K - 1=ERROR): "); 
      Serial.println(status);
    });
  }

  void loop() {

    if (tick == true) { 
      Serial.println("Tick Occurred : 2s");
      tick = false;

      DATAS ED;                     
      ED.pot = analogRead(A0);
      Serial.print("Data pot: "); Serial.print(ED.pot);
      delay(20);
      ED.tmp = millis();
      Serial.print(". Data tmp: "); Serial.print(ED.tmp);

      uint8_t data[sizeof(ED)]; 
      memcpy(data, &ED, sizeof(ED));
      uint8_t len = sizeof(data);
      esp_now_send(da, data, len); // first argument to "NULL" will brodcast data to all paired ESPs
    }
  }
