#include <WiFi.h>

WiFiServer server(80); //Declare un web server
int tempValue = 0;
int lightValue = 0;

//***********************

//source : https://startingelectronics.org/tutorials/arduino/ethernet-shield-web-server-tutorial/SD-card-AJAX-XML-web-server/
char HTTP_req[50] = {0};
char req_index = 0;
// sets every element of str to 0 (clears array)
void StrClear(char *str, char length)
{
  for (int i = 0; i < length; i++) {
    str[i] = 0;
  }
}
// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind)
{
  char found = 0;
  char index = 0;
  char len;
  len = strlen(str);
  if (strlen(sfind) > len) {
    return 0;
  }
  while (index < len) {
    if (str[index] == sfind[found]) {
      found++;
      if (strlen(sfind) == found) {
        return 1;
      }
    }
    else {
      found = 0;
    }
    index++;
  }
  return 0;
}
void XML_response(WiFiClient client) {
  Serial.write("\nXMLRESPONSE\n");
  client.print("<?xml version = \"1.0\" ?>");
  client.print("<inputs>");
  client.print("<button1>");
  client.print("aVal");
  client.print("</button1>");
  client.print("</inputs>");
}
//***********************
//Connexion wifi
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
void print_status() {
  Serial.print("WiFi connected \n");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MAC address: ");
  Serial.print(WiFi.macAddress());
  Serial.print("\n");
}
//***********************
//http
void httpReply(WiFiClient client) {
  
  client.println("Content-Type: text/html");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.println("Refresh: 10");         // refresh the page automatically every 5 sec
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  printHTML(client);
  client.println("</html>");
  printJS(client);
}
void printHTML(WiFiClient client) {
  updateValues();
  client.print("<h2>température du batiment : ");
  client.print("<span id=\"temp\">");
  client.print(tempValue);
  client.print("</span>");
  client.print(" degrés</h2>");
  client.print("<h2>luminosité du batiment : ");
  client.print("<span id=\"light\">");
  client.print(lightValue);
  client.print(" < / span > ");
  client.print(" lumens < / h2 > ");
  client.print("<button onclick = 'onoff()'>on / off < / button > ");
}
void updateValues() {
  tempValue = 1;//sera mis a jour avec la valeur du capteur
  lightValue = 1;
}
void printJS(WiFiClient client) {
  client.print("<script>");
  client.print("function onoff() {");
  client.print("console.log(\"on/off\");");

  client.print("var xmlHttp = new XMLHttpRequest();");
  client.print("xmlHttp.open( \"GET\", \"ajax_inputs\", true );"); // false for synchronous request
  client.print("xmlHttp.send( '0' );");
  client.print("console.log(\"rep = \"+xmlHttp.responseText);");
  //mise a jour de la page ici
  client.print("return xmlHttp.responseText;");
  client.print("}");
  client.print("</script>");
}
//*********************************
//point d'entrée
void setup() {
  Serial.begin(9600);
  delay(1);
  connect_wifi(); // Connexion Wifi
  server.begin(); // Lancement du serveur
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    String req = "";
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c); // Pour voir sur la console ce que l'on a recu
        req+=c;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) { // send a standard http response header
          
          Serial.write(req.c_str());
          Serial.write("\n");

          client.println("HTTP/1.1 200 OK");
          if (req.indexOf("ajax_inputs")>-1) {
            // send rest of HTTP header
            Serial.write("\nAJAX reply\n");
            client.println("Content-Type: text/xml");
            client.println("Connection: keep-alive");
            client.println();
            // send XML file containing input states
            XML_response(client);
          } else {
            Serial.write("\nHTTP reply\n");
            httpReply(client);
          }
          
          break;
        }
        if (c == '\n') { // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') { // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(100); // ms
    // close the connection :
    client.stop();
  }
}
