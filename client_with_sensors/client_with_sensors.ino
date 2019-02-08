#include <WiFi.h>
#include <HTTPClient.h>
const char* SERV_ADDR = "http://10.154.118.235:8080";

void print_ip_status() {
  Serial.print("WiFi connected \n");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MAC address: ");
  Serial.print(WiFi.macAddress());
  Serial.print("\n");
}

void connect_wifi() {
  const char* ssid = "NetworkComesWithFaith";
  const char *password = "0987654321";

  Serial.println("\nConnecting Wifi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect ..\n");
    delay(1000);
  }
  Serial.print("Connected to local Wifi\n");
  print_ip_status();
}

void get_from_serv() {
  // configure targeted server and url
  HTTPClient serv;

  serv.begin(SERV_ADDR); // Ce serveur est suppose renvoyer
  // une page Web contenant votre IP

  // start connection and send HTTP header
  int HttpRetCode = serv.GET();
  Serial.print("\n");
  Serial.print(HttpRetCode);
  if (HttpRetCode > 0) {
    // HTTP header has been send and Server response header has been handled
    //Serial.print("Received data ...");
    String Contents = serv.getString();

    Serial.print("\n");
    Serial.print(Contents);
    Serial.print("\n");

    //serv.end(); // End connection
  } else {

    Serial.print("\n");

    Serial.print("Fail : retCode : ");
    Serial.print(HttpRetCode);
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for a serial connection

  connect_wifi();

  get_from_serv();
}

void loop() {
}
