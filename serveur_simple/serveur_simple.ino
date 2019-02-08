#include <SPI.h>
#include <WiFi.h>


WiFiServer server(80); //Declare un web server


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  connect_wifi(); // Connexion Wifi
}


void loop() {
  // listen for incoming clients
  
  server.println("HTTP/1.1 200 OK");
  server.println("Content-Type: text/html");
  server.println("Connection: close");  // the connection will be closed after completion of the response
  server.println("Refresh: 5");  // refresh the page automatically every 5 sec
  server.println();
  server.println("<!DOCTYPE HTML>");
  server.println("<html>");
  // output the value of each analog input pin
  server.print("<h1>Analogue Values</h1>");
  server.println("</html>");

  // give the web browser time to receive the data
  delay(1);
  // close the connection:
}

void connect_wifi() {
  const char* ssid = "NetworkComesWithFaith";
  const char* password = "0987654321";

  Serial.println("Connecting Wifi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect ..");
    delay(1000);
  }
  Serial.print("Connected to local Wifi\n");
  print_status();
  server.begin();
  Serial.print("Connected to wifi. My address:");
  IPAddress myAddress = WiFi.localIP();
  Serial.println(myAddress);
}
void print_status() {
  Serial.print("WiFi connected \n");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MAC address: ");
  Serial.print(WiFi.macAddress());
  Serial.print("\n");
}
