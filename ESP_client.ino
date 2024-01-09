#include <WiFi.h>

const char* ssid = "Reynan";
const char* password = "reynan987";
const char* serverIP = "192.168.122.233";  // Substitua pelo endereço IP do ESP32 servidor
const int serverPort = 80;  // A porta que o servidor está ouvindo

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Crie uma conexão com o servidor
  WiFiClient client;
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Conectado ao servidor");

    // Envie uma mensagem para o servidor
    String message = "Olá, servidor!";
    Serial.println("Enviando mensagem para o servidor: " + message);
    client.println(message);

    // Aguarde uma resposta do servidor (opcional)
    while (client.connected()) {
      if (client.available()) {
        String response = client.readStringUntil('\r');
        Serial.println("Resposta do servidor: " + response);
        break;
      }
    }

    // Feche a conexão
    client.stop();
  } else {
    Serial.println("Falha ao se conectar ao servidor");
  }

  // Espere por algum tempo antes de enviar a próxima mensagem
  delay(5000);
}
