

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
int i = 0;

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

long int tempBparameterInt(int R){
  return 29815*B_1/(B_1*100 + 29815*log(R/R0));
}

void loop() {
 
 val = analogRead(potPin); // ler o valor do potenciômetro
 Rntc = ((1023/val) - 1)*10000;

 // Leitura utilizando o calculo de Steinhart-Hart
 digitalWrite(ledPin, HIGH);
 time1 = micros();
 temperatura = tempSteinhartHart(Rntc);
 time2 = micros();
 digitalWrite(ledPin, LOW);
 Serial.print("Tempo: ");
 Serial.print(time2 - time1);
 Serial.print("us. Steinhart = ");
 Serial.print(temperatura-273);
 Serial.println("°C\n");
 delay(1000);

// Leitura utilizando o calculo com o parâmetro B float
 digitalWrite(ledPin, HIGH);
 time1 = micros();
 temperatura1 = tempBparameter(Rntc);
 time2 = micros();
 digitalWrite(ledPin, LOW);
 Serial.print("Tempo: ");
 Serial.print(time2-time1);
 Serial.print("us. Parametro B FLOAT = ");
 Serial.print(temperatura1-273);
 Serial.println("°C\n");


 // Leitura utilizando o calculo com o parâmetro B INT
 digitalWrite(ledPin, HIGH);
 time1 = micros();
 temperatura2 = tempBparameterInt(Rntc);
 time2 = micros();
 digitalWrite(ledPin, LOW);
 Serial.print("Tempo: ");
 Serial.print(time2 - time1);
 Serial.print("us. Parametro B INT = ");
 Serial.print(temperatura2 - 273);
 Serial.println("°C\n");
 delay(2000);

}
