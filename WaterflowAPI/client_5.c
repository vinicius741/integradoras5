#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
     
const char* ssid     = "Falcao";
const char* password = "30062017";     

bool executeBroadcast = true;

IPAddress SERVER_IP;
char* NODE_ID;
char* data;

WiFiUDP udp;
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
}   
     
void loop() {

    do_connect();

  
    if (executeBroadcast)
    {
        do_broadcast();
    }
  
    
    do_listen();
}

void do_connect() {

    wifiStatus = WiFi.status();

    if(wifiStatus == WL_CONNECTED) {

        Serial.println("");
        Serial.println("Your node is connected!");  
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

        executeBroadcast = true;
    }

    delay(1000);
}

void do_broadcast() {

    if (wifiStatus == WL_CONNECTED) {

        IPAddress enrr = ~WiFi.subnetMask() | WiFi.gatewayIP();
        Serial.println(enrr);

        udp.beginPacket(enrr, 555);
        udp.println("Hello, Server!");
        udp.endPacket();

        executeBroadcast = false;

        Serial.print("Sending broadcast Hello");

        digitalWrite(D4, LOW);
        delay(5);
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

        if (strcmp(data, "Hi, there!") == 0) {

            SERVER_IP = udp.remoteIP();
            udp.beginPacket(SERVER_IP, 555);
            udp.println("What's my ID?");
            udp.endPacket();

            data = "";

            while (udp.available() > 0)
            {
                char z = udp.read();
                data += z;
            }

            Serial.print("ID received: ");
            Serial.println(data);
            NODE_ID = data;
        }
        else {

            Serial.println("");
            Serial.println("");
            Serial.print("Received data: ");
            Serial.println(data);
            Serial.println("");
            Serial.println("");

        }

    }
}