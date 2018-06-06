#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
     
const char* ssid     = "Falcao";
const char* password = "30062017";     

WiFiUDP udp;
long x = 0;
String data;

int wifiStatus;

void setup() {

    pinMode(D0, OUTPUT);
    pinMode(D4, OUTPUT);

    digitalWrite(D4, 1);

    Serial.begin(115200);
    delay(200);

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Your are connecting to; ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    udp.begin(555);
}   
     
void loop() {

    do_connect();
    do_send();
    do_listen();

}

void do_connect() {

    wifiStatus = WiFi.status();

    if(wifiStatus == WL_CONNECTED) {

        Serial.println("");
        Serial.println("Your ESP is connected!");  
        Serial.println("Your IP address is: ");
        Serial.println(WiFi.localIP());  

        digitalWrite(D0, HIGH);
        delay(100);
        digitalWrite(D0, LOW);
    }
    else {
        Serial.println("");
        Serial.println("WiFi not connected, trying again ...");
        WiFi.begin(ssid, password);
        digitalWrite(D0, HIGH);
        delay(1000);
        digitalWrite(D0, LOW);
    }

    delay(1000);
}

void do_send() {

    if (wifiStatus == WL_CONNECTED) {

        x = random(0, 1000);
        udp.beginPacket("192.168.1.2", 555);
        udp.println(x);
        udp.endPacket();

        Serial.print("Sending: ");
        Serial.println(x);

        digitalWrite(D4, LOW);
        delay(5);
        digitalWrite(D4, HIGH);
    }
    else {

        Serial.println("Connection failed");
        digitalWrite(D4, LOW);
        delay(150);
        digitalWrite(D4, HIGH);

    }

}

void do_listen() {

    if (udp.parsePacket() > 0)
    {
        data = "";

        while (udp.available() > 0)
        {
            char z = udp.read();
            data += z;
        }

        Serial.println("");
        Serial.println("");
        Serial.print("Received data: ");
        Serial.println(data);
        Serial.println("");
        Serial.println("");
    }
}