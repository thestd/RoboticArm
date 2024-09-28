#include <esp_now.h>
#include <WiFi.h>

// MAC address of the receiver
uint8_t receiverMac[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Structure to hold the message
typedef struct {
    uint8_t sequence;
    char text[32];
} Message_t;

Message_t txMessage;

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

    // Register peer
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, receiverMac, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop() {
    // Prepare the message
    strcpy(txMessage.text, "Hello from ESP32");

    // Send the message
    esp_err_t result = esp_now_send(receiverMac, (uint8_t *) &txMessage, sizeof(txMessage));

    // Increment sequence for the next message
    txMessage.sequence++;
    
    if (result == ESP_OK) {
        Serial.println("Message sent successfully");
    } else {
        Serial.println("Error sending the message");
    }

    delay(500);
}