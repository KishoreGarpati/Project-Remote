/*Description : API for accessing TV remote */

#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <ESP8266mDNS.h>

IPAddress ip(192, 168, 0, 4);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

const char* ssid = "t3..";
const char* password = "worldcup@15";
MDNSResponder mdns;

IRsend irsend(4); //an IR led is connected to D2

int khz = 38; 

WiFiServer server(80);


void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.config(ip, gateway, subnet);
  irsend.begin();
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  // Start the server
  server.begin();
  Serial.println("HTTP Server Started");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("IRBlasterLR", WiFi.localIP())) {
    Serial.println("MDNS Responder Started");
  }

  Serial.println();
  Serial.println();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  if (req.indexOf("/KEY_POWER") != -1){
      irsend.sendRC6(0x1000C, 20); 
      Serial.println("IRreq KEY_POWER sent");
  }
  else if (req.indexOf("/KEY_MUTE") != -1){
      irsend.sendRC6(0x1000D, 20);
      Serial.println("IRreq KEY_MUTE sent");
  }
  else if (req.indexOf("/KEY_1") != -1){
      irsend.sendRC6(0x10001, 20);
      Serial.println("IRreq KEY_1 sent");
  }
  else if (req.indexOf("/KEY_2") != -1){
      irsend.sendRC6(0x10002, 20);
      Serial.println("IRreq KEY_2 sent");
  }
  else if (req.indexOf("/KEY_3") != -1){
      irsend.sendRC6(0x10003, 20);
      Serial.println("IRreq KEY_3 sent");
  }
  else if (req.indexOf("/KEY_4") != -1){
      irsend.sendRC6(0x10004, 20);
      Serial.println("IRreq KEY_4 sent");
  }
  else if (req.indexOf("/KEY_5") != -1){
      irsend.sendRC6(0x10005, 20);
      Serial.println("IRreq KEY_5 sent");
  }
  else if (req.indexOf("/KEY_6") != -1){
      irsend.sendRC6(0x10006, 20);
      Serial.println("IRreq KEY_6 sent");
  }
  else if (req.indexOf("/KEY_7") != -1){
      irsend.sendRC6(0x10007, 20);
      Serial.println("IRreq KEY_7 sent");
  }
  else if (req.indexOf("/KEY_8") != -1){
      irsend.sendRC6(0x10008, 20);
      Serial.println("IRreq KEY_8 sent");
  }
  else if (req.indexOf("/KEY_9") != -1){
      irsend.sendRC6(0x10009, 20);
      Serial.println("IRreq KEY_9 sent");
  }  
  else if (req.indexOf("/KEY_0") != -1){
      irsend.sendRC6(0x10000, 20);
      Serial.println("IRreq KEY_0 sent");
  }
  else if (req.indexOf("/KEY_CHANNELUP") != -1){
      irsend.sendRC6(0x1004C, 20);
      Serial.println("IRreq KEY_CHANNELUP sent");
  }
  else if (req.indexOf("/KEY_CHANNELDOWN") != -1){
      irsend.sendRC6(0x1004D, 20);
      Serial.println("IRreq KEY_CHANNELDOWN sent");
  }
  else if (req.indexOf("/KEY_VOLUMEDOWN") != -1){
      irsend.sendRC6(0x10011, 20);
      Serial.println("IRreq KEY_VOLUMEDOWN sent");
  }
  else if (req.indexOf("/KEY_VOLUMEUP") != -1){
      irsend.sendRC6(0x10010, 20);
      Serial.println("IRreq KEY_VOLUMEUP sent");
  }
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
  
  client.flush();
   
  // Send the response to the client
  //client.print(s);
  client.print("HTTP/1.1 200 OK\r\n");
  delay(1);
  Serial.println("Client Disconnected");
  Serial.println();
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
