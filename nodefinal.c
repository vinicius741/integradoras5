#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


const char* wifiName = "WiFi-Repeater";
const char* wifiPass = "10203040";

const char* targetUDP = "192.168.1.2";

char incomingPacket[255];

WiFiUDP udp;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    delay(10);
    Serial.println();

    Serial.print("Connecting to ");
    Serial.println(wifiName);

    WiFi.begin(wifiName, wifiPass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());  
}

void loop() {
    sendLDR(analogRead(A0));



    int packetSize = udp.parsePacket();

   








    Serial.printf("TAMANHO: %d\n", packetSize);
    Serial.printf(WiFi.status());
    if (packetSize)
    {
        // receive incoming UDP packets
        Serial.printf("Received %d bytes from %s, port %d\n", packetSize, udp.remoteIP().toString().c_str(), udp.remotePort());
        int len = udp.read(incomingPacket, 555);
        if (len > 0)
        {
        incomingPacket[len] = 0;
        }
        Serial.printf("UDP packet contents: %s\n", incomingPacket);
        if(incomingPacket[0] == '0')
        {
            delay(2000);
        }
        if(incomingPacket[0] == '1')
        {
            digitalWrite(LED_BUILTIN, LOW);
            delay(2000);
            digitalWrite(LED_BUILTIN, HIGH);
        }
        if(incomingPacket[0] == '2')
        {
            for(int i = 0;i<4;i++){
                delay(250);
                digitalWrite(LED_BUILTIN, LOW);
                delay(250);
                digitalWrite(LED_BUILTIN, HIGH); 
            }
            
        }

    }


    
    delay(1000);

}
void sendLDR(int dado){
    udp.beginPacket(targetUDP, 555);
    udp.println(dado);
    udp.endPacket();

    Serial.print("Sending: ");
    Serial.println(dado);
}
