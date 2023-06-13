/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/
// inclusão da biblioteca do lcd
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(5, 4, 0, 2, 14, 12);

#define botao 16

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

int SonarTrigger = 12;
int SonarEcho = 14;

long duration;
float distanceCm;
float distanceInch;

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "ANDRADE"
#define STAPSK "192530Pecf"
#endif

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
  //lcd.begin(16, 2);
  //lcd.setCursor(0, 0);
  pinMode(SonarTrigger, OUTPUT);
  pinMode(SonarEcho, INPUT);
 // pinMode(5, OUTPUT);
}

void loop() {
  // Clears the trigPin
  digitalWrite(SonarTrigger, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(SonarTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(SonarTrigger, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(SonarEcho, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  
  delay(1000);
}
