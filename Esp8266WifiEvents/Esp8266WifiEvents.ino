#include <ESP8266WiFi.h>
// include plain C library
extern "C" {
#include "user_interface.h"
}

#define YOUR_WIFI_SSID "NUMERICABLE-3DA4"
#define YOUR_WIFI_PASSWD "BJX57NGKBW"
#define ONBOARDLED 2 // Built in LED on ESP-12/ESP-07

boolean waitingDHCP=false;
char last_mac[18];


// Manage IP attribution from station we are connected to
void onSTAGotIP(WiFiEventStationModeGotIP ipInfo) {
  Serial.printf("Got IP: %s\r\n", ipInfo.ip.toString().c_str());
  digitalWrite(ONBOARDLED, LOW); // Turn on LED
}

// Manage network disconnection
void onSTADisconnected(WiFiEventStationModeDisconnected event_info) {
  Serial.printf("Disconnected from SSID: %s\n", event_info.ssid.c_str());
  Serial.printf("Reason: %d\n", event_info.reason);
  digitalWrite(ONBOARDLED, HIGH); // Turn off LED
}

// Manage incoming connection on ESP access point
void onNewStation(WiFiEventSoftAPModeStationConnected sta_info) {
  uint8 softap_stations_cnt;
  struct station_info *stat_info;
  struct ip_addr *ipaddr;
  Serial.println("New Station :");
  //Serial.printf("dst.mac: %02X:%02X:%02X:%02X:%02X:%02X\n", MAC2STR(sta_info.mac));
  sprintf(last_mac,"%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(sta_info.mac));
  Serial.println(last_mac);
  Serial.printf("dst.aid: %d\n", sta_info.aid); //number of connected stations
  waitingDHCP=true;
}


void setup() { 

  static WiFiEventHandler e1, e2, e3;

  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(YOUR_WIFI_SSID, YOUR_WIFI_PASSWD);
  
  pinMode(ONBOARDLED, OUTPUT); // Onboard LED
  digitalWrite(ONBOARDLED, HIGH); // Switch off LED

  e1 = WiFi.onStationModeGotIP(onSTAGotIP);
  e2 = WiFi.onStationModeDisconnected(onSTADisconnected);
  e3 = WiFi.onSoftAPModeStationConnected(onNewStation);
}

void loop() {

  if (waitingDHCP) {
    newConnectedDevice();
  }

  delay(2000);
}

void newConnectedDevice() {

  struct station_info *station_list = wifi_softap_get_station_info();

  while (station_list != NULL) {
    char station_mac[18] = {0}; sprintf(station_mac, "%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(station_list->bssid));
    String station_ip = IPAddress((&station_list->ip)->addr).toString();

    if (strcmp(last_mac,station_mac)==0) {
      Serial.print("New station connected : ");
      Serial.print(station_mac); Serial.print(" "); Serial.println(station_ip);
      waitingDHCP=false;
    } 

    station_list = STAILQ_NEXT(station_list, next);
    waitingDHCP=false;
  }

  wifi_softap_free_station_info();

}
