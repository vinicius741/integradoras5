#include <ESP8266WiFi.h>//Biblioteca do WiFi.
#include <WiFiUdp.h>//Biblioteca do UDP.
 
WiFiUDP udp;//Cria um objeto da classe UDP.
String req;//String que armazena os dados recebidos pela rede.
long x;//Variavel para ser enviada.
 
void setup()
{
    Serial.begin(115200);
    delay(200);

   pinMode(D4, OUTPUT);//Habilita o LED onboard como saida.
   digitalWrite(D4, 1);//Desliga o LED.
 
   WiFi.mode(WIFI_STA);//Define o ESP8266 como Station.
   udp.begin(555);//Inicializa a recepçao de dados UDP na porta 555
}
 
void loop()
{
    // |@ARDUINO_ID@READING@RELAY_STATUS@;
    // |@0xADE12380@710.300@111111111111@;

    connect(); //Sub-rotina para conectar-se ao host.

    listen(); //Sub-rotina para ouvir os dados do host.

    send(); //Sub-rotina para enviar os dados ao host.
}
 
void connect()//Sub-rotina para verificar a conexao com o host.
{
   if (WiFi.status() != WL_CONNECTED)//Caso nao esteja conectado ao host, ira se conectar.
   {
      Serial.println("Tentando se conectar");
      WiFi.begin("Falcao", "30062017");//Conecta à rede do host.
      delay(2000);//Espera ate que a conexao seja feita.
   }
   else
   {
        Serial.println("Your IP address is: ");
        Serial.println(WiFi.localIP());  
   }
}
 
void send()//Sub-rotina para enviar dados ao host.
{
   if (WiFi.status() == WL_CONNECTED)//Só ira enviar dados se estiver conectado.
   {
      x = random(0, 1000);//Gera um numero aleatorio entre 0 e 1000.
      udp.beginPacket("192.168.1.2", 555);//Inicializa o pacote de transmissao ao IP e PORTA.
      udp.println(x);//Adiciona-se o valor ao pacote.
      udp.endPacket();//Finaliza o pacote e envia.
 
      Serial.println("Conexao feita.");
      digitalWrite(D4, 0);//-
      delay(150);//-
      digitalWrite(D4, 1);//Pisca o led rapidamente apos enviar.
   }
   else//Caso nao esteja com uma conexao estabelicida ao host, piscara lentamente.
   {
      Serial.println("Conexao falhou.");
      digitalWrite(D4, 0);
      delay(850);
      digitalWrite(D4, 1);
   }
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