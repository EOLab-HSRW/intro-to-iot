#include <ESP8266WiFi.h>

// Define SECURE_CONNECTION: 1 for secure connection, 0 for unsecure
#define SECURE_CONNECTION 1

// Conditionally include secure or unsecure library
#if SECURE_CONNECTION
    #include <WiFiClientSecure.h>
    WiFiClientSecure wifi_client;
    const uint16_t HTTP_PORT = 443;
#else
    #include <WiFiClient.h>
    WiFiClient wifi_client;
    const uint16_t HTTP_PORT = 80;
#endif


// Replace with your WiFi credentials
const char* SSID = "harley"; // [USER INPUT]
const char* PASSWORD = "123456789"; // [USER INPUT]

// Replace with your API details
const char* API_HOST = "weather.eolab.de"; // [USER INPUT]
const char* API_ENDPOINT = "/api"; // [USER INPUT]

const uint8_t PERIOD_MINUTES = 1;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(SSID, PASSWORD);

  Serial.print("\n\nConnecting to ");
  Serial.print(SSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");

  #if SECURE_CONNECTION
    // Set the client to verify the server's certificate
    wifi_client.setInsecure();
  #endif
  // Give the client a chance to perform the handshake
  delay(1000);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    wifi_client.connect(API_HOST, HTTP_PORT);
    // Make an HTTPS GET request
    wifi_client.println("GET " + String(API_ENDPOINT) + " HTTP/1.1");
    wifi_client.println("Host: " + String(API_HOST));
    wifi_client.println("Connection: close");
    wifi_client.println();

    // Wait for the response
    while (wifi_client.connected()) {
      if (wifi_client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = wifi_client.read();
        Serial.print(c);
      }
    }

    wifi_client.stop();
  }

  // Wait for a while before making the next request
  delay(PERIOD_MINUTES * 60 * 1000); // convert from min to sec (60) and from sec to ms (1000)
}