//inclusão da biblioteca do lcd
#include <LiquidCrystal.h> 
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
  
// C++ code
//


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

void setup()
{
  pinMode(botao, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  pinMode(SonarTrigger, OUTPUT);
  pinMode(SonarEcho, INPUT);
  pinMode(8,OUTPUT);
  Serial.begin(9600);
}

void display(){
  lcd.setCursor(1,0);
  lcd.print("Voce mede: ");
  lcd.print(altura);
  Serial.print("Voce mede:");
  Serial.print(altura);
  if (altura < 1.00 ){
    lcd.setCursor(0,1);
    lcd.print("");
  	lcd.print("centimetros");
    Serial.println(" cm");
  } else {
    lcd.setCursor(0,1);
    lcd.print("");
    lcd.print("     metros ");
    Serial.println(" metros         ");
  }
  
  delay(500);
}

void loop(){
  valBotao = digitalRead(botao); // quando o botao for clicado recebera 1 se nao 0

  digitalWrite(SonarTrigger, LOW);
  delay(200); 
  digitalWrite(SonarTrigger, HIGH);
  delay(100); 
  digitalWrite(SonarTrigger, LOW);

  //Calculo da altura 
  
  tempo = pulseIn(SonarEcho,HIGH);
  distancia = (tempo/58.2)/100;
  altura = altPadrao - distancia;

  // comando para quando clicar no botão salvar a altura desejada e futuramente enviar para o banco de dados

  if (valBotao == 1) {
  	alturaPessoa = altura;
    //Serial.print("altura salva e: ");
    //Serial.println(alturaPessoa);
  } else {
    //Serial.print("");
    //Serial.println("");
  }
  
  display();
}