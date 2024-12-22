#include <WiFi.h>
#include <HTTPClient.h>
#include <Seeed_Arduino_SSCMA.h>


// Replace with your WiFi credentials
const char* ssid = "your ssid name";
const char* password = "your password";


// Replace with your Telegram Bot Token and Chat ID
const char* telegramBotToken = "your token id";
const char* chatID = "your chat id";


SSCMA AI;
int personLimit = 10; // Set the limit of people


void sendTelegramMessage(const char* message) {
    // Create the Telegram API URL
    String telegramURL = String("https://api.telegram.org/bot") + telegramBotToken +
                         "/sendMessage?chat_id=" + chatID + "&text=" + message;


    // Send the HTTP GET request
    HTTPClient http;
    http.begin(telegramURL);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
        Serial.print("Telegram message sent, response code: ");
        Serial.println(httpResponseCode);
    } else {
        Serial.print("Error sending message, response code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}


void setup() {
    // Initialize serial communication and WiFi
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");


    // Initialize the AI module
    AI.begin();
}


void loop() {
    if (!AI.invoke()) { // If the AI successfully processes the image
        Serial.println("invoke success");


        // Count the number of people detected
        int numberOfPeople = AI.boxes().size();
       
        // Print the number of people detected
        Serial.print("Number of people detected: ");
        Serial.println(numberOfPeople);


        // Check if the number of detected people exceeds the limit
        if (numberOfPeople > personLimit) {
            // If more than the limit, send an alert
            Serial.println("ALERT: Person limit exceeded!");


            // Send a notification to Telegram
            String alertMessage = "ALERT: Person limit exceeded! Detected " +
                                  String(numberOfPeople) + " people.";
            sendTelegramMessage(alertMessage.c_str());
        }
    }
}
