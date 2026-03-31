include <ESP8266WiFi.h>

const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";

WiFiServer server(80);
int relayPin = D1;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("/ON") != -1) {
    digitalWrite(relayPin, HIGH);
  }
  if (request.indexOf("/OFF") != -1) {
    digitalWrite(relayPin, LOW);
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<h1>Home Automation</h1>");
  client.println("<a href=\"/ON\">Turn ON</a><br>");
  client.println("<a href=\"/OFF\">Turn OFF</a><br>");
}
