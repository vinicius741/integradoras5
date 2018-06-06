#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
     
const char* ssid     = "Falcao";
const char* password = "30062017";     

WiFiUDP udp;
String data;

int sensorPin = A0;

int myvalue = 0;
int readedValue = 0;

int wifiStatus;

void setup() {

    pinMode(D4, OUTPUT);

    // 1 = Disable, 0 = Enable
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

    do_sensor();
    do_connect();
    do_send();
    do_listen();

    Serial.println("");
    Serial.print("My value: ");
    Serial.println(myvalue);
    Serial.print("Readed value: ");
    Serial.println(readedValue);

    if (myvalue > readedValue)
        // 1 = Disable, 0 = Enable
        digitalWrite(D4, 0);
    
    else
        // 1 = Disable, 0 = Enable
        digitalWrite(D4, 1);

}

void do_sensor() {

    myvalue = analogRead(sensorPin); 

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

        udp.beginPacket("192.168.1.2", 555);
        udp.println(myvalue);
        udp.endPacket();

        Serial.print("Sending: ");
        Serial.println(myvalue);

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

        readedValue = toInt(data);
    }
}

int toInt(char * str)
{
    int result;
    int puiss;

    result = 0;
    puiss = 1;

    while (('-' == (*str)) || ((*str) == '+'))
    {
        if (*str == '-')
        puiss = puiss * -1;
        str++;
    }

    while ((*str >= '0') && (*str <= '9'))
    {
      result = (result * 10) + ((*str) - '0');
      str++;
    }

    return (result * puiss);
}