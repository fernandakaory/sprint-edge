
#include <WiFi.h>
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient
 
//defines:
//defines de id mqtt e tópicos para publicação e subscribe denominado TEF(Telemetria e Monitoramento de Equipamentos)
#define TOPICO_SUBSCRIBE    "/TEF/sensor_infravermelho0.2/cmd"        //tópico MQTT de escuta
#define TOPICO_PUBLISH      "/TEF/sensor_infravermelho0.2/attrs"      //tópico MQTT de envio do tópico para ativar ou desativar o sensor até o Broker
#define TOPICO_PUBLISH_2    "/TEF/sensor_infravermelho0.2/attrs/a"    //tópico MQTT de envio da quantidade de passageiros para o Broker
#define TOPICO_PUBLISH_3    "/TEF/sensor_infravermelho0.2/attrs/l"    //tópico MQTT de envio da lotação para Broker
                                                      //IMPORTANTE: recomendamos fortemente alterar os nomes
                                                      //            desses tópicos. Caso contrário, há grandes
                                                      //            chances de você controlar e monitorar o ESP32
                                                      //            de outra pessoa.
#define ID_MQTT  "fiware_0.2"      //definição do id mqtt

// WIFI
const char* SSID = "Helena"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "maria@210259"; // Senha da rede WI-FI que deseja se conectar
  
// MQTT
const char* BROKER_MQTT = "46.17.108.113"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT
 
int D4 = 2;

//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
char EstadoSaida = '0';  //variável que armazena o estado atual da saída
  
//Prototypes
void initSerial();
void initWiFi();
void initMQTT();
void reconectWiFi(); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);
 
//Declaração das variáveis
const int sensor1 = 34;
const int sensor2 = 4;
int contador = 0;
bool estado=false;
bool estadoAnt=false;  
bool estado2=false;
bool estadoAnt2=false; 
void setup() 
{
    //inicializações:
    InitOutput();
    initSerial();
    initWiFi();
    initMQTT();
    delay(5000);
    MQTT.publish(TOPICO_PUBLISH, "s|on");
    pinMode(sensor1, INPUT);
}
  
//Função: inicializa comunicação serial com baudrate 115200 (para fins de monitorar no terminal serial 
//        o que está acontecendo.
//Parâmetros: nenhum
//Retorno: nenhum
void initSerial() 
{
    Serial.begin(115200);
}
 
//Função: inicializa e conecta-se na rede WI-FI desejada
//Parâmetros: nenhum
//Retorno: nenhum
void initWiFi() 
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
     
    reconectWiFi();
}
  
//Função: inicializa parâmetros de conexão MQTT(endereço do 
//        broker, porta e seta função de callback)
//Parâmetros: nenhum
//Retorno: nenhum
void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}
  
// Função: função de callback 
//        esta função é chamada toda vez que uma informação de 
//        um dos tópicos subescritos chega)
// Parâmetros: nenhum
// Retorno: nenhum
bool sensorAtivo = false;
void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
     
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
    
    Serial.print("- Mensagem recebida: ");
    Serial.println(msg);
    
    // Variável de controle para ativar/desativar o sensor

    //toma ação dependendo da string recebida:
   // Verifica a mensagem recebida e ativa ou desativa o sensor infravermelho
    if (msg.equals("sensor_infravermelho0.2@on|")) {
       // digitalWrite(sensor1, LOW); // Ativa o sensor (pino D4)
        EstadoSaida = '1';
        sensorAtivo = true;
    }

    if (msg.equals("sensor_infravermelho0.2@off|")) {
       // digitalWrite(sensor1, HIGH); // Desativa o sensor (pino D4)
        EstadoSaida = '0';
        sensorAtivo = false;
    }
     
}
  
//Função: reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
//        em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.
//Parâmetros: nenhum
//Retorno: nenhum
void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(5000);
        }
    }
}
  
//Função: reconecta-se ao WiFi
//Parâmetros: nenhum
//Retorno: nenhum
void reconectWiFi() 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
       // Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}
 
//Função: verifica o estado das conexões WiFI e ao broker MQTT. 
//        Em caso de desconexão (qualquer uma das duas), a conexão
//        é refeita.
//Parâmetros: nenhum
//Retorno: nenhum
void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
     
     reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}
 
//Função: envia ao Broker o estado atual do output 
//Parâmetros: nenhum
//Retorno: nenhum
void EnviaEstadoOutputMQTT(void)
{
    if (EstadoSaida == '1')
    {
      MQTT.publish(TOPICO_PUBLISH, "s|on");
      //Serial.println("Contagem iniciada");
    }
    if (EstadoSaida == '0')
    {
      MQTT.publish(TOPICO_PUBLISH, "s|off");
      Serial.println("Contagem desativada");
    }
    //Serial.println("- Estado do sensor enviado ao broker!");
    //delay(1000);
}
 
//Função: inicializa o output em nível lógico baixo
//Parâmetros: nenhum
//Retorno: nenhum
void InitOutput(void)
{
    //IMPORTANTE: o Led já contido na placa é acionado com lógica invertida (ou seja,
    //enviar HIGH para o output faz o Led apagar / enviar LOW faz o Led acender)
    pinMode(D4, OUTPUT);
    digitalWrite(D4, HIGH);
    
    boolean toggle = false;

    for(int i = 0; i <= 10; i++)
    {
        toggle = !toggle;
        digitalWrite(D4,toggle);
        delay(200);           
    }
}

//programa principal
void loop() 
{     
    char msgBuffer[5];
    //garante funcionamento das conexões WiFi e ao broker MQTT
    VerificaConexoesWiFIEMQTT();
 
    //envia o status de todos os outputs para o Broker no protocolo esperado
    EnviaEstadoOutputMQTT();

//realiza a leitura dos sensores e atualiza o contador    
    if (sensorAtivo){
      estado= !digitalRead(sensor1);
      estado2= !digitalRead(sensor2);
      if (estado && !estadoAnt){
          contador++;
          Serial.print("Passageiros: ");
          Serial.println(contador);
          delay(1000);
      }
      estadoAnt = estado;

      if (estado2 && !estadoAnt2 && contador>0){
        contador = contador-1;
        Serial.print("Passageiros: ");
        Serial.println(contador);
        delay(1000);
      }
      estadoAnt2 = estado2;

//envia o tópico de lotação por mqtt
      if(contador <= 10){
        MQTT.publish(TOPICO_PUBLISH_3, "VAZIO");
      } else if(contador <= 20){
        MQTT.publish(TOPICO_PUBLISH_3, "MEDIANO");
      } else if(contador <= 30){
        MQTT.publish(TOPICO_PUBLISH_3, "LOTADO");
      } else {
      contador = 0; // Reinicia o contador quando atinge 30 pessoas
      }
      //se o sensor for desligado, zera o contador e a lotação muda para "vazio"
    } else if (!sensorAtivo) {
      contador = 0;
      MQTT.publish(TOPICO_PUBLISH_3, "VAZIO");
    }

    //faz envio do tópico do contador, ou seja, da quantidade de passageiros
    sprintf(msgBuffer, "%d", contador);
    MQTT.publish(TOPICO_PUBLISH_2,msgBuffer);

    //keep-alive da comunicação com broker MQTT
    MQTT.loop();
    delay(100);
}
