/*
* Entrada analógica
* Liga e desliga um LED conectado ao pino digital 13. O tempo
* que o LED permanece ligado ou desligado depende do valor
* obtido pelo analogRead().
*/


int potPin = 0; // selecione o pino de entrada ao potenciômetro
int ledPin = 13;   // selecione o pino ao LED
float val = 0;    // variável a guardar o valor proveniente do sensor
float vin = 5;
float vout = 0;
float A = 1.112272865*pow(10,-3);
float B = 2.375809102*pow(10,-4);
float C = 0.6852858650*pow(10,-7);
float Rntc = 0;
float temp = 0;
float temperatura = 0;

void setup() {
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);  // declarar o pino ledPin como saída
}

float lerTemperatura(float R){
  return  pow(A + B*log(R) + C*pow(log(R), 3),-1);
}
 

void loop() {

 
 val = analogRead(potPin); // ler o valor do potenciômetro
 vout = vin*(val/1023);
 //Rntc = 10000*(1023/vout - 1);
 //temperatura = lerTemperatura(Rntc);

 Rntc = ((1023/val) - 1)*10000;
 Serial.println(Rntc);
 if (Rntc > 10000){
  digitalWrite(ledPin, HIGH);
  }else{
  digitalWrite(ledPin, LOW);  // desligar o led
  } 
 delay(500);                  // espera tempo ajustado no potenciometro

}
