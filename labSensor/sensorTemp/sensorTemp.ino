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
float R0 = 10000;
float temperatura = 0;
float temperatura1 = 0;
long int temperatura2 = 0;
float B_1 = 3950;
unsigned long time1, time2;

void setup() {
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);  // declarar o pino ledPin como saída
}

float tempSteinhartHart(float R){
  return  pow(A + B*log(R) + C*pow(log(R), 3),-1);
}
 
float tempBparameter(float R){
  return 1/(1/298.15 + (1/B_1)*log(R/R0));
}

long int tempBparameterInt(float R){
  return 1000/(1000/298.15 + (1000/(B_1))*log(R/(R0)));
}

void loop() {
 
 val = analogRead(potPin); // ler o valor do potenciômetro
 //vout = vin*(val/1023);
 //Rntc = 10000*(1023/vout - 1);
 //temperatura = lerTemperatura(Rntc);
 Rntc = ((1023/val) - 1)*10000;


 time1 = millis();
 digitalWrite(ledPin, HIGH);
 temperatura = tempSteinhartHart(Rntc);
 
 digitalWrite(ledPin, LOW);
 delay(2);
 time2 = millis();
 Serial.print(time2 - time1);
 Serial.print(" Steinhart = ");
 Serial.println(temperatura-273);
 delay(1000);

 time1 = millis();
 digitalWrite(ledPin, HIGH);
 
 temperatura1 = tempBparameter(Rntc);
 
 digitalWrite(ledPin, LOW);
 delay(2);
 time2 = millis();
 
 
 Serial.print(time2-time1);
 
 Serial.print(" parametro B = ");
 Serial.println(temperatura1-273);

 time1 = millis();
 digitalWrite(ledPin, HIGH);
 temperatura2 = tempBparameterInt(Rntc);
 digitalWrite(ledPin, LOW);
 delay(2);
 time2 = millis();
 Serial.print(time2 - time1);
 Serial.print(" parametro B INT = ");
 Serial.println(temperatura2 - 273);
 delay(2000);

}
