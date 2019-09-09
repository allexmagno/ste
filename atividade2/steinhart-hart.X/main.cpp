/* Engenharia de Telecomunicações 2019/2
 *  
 * Laboratório de Sistemas Embarcados - Sensor de Temperatura avr lib_c
 * Alunos:  Allex Magno Andrade
 *          Douglas Amorim dos Santos
 * 
 */

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD-1)
#define Vin_d 10230000
#define R10K 10000
#define Beta 39500000
#define Rinf 176


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// Configuração inicial
void setup(void){
    
   // Configuração para GPIO
    DDRB |= (1 << 7);
    DDRE &= ~(1 << 4);
}

// Configuração da Serial
void serial(unsigned int ubrr){
    UBRR0 = ubrr;
    /* Frame format: 8N1*/
    UCSR0C = (3 << UCSZ00); // Mesma configuração feita acima
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}
// Configuração do A/D
void adc_init(void){
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << ADLAR);
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADCSRA |= (1 << ADEN);
}

// Leitor da porta analogica
float analogRead(void){
   
   float valor;
   ADCSRA|=(1<<ADSC);
   while(ADCSRA & (1 << ADSC));
   
   valor = ADCL;
   valor = (ADCH << 8) + valor;
   return valor;
}

// RX serial
unsigned char rx(void){
    while( !(UCSR0A & (1 << RXC0)));
    return UDR0;   
}

// TX Serial
void tx(unsigned int data){
    while ( !(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

int main() {
    
    // Configurações iniciais
    setup();
    serial(MYUBRR);
    adc_init();    
    
    // Valor que será retonado após conversão serial em 16 bits
    unsigned int buffer;
    unsigned int LnR;
    unsigned long Rntc; // Valor da resistencia calculada a partir do valor do sensor
    unsigned int TK;
    int TC;    // Valor da temperatura
    
    char string[16];
    
    
    for(;;){
        PORTB |= (1 << 7); // Acende bit 7 da porta B [10000000]
        buffer = analogRead();
        Rntc = ((Vin_d/buffer) - 10000)*R10K;        // Calcula o valor da resistência
        LnR = log(Rntc/Rinf)*100;
        TK =  Beta/LnR;  
        TC = (TK-27315)/100;
        PORTB &= ~(1 << 7); // Apaga
        itoa(TC, string, 10);
        int len = strlen(string);
        for(int i = 0; i < len; i++){
            tx(string[i]);
        }
        tx('\n');
        _delay_ms(1000);
    }
    return 0;
}

