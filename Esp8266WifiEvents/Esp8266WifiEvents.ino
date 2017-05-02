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

 // ----- Event functions -----

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

// Manage incoming device connection on ESP access point
void onNewStation(WiFiEventSoftAPModeStationConnected sta_info) {
  Serial.println("New Station :");
  sprintf(last_mac,"%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(sta_info.mac));
  Serial.printf("MAC address : %s\n",last_mac);
  Serial.printf("Id : %d\n", sta_info.aid);
  waitingDHCP=true;
}

// Manage device disconnection on ESP access point
void onLeaveStation(WiFiEventSoftAPModeStationDisconnected sta_info) {
  Serial.println("Leaving Station :");
  sprintf(last_mac,"%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(sta_info.mac));
  Serial.printf("MAC address : %s\n",last_mac);
  Serial.printf("Id : %d\n", sta_info.aid);
  Serial.println("Device List :");
  Serial.println(deviceList());
}

// Manage stations asking for access points list
void onProbeRequest(WiFiEventSoftAPModeProbeRequestReceived sta_info) {
  char prob_mac[18];
  Serial.println("Probe Request :");
  sprintf(prob_mac,"%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(sta_info.mac));
  Serial.printf("MAC address : %s\n",prob_mac);
  Serial.printf("RSSI : %d\n", sta_info.rssi);
}

void setup() { 

  static WiFiEventHandler e1, e2, e3, e4, e5;

  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(YOUR_WIFI_SSID, YOUR_WIFI_PASSWD);
  
  pinMode(ONBOARDLED, OUTPUT); // Onboard LED
  digitalWrite(ONBOARDLED, HIGH); // Switch off LED

  // Event subscriptions
  e1 = WiFi.onStationModeGotIP(onSTAGotIP);
  e2 = WiFi.onStationModeDisconnected(onSTADisconnected);
  e3 = WiFi.onSoftAPModeStationConnected(onNewStation);
  e4 = WiFi.onSoftAPModeStationDisconnected(onLeaveStation);
  e5 = WiFi.onSoftAPModeProbeRequestReceived(onProbeRequest);
}

void loop() {

  if (waitingDHCP) {
    String cb;
    if (deviceIP(last_mac,cb)) {
      Serial.println(cb); //do something
    } else {
      Serial.println(cb); //do something else
    }
  }

  delay(2000);
}

// function that writes in cb variable the IP address related to device MAC address
// true if IP exists, false if DHCP is not ready or bad MAC address

boolean deviceIP(char* mac_device, String &cb) {

  struct station_info *station_list = wifi_softap_get_station_info();

  while (station_list != NULL) {
    char station_mac[18] = {0}; sprintf(station_mac, "%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(station_list->bssid));
    String station_ip = IPAddress((&station_list->ip)->addr).toString();

    if (strcmp(mac_device,station_mac)==0) {
      waitingDHCP=false;
      cb = station_ip;
      return true;
    } 

    station_list = STAILQ_NEXT(station_list, next);
  }

  wifi_softap_free_station_info();
  cb = "DHCP not ready or bad MAC address";
  return false;
}

// Function that returns devices connected to Esp access point in json format
String deviceList() {
  String list="[";
  struct station_info *station_list = wifi_softap_get_station_info();

  while (station_list != NULL) {
    char station_mac[18] = {0}; sprintf(station_mac, "%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(station_list->bssid));
    String station_ip = IPAddress((&station_list->ip)->addr).toString();

    list += "{\"mac\":\"" + String(station_mac) + "\"";
    list += ",\"ip\":\"" + station_ip + "\"}";

    station_list = STAILQ_NEXT(station_list, next);
  }
  list+="]";

  wifi_softap_free_station_info();
  return list;
}
