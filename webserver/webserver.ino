#include <WiFi.h>

WiFiServer server(80); //Declare un web server
               
void print_status(){
  Serial.print("WiFi connected \n");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MAC address: ");
  Serial.print(WiFi.macAddress());
  Serial.print("\n"); 
}

void connect_wifi(){
 const char* ssid = "NetworkComesWithFaith"; 
 const char* password= "0987654321"; 
 
 Serial.println("Connecting Wifi...");
 WiFi.begin(ssid, password);
 while(WiFi.status() != WL_CONNECTED){
   Serial.print("Attempting to connect ..");
   delay(1000);
 }
 
 Serial.print("Connected to local Wifi\n");  
 print_status();
}

// this method makes a HTTP reply:
void httpReply(WiFiClient client) {
   client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
   client.println("Connection: close");  // the connection will be closed after completion of the response
   client.println("Refresh: 5");         // refresh the page automatically every 5 sec
   client.println();
   client.println("<!DOCTYPE HTML>");
   client.println("<html>");    
   printHTML(client);
   client.println("</html>");
   printJS(client);
}

void printHTML(WiFiClient client){
  int tempValue=999; 
  client.print("<h2>température du batiment : ");
  client.print(tempValue);
  client.print(" degrés</h2>");
  
  int lightValue=888; 
  client.print("<h2>luminosité du batiment : ");
  client.print(lightValue);
  client.print(" lumens</h2>");


  client.print("<button onclick='onoff()'>on/off</button>");
}
void printJS(WiFiClient client){
  client.print("<script>");
  client.print("function onoff(){");
  client.print("console.log(\"on/off\");");
  client.print("var ip = location.hostname;");
  client.print("var xmlHttp = new XMLHttpRequest();");
  client.print("xmlHttp.open( \"GET\", ip, false );"); // false for synchronous request
  client.print("xmlHttp.send( '0' );");
  client.print("return xmlHttp.responseText;");
  client.print("}");
  client.print("</script>");
}

void setup(){ 
  Serial.begin(9600);
  delay(1);

  connect_wifi(); // Connexion Wifi  
  server.begin(); // Lancement du serveur
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c); // Pour voir sur la console ce que l'on a recu
       
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) { // send a standard http response header
          httpReply(client);
          break;
        }
        if (c == '\n') { // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') { // you've gotten a character on the current line
          currentLineIsBlank = false;
          if(c=='0') {

          }
        }
      }
    }
    
    // give the web browser time to receive the data
    delay(100); // ms

    // close the connection :
    client.stop();
    Serial.println("client disconnected");
  }
}
