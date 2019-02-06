#include <WiFi.h>
#define LED 23
WiFiServer server(80); //Declare un web server

void print_status() {
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
  const char* password = "0987654321";

  Serial.println("Connecting Wifi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect ..");
    delay(1000);
  }

  Serial.print("Connected to local Wifi\n");
  print_status();
}

void printHTML(WiFiClient client, int lightSensorValue) {
  client.println("<!DOCTYPE HTML>");
  client.println("<html lang=\"en\">");
  client.println("<script>window.setInterval(function(){");
  client.println("nocache = \"&nocache=\" + Math.random() * 10;");
  client.println("var request = new XMLHttpRequest();");
  client.println("request.onreadystatechange = function() {");
  client.println("if (this.readyState == 4) {");
  client.println("if (this.status == 200) {");
  client.println("if (this.responseText != null) {");
  client.println("document.getElementById(\"analoge_data\").innerHTML = this.responseText;");
  client.println("}}}}");
  client.println("request.open(\"GET\", \"ajaxrefresh\" + nocache, true);");
  client.println("request.send(null);");
  client.println("}, 5000);");
  client.println("function changeLEDStatus() {");
  client.println("nocache = \"&nocache=\" + Math.random() * 10;");
  client.println("var request = new XMLHttpRequest();");
  client.println("request.onreadystatechange = function() {");
  client.println("if (this.readyState == 4) {");
  client.println("if (this.status == 200) {");
  client.println("if (this.responseText != null) {");
  client.println("document.getElementById(\"led_status\").innerHTML = this.responseText;");
  client.println("}}}}");
  client.println("request.open(\"GET\", \"?ledstatus=1\" + nocache, true);");
  client.println("request.send(null);");
  client.println("}");
  client.println("</script></head>");
  // output the value of each analog input pin
  client.print("<h1>Analogue Values</h1>");
  client.println("<div id=\"analoge_data\">");
  client.print("lightSensorValue : ");
  client.print("</div>");
  client.println("<h1>Arduino LED Status</h1>");
  client.println("<div><span id=\"led_status\">");
}
void ajaxRequest(WiFiClient client)
{
  for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
    int sensorReading = analogRead(analogChannel);
    client.print("analog input ");
    client.print(analogChannel);
    client.print(" is ");
    client.print(sensorReading);
    client.println("<br />");
  }
}

void ledChangeStatus(WiFiClient client)
{
  int state = digitalRead(LED);
  Serial.println(state);
  if (state == 1) {
    digitalWrite(LED, LOW);
    client.print("OFF");
  }
  else {
    digitalWrite(LED, HIGH);
    client.print("ON");
  }
}
void setup() {
  Serial.begin(9600);
  delay(1);

  connect_wifi(); // Connexion Wifi
  server.begin(); // Lancement du serveur
}

void loop() {
  String HTTP_req;
  //the light sensor value
  int sensorValue = analogRead(A0);
  //Serial.println(sensorValue);
  // listen for incoming clients
  WiFiClient client = server.available();
  //Serial.println(client);//seems there is no client 
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if ( HTTP_req.length() < 120)
          HTTP_req += c; // save the HTTP request 1 char at a time
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank)
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          Serial.println(HTTP_req);
          if (HTTP_req.indexOf("ajaxrefresh") >= 0 ) {
            // read switch state and analog input
            ajaxRequest(client);
            break;
          }
          else if (HTTP_req.indexOf("ledstatus") >= 0 ) {
            // read switch state and analog input
            ledChangeStatus(client);
            break;
          }
          else {
            printHTML(client, sensorValue);
            if (digitalRead(LED) == 1)
              client.println("On");
            else
              client.println("Off");
            client.println("</span> | <button onclick=\"changeLEDStatus()\">Change Status</button> </div>");
            client.println("</html>");
            break;
          }
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    HTTP_req = "";
    Serial.println("client disconnected");
  }
}
