// inclusão da biblioteca do lcd
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
// WiFi - configurações de WI-FI
const char ssid[] = "login";
const char psw[] = "senha";

// Site remoto - Dados do site que vai receber a requisição POST ou GET
const char http_site[] = "http://localhost/processa.php";
const int http_port = 8080;

// Variáveis globais
WiFiClient client;
IPAddress server(192, 168, 0, 23); // Endereço IP do servidor - http_site

#define botao 1
int valBotao;

int SonarTrigger = 7;
int SonarEcho = 6;

float distancia = 0;
int tempo = 0;
float altPadrao = 1.84;
float altura = 0;
float alturaPessoa;

float seno;
int frequencia;

void setup(){
  // Tenta conexão com Wi-fi
    Serial.begin(9600);
    WiFi.begin(ssid, psw);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(100);
      Serial.print(".");
    }
    Serial.print("\nWI-FI conectado com sucesso: ");
    Serial.println(ssid);
    delay(500);
  // -------------------------
  pinMode(botao, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  pinMode(SonarTrigger, OUTPUT);
  pinMode(SonarEcho, INPUT);
  pinMode(8, OUTPUT);
}

void display(){
  lcd.setCursor(1, 0);
  lcd.print("Voce mede: ");
  lcd.print(altura);
  Serial.print("Voce mede:");
  Serial.print(altura);
  if (altura < 1.00){
    lcd.setCursor(0, 1);
    lcd.print("");
    lcd.print("centimetros");
    Serial.println(" cm");
  }else{
    lcd.setCursor(0, 1);
    lcd.print("");
    lcd.print("     metros ");
    Serial.println(" metros         ");
  }

  delay(500);
}

void enviaphp(){
  // Construa a string de URL com os parâmetros
  String url = "http://localhost/ProjetoPrincipalTemp/processo.php?";
  url += "alturaPessoa=";
  url += alturaPessoa;

  // Envie a string de URL pela porta serial
  Serial.println(url);
}

void loop(){
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

  if (valBotao == 1){
    // Envio dos dados do sensor para o servidor via GET - duplicado temporariamente pq os dados tem q ser enviados somente quando clicado no botao
    if ( !getPage((float)alturaPessoa) ) {
      Serial.println("GET request failed");
    }
  } else {
    // Serial.print("");
    // Serial.println("");
  }

//função para mostrar a altura medida no momento atual no display 
  display();

///////////////////////
// Envio dos dados do sensor para o servidor via GET
  if ( !getPage((float)alturaPessoa) ) {
    Serial.println("GET request failed");
  }
}

// Executa o HTTP GET request no site remoto
bool getPage(float alturaPessoa) {
  if ( !client.connect(server, http_port) ) {
    Serial.println("Falha na conexao com o site ");
    return false;
  }
  String param = "?altura=" + String(alturaPessoa); //Parâmetros com as leituras
  Serial.println(param);
  client.println("GET /processoAltura.php" + param + " HTTP/1.1");
  client.println("Host: ");
  client.println(http_site);
  client.println("Connection: close");
  client.println();
  client.println();

  // Informações de retorno do servidor para debug
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  return true;
}