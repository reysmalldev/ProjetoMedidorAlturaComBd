/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/
// inclusão da biblioteca do lcd
#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 4, 0, 2, 14, 12);

#define botao 16
int valBotao = 0;

int SonarTrigger = 15;
int SonarEcho = 13;

float distancia = 0;
int tempo = 0;
float altPadrao = 1.84;
float altura = 0;
float alturaPessoa;

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#ifndef STASSID
#define STASSID "ANDRADE"
#define STAPSK "192530Pecf"
#endif

// Site remoto - Dados do site que vai receber a requisição POST ou GET
const char http_site[] = "http://fe80::1%2";
const int http_port = 8080;

WiFiClient client;
IPAddress server(192, 168, 10, 6); // Endereço IP do servidor - http_site

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "djxmmx.net";
const uint16_t port = 17;

void setup() {
  Serial.begin(115200);

  // Começamos conectando-nos a uma rede WiFi

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Defina explicitamente o ESP8266 como um cliente WiFi, caso contrário, por padrão,
     tentaria agir tanto como cliente quanto como ponto de acesso e poderia causar
     problemas de rede com seus outros dispositivos WiFi em sua rede WiFi. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(botao, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  pinMode(SonarTrigger, OUTPUT);
  pinMode(SonarEcho, INPUT);
  pinMode(5, OUTPUT);
}

void display()
{
  lcd.setCursor(1, 0);
  lcd.print("Voce mede: ");
  lcd.print(altura);
  Serial.print("Voce mede:");
  Serial.print(altura);
  if (altura < 1.00)
  {
    lcd.setCursor(0, 1);
    lcd.print("");
    lcd.print("centimetros");
    Serial.println(" cm");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("");
    lcd.print("     metros ");
    Serial.println(" metros         ");
  }

  delay(500);
}

void loop() {
  valBotao = digitalRead(botao); // quando o botao for clicado recebera 1 se nao 0

  digitalWrite(SonarTrigger, LOW);
  delay(200);
  digitalWrite(SonarTrigger, HIGH);
  delay(100);
  digitalWrite(SonarTrigger, LOW);

  // Calculo da altura
  tempo = pulseIn(SonarEcho, HIGH);
  distancia = (tempo / 58.2) / 100;
  altura = altPadrao - distancia;

  // comando para quando clicar no botão salvar a altura desejada e futuramente enviar para o banco de dados
  if (pinBotao1Retencao())
  {
    if (!getPage((float)alturaPessoa))
    {
      Serial.println("GET request failed");
    }
  }

  if (pinBotao1Retencao()) {
    if (!getPage((float)alturaPessoa))
    {
      Serial.println("GET request failed");
    }
  	alturaPessoa = altura;
    Serial.println(valBotao);
    Serial.print("altura salva e: ");
    Serial.println(alturaPessoa);
  }

  display();
  
  delay(1000);
}

// Executa o HTTP GET request no site remoto
bool getPage(float alturaPessoa)
{
  if (!client.connect(server, http_port))
  {
    Serial.println("Falha na conexao com o site ");
    return false;
  }
  String param = "?alturaPessoa=" + String(alturaPessoa); // Parâmetros com as leituras
  Serial.println(param);
  client.println("localhost/Altura/processo.php" + param + " HTTP/1.1");
  client.println("Host: ");
  client.println(http_site);
  client.println("Connection: close");
  client.println();
  client.println();

  // Informações de retorno do servidor para debug
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  return true;
}

bool pinBotao1Retencao() {
   #define tempoDebounce 50 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)

   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static bool estadoRet = true;
   static unsigned long delayBotao = 0;

   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(botao);
       if ( estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
          estadoRet = !estadoRet;
          delayBotao = millis();
       }
       estadoBotaoAnt = estadoBotao;
   }

   return estadoRet;
}
