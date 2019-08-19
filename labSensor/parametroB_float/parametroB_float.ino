/* Engenharia de Telecomunicações 2019/2
 *  
 * Laboratório de Sistemas Embarcados - Sensor de Temperatura
 * Alunos:  Allex Magno Andrade
 *          Douglas Amorim dos Santos
 * 
 */


#define sensorPin 0   // Pino de entrada do sensor de temperatura
#define ledPin 13     // Pino que era ativar o led
#define R10K 10000.0
// Valores de B, utilizando a tabela de resistência
#define R0 10000.0
#define Beta 3950.0
#define T0 298.15
#define Vin_d 1023.0
#define Vout_d 753

float temp;       // Valor que será lido do sensor
float Rntc;       // Valor da resistencia calculada a partir do valor do sensor
float TK;      // Valor da temperatura
float TC;

unsigned long time1, time2; // Parâmetros para o calculo do tempo de execução da função




void setup() {
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);  // declarar o pino ledPin como saída
}

// Função que implementa o parâmetro B para calcular o valor da temperatura
float tempBparameter(float R){
  return 1/(1/298.15 + (1/Beta)*log(R/R0));
}


void loop(){

 temp = analogRead(sensorPin);          // ler o valor do sensor
 Rntc = ((Vin_d/temp) - 1)*R10K;         // Calcula o valor da resistência

 
 digitalWrite(ledPin, HIGH);            // Liga o Led
 time1 = micros();                      // Captura o tempo inicial
 TK = tempBparameter(Rntc);             // Obtenção da temperatura a partir do calculo do parâmetro B
 time2 = micros();                      // Captura o tempo final
 digitalWrite(ledPin, LOW);             // Desliga o Led
 TC = TK -273;
  Serial.print("Tempo: ");
 Serial.print(time2-time1);
 Serial.print("us. Parametro B FLOAT = ");
 Serial.print(TC);
 Serial.println("°C\n");
 delay(1000);
 
}
