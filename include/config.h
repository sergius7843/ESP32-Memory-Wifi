#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials
#define WIFI_SSID     "Nombre de tu red wifi"
#define WIFI_PASSWORD "Contraseña de tu red wifi"

// Intervalo de actualización de información WiFi (en milisegundos)
#define WIFI_INFO_INTERVAL 5000

//para el broker
#define MQTT_BROKER     "La IP de tu broker"   // IP o dominio del broker
#define MQTT_PORT       1883                   // indica tu puerto, lo normal es 1883 para mqtt y 9001 para 
                                               // websockets, pero como es una ESP32 enviando datos a un broker con 1883 esta bien 
#define MQTT_CLIENT_ID  "esp32_device_01"

//TOPICS

//TOPIC WIFI
#define MQTT_TOPIC_WIFI   "esp32/wifi/status"

//TOPIC MEMORIA
#define MQTT_TOPIC_MEMORY "esp32/system/memory"


#endif // CONFIG_H
