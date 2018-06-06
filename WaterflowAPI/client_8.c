#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define HELLO_SERVER "0"
#define HI_THERE     "1"
#define WHATS_MY_ID  "2"

const char* ssid     = "Falcao";
const char* password = "30062017"; 
char * NODE_ID       = "";
IPAddress SERVER_IP;
WiFiUDP udp;

void setup() {

    Serial.begin(115200);
    delay(200);

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Your are connecting to: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println();
    Serial.print("Connected. ");
    Serial.println();

    WiFi.mode(WIFI_STA);

    do_broadcast();
}

void loop() {
    Serial.print("#");
}

void do_broadcast() {

    if (WiFi.status() == WL_CONNECTED)
    {
        IPAddress broadcastIP = ~WiFi.subnetMask() | WiFi.gatewayIP();

        Serial.println("==========================================");
        Serial.print("Broadcast Addr ::: ");
        Serial.println(broadcastIP);
        Serial.println("==========================================");

        udp.beginPacket(broadcastIP, 555);
        udp.write(HELLO_SERVER);
        udp.endPacket();

        Serial.println("==========================================");
        Serial.println("Sending broadcast ...");
        Serial.println("==========================================");

        while(udp.parsePacket() <= 0) {
            delay(500);
            Serial.print(".");
        }

        char * responseFromServer;

        while (udp.available() > 0)
        {
            char z = udp.read();
            responseFromServer += z;
        }

        SERVER_IP = udp.remoteIP();

        Serial.println("==========================================");
        Serial.print("Server: ");
        Serial.println(SERVER_IP);
        Serial.println("==========================================");

        if (responseFromServer == HI_THERE) {

            udp.beginPacket(SERVER_IP, 555);
            udp.write(WHATS_MY_ID);
            udp.endPacket();

            while(udp.parsePacket() <= 0) {
                delay(500);
                Serial.print(".");
            }

            char * responseId;

            while (udp.available() > 0)
            {
                char z = udp.read();
                responseId += z;
            }

            NODE_ID = responseId;

            Serial.println("==========================================");
            Serial.print("Node ID From Server: ");
            Serial.println(responseId);
            Serial.println("==========================================");
        }
        else {

            Serial.println("==========================================");
            Serial.println("Essa nao e a resposta que eu esperava :(");
            Serial.println("==========================================");

        }
    }
}

void do_send() {

}

void do_listen() {

}