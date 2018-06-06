#include <ESP8266WiFi.h>//Biblioteca do WiFi.
#include <WiFiUdp.h>//Biblioteca do UDP.
 
WiFiUDP udp;//Cria um objeto da classe UDP.
 
String req;//String que armazena os dados recebidos pela rede.
 
void setup()
{
   pinMode(D4, OUTPUT);//Habilita o LED onboard como saida.
   digitalWrite(D4, 1);//Desliga o LED.
 
   Serial.begin(115200);//Habilita a comunicaçao serial para a string recebida ser lida no Serial monitor.
 
   WiFi.mode(WIFI_AP);//Define o ESP8266 como Acess Point.
   WiFi.softAP("NodeMCU", "");//Cria um WiFi de nome "NodeMCU" e sem senha.
   delay(2000);//Aguarda 2 segundos para completar a criaçao do wifi.
 
   udp.begin(555);//Inicializa a recepçao de dados UDP na porta 555
}
 
void loop()
{
   listen();//Sub-rotina para verificar a existencia de pacotes UDP.
}
 
void listen()//Sub-rotina que verifica se há pacotes UDP's para serem lidos.
{
   if (udp.parsePacket() > 0)//Se houver pacotes para serem lidos
   {
       req = "";//Reseta a string para receber uma nova informaçao
       while (udp.available() > 0)//Enquanto houver dados para serem lidos
       {
           char z = udp.read();//Adiciona o byte lido em uma char
           req += z;//Adiciona o char à string
       }
 
       //Após todos os dados serem lidos, a String estara pronta.
 
       Serial.println(req);//Printa a string recebida no Serial monitor.
 
       digitalWrite(D4, 0);//-
       delay(5);//-
       digitalWrite(D4, 1);//Pisca o LED rapidamente apos receber a string.
    }
}