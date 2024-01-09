#include <WiFi.h>
 
const char* ssid = "Reynan";
const char* password = "reynan987";

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
 
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
 
  server.begin();
}
 
void loop() {
    WiFiClient client = server.available();
    if (client) {
    Serial.println("Novo cliente conectado");
    // Aguarde até que o cliente envie dados
    while (client.connected()) {
      if (client.available()) {
        // Leia os dados do cliente
        String message = client.readStringUntil('\r');
        Serial.print("Mensagem recebida: ");
        Serial.println(message);

        // Enviar uma resposta de volta ao cliente (opcional)
        client.println("Mensagem recebida com sucesso!");

        // Feche a conexão
        client.stop();
      }
    }
  }
}