#include <esp_now.h>
#include <WiFi.h>

// Structure to hold the incoming message
typedef struct {
    uint8_t sequence;
    char text[32];
} Message_t;

Message_t rxMessage;

// Callback function to receive data
void onDataReceive(const uint8_t *mac, const uint8_t *rxData, int len) {
    memcpy(&rxMessage, rxData, sizeof(rxMessage));
    Serial.print("New message! Sequence:");
    Serial.print(rxMessage.sequence);
    Serial.print("Text: ");
    Serial.println(rxMessage.text);
}

void setup() {
    Serial.begin(115200);

    // Initialize WiFi in station mode
    WiFi.mode(WIFI_STA);
    Serial.println(WiFi.macAddress());

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register receive callback
    esp_now_register_recv_cb(onDataReceive);
}

void loop() {
}