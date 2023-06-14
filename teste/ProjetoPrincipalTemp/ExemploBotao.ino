#define pinBotao1 13
#define pinLED1   10

#define pinBotao2 12
#define pinLED2   9

#define pinBotao3 11
#define pinLED3   8

bool pinBotao1Retencao();
bool pinBotao2Retencao();
bool pinBotao3Retencao();

void setup() {
  pinMode(pinBotao1, INPUT_PULLUP);
  pinMode(pinBotao2, INPUT_PULLUP);
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
}


void loop() {

   if (pinBotao1Retencao()) {
      digitalWrite(pinLED1, HIGH);
   } else {
      digitalWrite(pinLED1, LOW);
   }


   if (pinBotao2Retencao()) {
      digitalWrite(pinLED2, HIGH);
   } else {
      digitalWrite(pinLED2, LOW);
   }

   if (pinBotao3Retencao()) {
      digitalWrite(pinLED3, HIGH);
   } else {
      digitalWrite(pinLED3, LOW);
   }

}


bool pinBotao1Retencao() {
   #define tempoDebounce 50 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)

   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static bool estadoRet = true;
   static unsigned long delayBotao = 0;

   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(pinBotao1);
       if ( estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
          estadoRet = !estadoRet;
          delayBotao = millis();
       }
       estadoBotaoAnt = estadoBotao;
   }

   return estadoRet;
}


bool pinBotao2Retencao() {
   #define tempoDebounce 50 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)

   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static bool estadoRet = true;
   static unsigned long delayBotao = 0;

   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(pinBotao2);
       if ( estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
          estadoRet = !estadoRet;
          delayBotao = millis();
       }
       estadoBotaoAnt = estadoBotao;
   }

   return estadoRet;
}

bool pinBotao3Retencao() {
   #define tempoDebounce 50 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)

   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static bool estadoRet = true;
   static unsigned long delayBotao = 0;

   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(pinBotao3);
       if ( estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
          estadoRet = !estadoRet;
          delayBotao = millis();
       }
       estadoBotaoAnt = estadoBotao;
   }

   return estadoRet;
}

