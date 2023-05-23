// C++ code
//
int SonarTrigger = 7;
int SonarEcho = 6;

float distancia = 0;
int tempo = 0;

int led1 = 3;
int led2 = 4;
int led3 = 5;

float seno;
int frequencia;

void setup()
{
  pinMode(SonarTrigger, OUTPUT);
  pinMode(SonarEcho, INPUT);
  pinMode(8,OUTPUT);
  Serial.begin(9600);
}

 void buz(){
   if (distancia < 40){
   		for(int x=0; x<180; x++){
      seno = (sin(x*3.1416/180));
      frequencia = 2000+(int(seno*1000));
      tone(8,frequencia);
      delay(1);
    }
   }else{	
      noTone(8);
   }
	
}

void loop()
  
{
  digitalWrite(SonarTrigger, LOW);
  delay(200); // Wait for 1000 millisecond(s)
  digitalWrite(SonarTrigger, HIGH);
  delay(100); // Wait for 1000 millisecond(s)
  digitalWrite(SonarTrigger, LOW);

  tempo = pulseIn(SonarEcho,HIGH);
  distancia = tempo/58.2;
  
  if (distancia < 40){
    digitalWrite(3,LOW);
  	digitalWrite(5,HIGH);
    digitalWrite(4,LOW);
    
    buz();
    
  }else if (distancia > 40 && distancia < 80){
  	digitalWrite(4,HIGH);
  	digitalWrite(3,LOW);
    digitalWrite(5,LOW);
    buz();
    
  }else if (distancia > 80){
   	digitalWrite(4,LOW);
  	digitalWrite(5,LOW);
    digitalWrite(3,HIGH); 
    buz();
  }
  Serial.print("Distancia média: ");
  Serial.print(distancia);
  if (distancia <= 100 ){
  	Serial.println(" cm");
  } else {
    Serial.println(" metros");
  }
  
  delay(500);
}