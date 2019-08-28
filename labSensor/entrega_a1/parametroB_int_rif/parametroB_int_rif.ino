/* Engenharia de Telecomunicações 2019/2
 *  
 * Laboratório de Sistemas Embarcados - Sensor de Temperatura
 * Alunos:  Allex Magno Andrade
 *          Douglas Amorim dos Santos
 * 
 */


#define sensorPin 0   // Pino de entrada do sensor de temperatura
#define ledPin 13     // Pino que era ativar o led
#define Vin_d 10230000
#define R10K 10000
// Valores de B, utilizando a tabela de resistência *10^4
#define Beta 39500000
// Rinf = 10000*e^(-3950/298.15);
#define Rinf 176

unsigned int temp;           // Valor que será lido do sensor
unsigned int LnR;
unsigned long Rntc; // Valor da resistencia calculada a partir do valor do sensor
unsigned int TK;    // Valor da temperatura
byte TC;

unsigned long time1, time2; // Parâmetros para o calculo do tempo de execução da função

void setup() {
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);  // declarar o pino ledPin como saída

}
void loop(){

 temp = analogRead(sensorPin);              // ler o valor do sensor
 //Rntc = ((Vin_d/Vout_d) - 10000)*R10K;    // Calcula o valor da resistência
 
 digitalWrite(ledPin, HIGH);   
 //time1 = micros();
 Rntc = ((Vin_d/temp) - 10000)*R10K;        // Calcula o valor da resistência
 LnR = log(Rntc/Rinf)*100;
 TK =  Beta/LnR;                            // Captura o tempo inicial
 //time2 = micros();                          // Captura o tempo final
 digitalWrite(ledPin, LOW);                 // Desliga o Led
 Serial.print("Tempo: ");
 Serial.print(time2 - time1); 
 TC = (TK-27315)/100;
 Serial.print("us. Parametro B INT Rif= ");
 Serial.print(TC);                          // Temperatura obtida
 Serial.println("°C");
 delay(1000);
 
}
