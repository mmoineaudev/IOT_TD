
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//les branchements
#define LED_PIN 23
#define TEMP_PIN 19
#define LIGTH_PIN 34
//le web server
WiFiServer server(80);
//les id de la wifi
const char* ssid = "NetworkComesWithFaith";
const char* password = "0987654321";
//les var globales
int tempValue = 0;
int lightValue = 0;
//la récupération de la température
OneWire oneWire(TEMP_PIN);
DallasTemperature tempSensor(&oneWire);

bool led_on = true;

//***********************
//Connexion wifi
void connect_wifi() {

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
}
//***********************
//http
void httpReply(WiFiClient client) {
  client.println("Content-Type: text/html");
  
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.println("Refresh: 2");         // refresh the page automatically every 5 sec
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<meta charset=\"UTF-8\">");
  client.println("<html>");
  printHTML(client);
  client.println("</html>");
  printJS(client);
}
void printHTML(WiFiClient client) {
  lightValue = analogRead(LIGTH_PIN);
  tempSensor.requestTemperaturesByIndex(0);
  tempValue = tempSensor.getTempCByIndex(0);

  client.print("<h3>IP du client :");
  client.print(WiFi.localIP());
  client.print("</h3>");
  client.print("<p>température du batiment : ");
  client.print("<span id=\"temp\">");
  client.print(tempValue);
  client.print("</span>");
  client.print(" degrés</p></br>");
  client.print("<p>luminosité du batiment : ");
  client.print("<span id=\"light\">");
  client.print(lightValue);
  client.print(" lumens </p>");

  client.print(" <p>La diode est  ");
  client.print(led_on?"allumée":"éteinte");
  client.print("</p>");
  client.print("<button onclick = 'diode(\"ON\")'> on </button > ");
  client.print("<button onclick = 'diode(\"OFF\")'> off </button > ");
}

void printJS(WiFiClient client) {
  client.print("<script>");
  client.print("function diode(on_off) {\n");//on_off vaut ON ou OFF
  client.print("console.log(on_off);\n");
  client.print("var xmlhttp = new XMLHttpRequest();\n");
  client.print("xmlhttp.open(\"GET\", on_off, true);\n");
  client.print("xmlhttp.send();\n");
  client.print("}\n");
  client.print("</script>");
}

//*********************************
//point d'entrée
void setup() {
  Serial.begin(9600);
  delay(1);
  connect_wifi(); // Connexion Wifi
  server.begin(); // Lancement du serveur
  pinMode(LED_PIN, OUTPUT);
  tempSensor.begin();

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
        req += c;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) { // send a standard http response header
          Serial.write(req.c_str());
          Serial.write("\n");
          client.println("HTTP/1.1 200 OK");
          if (req.indexOf("ON") > -1) {
            led_on = true;
          } else if (req.indexOf("OFF") > -1) {
            led_on = false;

          } else {
            //Serial.write("\nHTTP reply\n");
            httpReply(client);
          }
          break;
        } else if (c == '\n') { // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') { // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    
    if (led_on) digitalWrite(LED_PIN, HIGH);
    else       digitalWrite(LED_PIN, LOW);
    
    delay(100); // ms
    // close the connection :
    client.stop();
  }
}



//***********************
//source : https://startingelectronics.org/tutorials/arduino/ethernet-shield-web-server-tutorial/SD-card-AJAX-XML-web-server/

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
