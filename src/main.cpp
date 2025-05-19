#include <Arduino.h>
#include "wifi_manager.h"
#include "json_formatter.h"
#include "memory_monitor.h"
#include "mqtt_client.h"
#include "config.h"
#include "status_reporter.h"
#include "temperature_sensor.h"


// Tarea que imprime y publica estado WiFi
void wifiInfoTask(void *parameter) {
    while (true) {
        String wifiJson = generate_wifi_json();
        Serial.println("[wifi/status]");
        Serial.println(wifiJson);
        mqtt_publish(MQTT_TOPIC_WIFI, wifiJson);
        vTaskDelay(pdMS_TO_TICKS(WIFI_INFO_INTERVAL));
    }
}

// Tarea que imprime y publica estado de memoria
void memoryInfoTask(void *parameter) {
    while (true) {
        String memJson = generate_memory_json();
        Serial.println("[system/memory]");
        Serial.println(memJson);
        mqtt_publish(MQTT_TOPIC_MEMORY, memJson);
        vTaskDelay(pdMS_TO_TICKS(WIFI_INFO_INTERVAL));
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    wifi_init();
    mqtt_setup();

    // Tarea de WiFi
    xTaskCreatePinnedToCore(
        wifiInfoTask,
        "WiFiInfoTask",
        4096,
        NULL,
        1,
        NULL,
        1
    );

    // Tarea de memoria
    xTaskCreatePinnedToCore(
        memoryInfoTask,
        "MemoryInfoTask",
        4096,
        NULL,
        1,
        NULL,
        1
    );

    // Tarea de status (heartbeat MQTT)
    start_status_reporter_task();

    //Tarea para el sensor de temperatura
    start_temperature_task();

}

void loop() {
    mqtt_loop();  // Mantiene conexión activa y maneja mensajes entrantes
    vTaskDelay(pdMS_TO_TICKS(100));  // Retardo mínimo para liberar CPU
}
