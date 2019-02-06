/* 
 *  Scan Wifi Network
 */
#include "WiFi.h"

String translateEncryptionType(wifi_auth_mode_t encryptionType) {
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}

void print_ith_interface(int i){
  Serial.print("Network Name : ");
  Serial.print(WiFi.SSID(i));
  Serial.print("\n");
  Serial.print("\tsignal Strength : ");
  Serial.print(WiFi.RSSI(i));
  Serial.print("\n");
  Serial.print("\tMAC Address : ");
  Serial.print(WiFi.BSSIDstr(i));
  Serial.print("\n");
  Serial.print("\tEncryption type: ");
  String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
  Serial.print(encryptionTypeDescription);
  Serial.print("\n");
}

void setup() {
  Serial.begin(9600);
  
  int N = WiFi.scanNetworks(); //Scan Networks
  
  if (N>0){      
    Serial.print("\n");
    Serial.print("-------------------\n");
    Serial.print("Networks found : #");
    Serial.print(N);
    Serial.print("\n"); 
    for (int i=0 ; i<N ; i++){
      Serial.print(i+1);
      Serial.print(") ");
      print_ith_interface(i);
      delay(1000);  
    }
  }
}

void loop() {
  // no code
}
