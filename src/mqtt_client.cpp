#include "mqtt_client.h"
#include "config.h"
#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    // Si quisieras manejar mensajes entrantes más adelante
}

void mqtt_reconnect() {
    while (!client.connected()) {
        Serial.print("Conectando a MQTT...");
        if (client.connect(MQTT_CLIENT_ID)) {
            Serial.println(" conectado.");
            // client.subscribe("esp32/command"); // Si deseas escuchar comandos
        } else {
            Serial.print(" fallo, rc=");
            Serial.print(client.state());
            Serial.println(" intentando de nuevo en 5s...");
            delay(5000);
        }
    }
}

void mqtt_setup() {
    client.setServer(MQTT_BROKER, MQTT_PORT);
    client.setCallback(mqtt_callback);
}

void mqtt_loop() {
    if (!client.connected()) {
        mqtt_reconnect();
    }
    client.loop();
}

void mqtt_publish(const char* topic, const String& payload) {
    if (client.connected()) {
        client.publish(topic, payload.c_str(), true);  // `true` = mensaje retenido
    }
}

bool mqtt_is_connected() {
    return client.connected();
}
