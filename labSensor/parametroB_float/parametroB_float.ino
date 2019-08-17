/* Engenharia de Telecomunicações 2019/2
 *  
 * Laboratório de Sistemas Embarcados - Sensor de Temperatura
 * Alunos:  Allex Magno Andrade
 *          Douglas Amorim dos Santos
 * 
 */


#define sensorPin 0   // Pino de entrada do sensor de temperatura
#define ledPin 13     // Pino que era ativar o led
float temp = 0;       // Valor que será lido do sensor
float Rntc = 0;       // Valor da resistencia calculada a partir do valor do sensor
float temperatura = 0;      // Valor da temperatura
unsigned long time1, time2; // Parâmetros para o calculo do tempo de execução da função

// Valores de B, utilizando a tabela de resistência
float B = 3950;
float R0 = 10000;


void setup() {
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);  // declarar o pino ledPin como saída
}

// Função que implementa o parâmetro B para calcular o valor da temperatura
float tempBparameter(float R){
  return 1/(1/298.15 + (1/B)*log(R/R0));
}

void loop(){
  
 temp = analogRead(sensorPin);          // ler o valor do sensor
 Rntc = ((1023/temp) - 1)*10000;         // Calcula o valor da resistência

 
 digitalWrite(ledPin, HIGH);            // Liga o Led
 time1 = micros();                      // Captura o tempo inicial
 temperatura = tempBparameter(Rntc); // Obtenção da temperatura a partir do calculo de Steinhart-Hart
 time2 = micros();                      // Captura o tempo final
 digitalWrite(ledPin, LOW);             // Desliga o Led
 Serial.print("Tempo: ");
 Serial.print(time2 - time1);           // Tempo de executção do cálculo em us
 Serial.print("us. Parametro B FLOAT = ");
 Serial.print(temperatura-273);       // Temperatura obtida
 Serial.println("°C");
 delay(1000);
 
}
