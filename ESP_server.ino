#include <WiFi.h>
 
const char* ssid = "Reynan";
const char* password = "reynan987";

//criando obj que irá gerenciar conexoes
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
 
  //inicia servidor
  server.begin();
}
 
void loop() {
  //aguarda conexoes de clientes
    WiFiClient client = server.available();
    if (client) {
    Serial.println("Novo cliente conectado");
    // Aguarda até que o cliente envie dados
    while (client.connected()) {
      if (client.available()) {
        // ler os dados do cliente
        String message = client.readStringUntil('\r');
        Serial.print("Mensagem recebida: ");
        Serial.println(message);

        // Enviar uma resposta de volta ao cliente 
        client.println("Mensagem recebida com sucesso!");

        // Feche a conexão
        client.stop();
      }
    }
  }
}