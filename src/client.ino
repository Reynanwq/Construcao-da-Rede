#include <WiFi.h>

const char *ssid = "Wokwi-GUEST";
const char *password = "";

// Define se o dispositivo atuará como servidor ou cliente
#define SERVER_MODE false // Defina como true para o ESP32 servidor e false para o ESP32 cliente

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password, 6);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println("\nConectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());

  // Obtém o endereço MAC
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());

  if (SERVER_MODE) {
    // Se for o servidor, inicia o servidor
    server.begin();
  }
}

void loop() {
  if (SERVER_MODE) {
    // Se for o servidor
    WiFiClient client = server.available();

    if (client) {
      Serial.println("New Client connected");
      String request = client.readStringUntil('\r');
      Serial.println("Request: " + request);

      String response = "Hello, ESP32!";
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/plain");
      client.println("Connection: close");
      client.println();
      client.println(response);

      delay(5000);
      client.stop();
      Serial.println("Client disconnected");
    }
  } else {
    // Se for o cliente
    WiFiClient client;
    const char *serverIP = "10.10.0.2"; // Substitua pelo endereço IP do servidor
    const int serverPort = 80;

    if (client.connect(serverIP, serverPort)) {
      Serial.println("Connected to server");
      client.println("Hello from ESP32 client!");
      delay(5000);
      client.stop();
      Serial.println("Client disconnected");
    } else {
      Serial.println("Connection to server failed");
    }

    delay(10000); // Aguardar 10 segundos antes de tentar novamente
  }
}
