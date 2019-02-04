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

  wifiMulti.addAP("HUAWEI-6EC2", "FGY9MLBL");
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");
  
  Serial.print("\nConnecting Wifi...\n");
  if(wifiMulti.run() == WL_CONNECTED) {
    print_ip_status();
  }
}

void loop(){
    if(wifiMulti.run() != WL_CONNECTED) {
        Serial.print("Attempting to connected !\n");
        delay(1000);
    }
    WiFi.disconnect();
}
