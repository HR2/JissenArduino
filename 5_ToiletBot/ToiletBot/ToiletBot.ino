#include <ESP8266WiFi.h>

const char* ssid     = "Buffalo-G-068D";
const char* password = "5ru53vaeaa86d";

const char* host = "maker.ifttt.com";
const char* keycode = "c3O7iak_EG2hUif1UJtaDL";

#define BUFFER_NUM 30
bool stateBuffer[BUFFER_NUM];
int bufferIndex = 0;
bool prevExist = false;

const int sensorPin = 12;

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  for (int i = 0; i < BUFFER_NUM; i++) stateBuffer[i] = false;
  beginWifi();

  delay(1000);
}

void loop() {
  bool sensorState = digitalRead( sensorPin );
  stateBuffer[bufferIndex] = sensorState;
  bufferIndex++;
  if ( bufferIndex >= BUFFER_NUM ) {
    bufferIndex = 0;
  }

  bool isExist = checkExist();
  if ( isExist && !prevExist) {
    sendRequest("ENTER_Toilet");
  } else if (!isExist && prevExist) {
    sendRequest("LEAVE_Toilet");
  }
  prevExist = isExist;

  delay(1000);
}

void beginWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendRequest(String _action) {
  Serial.println(_action);

  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/trigger/";
  url += _action;
  url += "/with/key/";
  url += keycode;

  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}

bool checkExist() {
  for (int i = 0; i < BUFFER_NUM; i++) {
    if (stateBuffer[i] == true) {
      return true;
    }
  }
  return false;
}
