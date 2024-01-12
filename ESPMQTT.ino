#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>

// WiFi
const char *ssid = "MEDIC";     // Nome da sua rede WiFi
const char *password = "medic123";  // Senha da sua rede WiFi

// MQTT Broker
const char *mqtt_broker = "ws://10.129.224.36";
const char *topic = "server";
const int mqtt_port = 9001;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

bool testNetworkConnectivity() {
    HTTPClient http;

    // Endereço do servidor para testar (por exemplo, o Google)
    http.begin("http://www.google.com");

    int httpCode = http.GET();

    // Fecha a conexão HTTP
    http.end();

    // Verifica se a resposta do servidor foi bem-sucedida (código 2xx)
    return (httpCode > 0 && httpCode < 300);
}

void setup() {
    Serial.begin(115200);

    // Conecta-se à rede WiFi
    Serial.print("Conectando ao WiFi..");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConectado ao WiFi!");

    // Verificar conectividade da rede
    if (testNetworkConnectivity()) {
        Serial.println("Conectividade de rede bem-sucedida!");
    } else {
        Serial.println("Falha na conectividade de rede!");
        // Pode adicionar um código aqui para lidar com a falta de conectividade
        // (por exemplo, tentar reconectar ou outros procedimentos)
        return;
    }

    // Conectando ao broker MQTT
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    delay(9000);
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("O cliente %s se conecta ao broker MQTT\n", client_id.c_str());
        delay(9000);
        if (client.connect(client_id.c_str())) {
            Serial.println("Conectado ao broker MQTT!");
            client.publish(topic, "Olá do ESP32 via MQTT");
        } else {
            Serial.print("\nERRP: ");
            Serial.println(client.state());
            delay(9000);
        }
    }

    Serial.println("");
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }

    client.loop();
}

void reconnect() {
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("O cliente %s se conecta ao broker MQTT\n", client_id.c_str());
        if (client.connect(client_id.c_str())) {
            Serial.println("Conectado ao broker MQTT!");
            client.publish(topic, "Olá do ESP32 via MQTT");
        } else {
            Serial.print("\nERRP: ");
            Serial.println(client.state());
            delay(9000);
        }
    }
}