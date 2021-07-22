#include <ESP8266WiFi.h>
const char* ssid = "HUAWEI LUA-U02_0467";
const char* password = "gerryleo";
WiFiServer  server(80);

String header;
String temp = "28";
String heaterState = "off";
String fanState = "off";

const int heaterpin = 5;
const int fanpin = 4;
const int signalpin = 2;
const int signalpin2 =3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(heaterpin, OUTPUT);
  pinMode(fanpin, OUTPUT);
  digitalWrite(heaterpin, LOW);
  digitalWrite(fanpin, LOW);
  digitalWrite(signalpin, LOW);
  digitalWrite(signalPin2, LOW);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wifi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

}

void loop() {
  WiFiClient client = server.available();
  
  if(client){
    Serial.println("New Client.");
    String currentLine = "";
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        Serial.write(c);
        header += c;
        if(c == '\n'){
          if(currentLine.length() == 0){
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if(header.indexOf("GET /5/on") >= 0){
              Serial.println("Heater on");
              heaterState = "on";
              digitalWrite(heaterpin, HIGH);
              digitalWrite(signalPin, HIGH);
            } else if( header.indexOf("GET /5/off") >= 0){
              Serial.println("Heater off");
              heaterState = "off";
              digitalWrite(heaterpin, LOW);
              digitalWrite(signalPin, LOW);
            } else if (header.indexOf("GET /4/on") >= 0){
              Serial.println("Fan on");
              fanState = "on";
              digitalWrite(fanpin, HIGH);
              digitalWrite(signalPin2, HIGH);
          } else if(header.indexOf("GET /4/off") >= 0){
              Serial.println("Fan off");
              fanState = "off";
              digitalWrite(fanpin, LOW);
              digitalWrite(signalPin2, LOW);
          }
          client.println("<!DOCTYPE html><html>");
          client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<meta http-equiv=\"refresh\" content=\"300\">");
          client.println("<link rel=\"icon\" href=\"data:,\">");
          client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
          client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
          client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
          client.println(".button2 {background-color: #77878A;}</style></head>");
          client.println("<body><h1>SmartChiqs</h1>");
          client.println("<div>Temperature value " + temp + "</div>");
           
          client.println("<p>Heater-State " + heaterState + "</p>");      
            if (heaterState=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            
          client.println("<p>Fan-State " + fanState + "</p>");       
            if (fanState=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
           client.println("</body></html>");
           client.println();
           break;
        } else {
          currentLine = "";
        }
      } else if (c != '\r'){
        currentLine +=c;
      }
    }
  }
  header = "";
  client.stop();
  Serial.println("Client disconnected..");
  Serial.println("");
  
  }
}

//To be integrated with the main program code