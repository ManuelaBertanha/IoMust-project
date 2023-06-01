//Incluir bibliotecas
#include <EspMQTTClient.h>

//Definicoes e constantes
char SSIDName[] = "Wokwi-GUEST"; //nome da rede WiFi
char SSIDPass[] = ""; //senha da rede WiFI

const int BUTTON_PIN_1 = 25;
const int BUTTON_PIN_2 = 26;
const int BUTTON_PIN_3 = 27;

char BrokerURL[] = "broker.hivemq.com"; //URL do broker MQTT
char BrokerUserName[] = "manu"; //nome do usuario para autenticar no broker MQTT
char BrokerPassword[] = "123"; //senha para autenticar no broker MQTT
char MQTTClientName[] = "mqtt-mack-pub"; //nome do cliente MQTT
int BrokerPort = 1883; //porta do broker MQTT

String TopicoPrefixo = "ATV182713MUSIC"; //prefixo do topico
String Topico = TopicoPrefixo+"/GeneroMusical"; //nome do topico

//Variaveis globais e objetos
String Genero = "";
int Comando_1;
int Comando_2;
int Comando_3;

EspMQTTClient clienteMQTT(SSIDName, SSIDPass, BrokerURL, BrokerUserName, BrokerPassword, MQTTClientName, BrokerPort); //inicializa o cliente MQTT

//Metodos

//Este prototipo de funcao deve estar sempre presente
void onConnectionEstablished() {
}

void enviarDados() {
  Comando_1 = digitalRead(BUTTON_PIN_1);
  if (Comando_1 == HIGH) {
    Genero = "POP";
    Serial.println(Comando_1);
    Serial.println(Genero);
    clienteMQTT.publish(Topico, String(Genero));
    Comando_1 = LOW;
  }
  Comando_2 = digitalRead(BUTTON_PIN_2);
  if (Comando_2 == HIGH) {
    Genero = "MPB";
    Serial.println(Comando_2);
    Serial.println(Genero);
    clienteMQTT.publish(Topico, String(Genero));
    Comando_2 = LOW;
  }
  Comando_3 = digitalRead(BUTTON_PIN_3);
  if (Comando_3 == HIGH) {
    Genero = "SERTANEJO";
    Serial.println(Comando_3);
    Serial.println(Genero);
    clienteMQTT.publish(Topico, String(Genero));
    Comando_3 = LOW;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
  pinMode(BUTTON_PIN_3, INPUT);
  clienteMQTT.enableDebuggingMessages();
}

void loop() {
  clienteMQTT.loop(); //funcao necessaria para manter a conexao com o broker MQTT ativa e coletar as mensagens recebidas
  enviarDados(); //funcao para publicar os dados no broker MQTT

  if (clienteMQTT.isWifiConnected() == 1) {
    Serial.println("Conectado ao WiFi!");
  } else {
    Serial.println("Nao conectado ao WiFi!");
    delay(4000);
  }

  if (clienteMQTT.isMqttConnected() == 1) {
    Serial.println("Conectado ao broker MQTT!");
  } else {
    Serial.println("Nao conectado ao broker MQTT!");
    delay(4000);
  }
}