/* Engenharia de Telecomunicações 2019/2
 *  
 * Laboratório de Sistemas Embarcados - Sensor de Temperatura
 * Alunos:  Allex Magno Andrade
 *          Douglas Amorim dos Santos
 * 
 */


#define sensorPin 0  // Pino de entrada do sensor de temperatura
#define ledPin 13    // Pino que era ativar o led
float temp = 0;      // Valor que será lido do sensor
float Rntc = 0;      // Valor da resistencia calculada a partir do valor do sensor
float temperatura = 0;      // Valor da temperatura
unsigned long time1, time2; // Parâmetros para o calculo do tempo de execução da função

// Valores de calibração do sistema, utilizando a tabela de resistência
float A = 1.112272865*pow(10,-3);
float B = 2.375809102*pow(10,-4);
float C = 0.6852858650*pow(10,-7);



void setup() {
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);  // declarar o pino ledPin como saída
}

// Função que implementa o modelo de Steinhart-Hart para calcular o valor da temperatura
float tempSteinhartHart(float R){
  return  pow(A + B*log(R) + C*pow(log(R), 3),-1);
}

void loop(){
  
 temp = analogRead(sensorPin);          // ler o valor do sensor

 
 digitalWrite(ledPin, HIGH);            // Liga o Led
 time1 = micros();                      // Captura o tempo inicial
 Rntc = ((1023/temp) - 1)*10000;        // Calcula o valor da resistência
 temperatura = tempSteinhartHart(Rntc); // Obtenção da temperatura a partir do calculo de Steinhart-Hart
 time2 = micros();                      // Captura o tempo final
 digitalWrite(ledPin, LOW);             // Desliga o Led
 Serial.print(time2 - time1);           // Tempo de executção do cálculo em us
 Serial.print("us. Steinhart = ");
 Serial.print(temperatura-273);         // Temperatura obtida
 Serial.println("°C");
 delay(1000);
 
}
