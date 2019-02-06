/*
 *  This sketch trys to Connect to the best AP based on a given list
 */

#include <WiFi.h>
#include <WiFiMulti.h>


WiFiMulti wifiMulti;

void print_ip_status(){
  Serial.print("WiFi connected \n");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MAC address: ");
  Serial.print(WiFi.macAddress());
  Serial.print("\n"); 
}

void setup(){
  Serial.begin(9600);
  delay(1000);

  wifiMulti.addAP("NetworkComesWithFaith", "0987654321");


  Serial.print("\nConnecting Wifi...\n");
  if(wifiMulti.run() == WL_CONNECTED) {
    print_ip_status();
  }else{
    Serial.print("\nWifi not connected\n");
  }
}

void loop(){
    if(wifiMulti.run() != WL_CONNECTED) {
        Serial.print("Attempting to connect !\n");
    }else print_ip_status();
    delay(2000);
    //WiFi.disconnect();
}
