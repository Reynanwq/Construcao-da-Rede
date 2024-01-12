#include <WiFi.h> 

const char* ssid = "MEDIC";
const char* password = "medic123";
const char* serverIP = "192.168.1.3";  //endereço IP do ESP32 servidor
const int serverPort = 80;  //porta que o servidor está ouvindo

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  //funcao que inicia conexao do esp32 à uma rede especifica
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
  //estabelecer e gerenciar conexões com servidores remotos através do protocolo TCP/IP.
  WiFiClient client;
  
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Conectado ao servidor");

    // envia uma mensagem para o servidor
    String message = "Olá, Leonardo!";
    Serial.println("Enviando mensagem para o servidor: " + message);
    client.println(message);

    // Aguarde uma resposta do servidor
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
