#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define HELLO_SERVER "0"
#define HI_THERE     "1"
#define WHATS_MY_ID  "2"
     
const char* ssid     = "Falcao";
const char* password = "30062017";     

bool executeBroadcast = true;
long x;

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
        executeBroadcast = false;
        do_broadcast();
    }
  
    
    do_listen();
    do_send();

    Serial.println("");
    Serial.print("Servidor: ");
    Serial.println(SERVER_IP);
    Serial.println("");
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
        udp.write("hellooooooo");
        udp.endPacket();
        udp.flush();

        executeBroadcast = false;

        Serial.println("");
        Serial.print("Sending broadcast Hello");
        Serial.println("");

        digitalWrite(D4, LOW);
        delay(5);
        digitalWrite(D4, HIGH);
    }

}

void do_send() {

    if (wifiStatus == WL_CONNECTED) {

        x = random(0, 1000);
        
        Serial.print("Sending: ");
        Serial.print("@|");
        Serial.print(NODE_ID);
        Serial.print("|");
        Serial.print(x);
        Serial.print("@;");

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
        Serial.println(data);
        Serial.println("");

        if (strcmp(data, HI_THERE) == 0) {

            SERVER_IP = udp.remoteIP();

            Serial.println("");
            Serial.println(SERVER_IP);
            Serial.println("");

            udp.beginPacket(SERVER_IP, 555);
            udp.write("ooooooooooooooooooooooi");
            udp.endPacket();
            udp.flush();

            data = "";

            while(udp.parsePacket() <= 0);

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