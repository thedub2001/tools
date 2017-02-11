#include <ESP8266WiFi.h> 
extern "C" {
  #include <espnow.h>
}

struct DATAS {
  uint16_t pot = 0;
  uint32_t tmp = 0;
};

void setup() {

  Serial.begin(115200); Serial.println();

  if (esp_now_init()!=0) {
    Serial.println("ESP-NOW not inicialized...");
    ESP.restart();
    delay(1);
  }

  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
  Serial.print("STA MAC: "); Serial.println(WiFi.macAddress());

  esp_now_set_self_role(2);   

  delay(10);

  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len) {

    char MACmaster[6];
    sprintf(MACmaster, "%02X:%02X:%02X:%02X:%02X:%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    Serial.print("Reception from ESP MAC: "); Serial.print(MACmaster);

    DATAS ED;
    memcpy(&ED, data, sizeof(ED));

    Serial.print(". Data pot: "); Serial.print(ED.pot);
    Serial.print(". Data tmp: "); Serial.println(ED.tmp);

  });
}

void loop() {
}

