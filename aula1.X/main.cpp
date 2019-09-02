/* 
 * File:   main.cpp
 * Author: aluno
 *
 * Created on 21 de Agosto de 2019, 08:31
 */

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD-1)

#include <avr/io.h>
#include <util/delay.h>
/*
 * 
 */
/* Configurando serial 8N1 */
// uint_16 (8)
void setup(unsigned int ubrr){
 
    /* Exemplo para capturar palavras maiores de 8 bits
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) ubrr;
    */
    UBRR0 = ubrr;
    /* Frame format: 8N1*/
    //UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0C = (3 << UCSZ00); // Mesma configuração feita acima
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN) & (7 << ADPS0);
}

void adc_init(void){

    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN) & (7 << ADPS0);
}
unsigned int readAnalog(void){
    
   ADCSRA|=(1<<ADSC);

   while((ADCSRA & (1<<ADSC)));
   
   return ADC;

}



unsigned char rx(void){

    while( !(UCSR0A & (1 << RXC0)));
    return UDR0;
    
}

void tx(unsigned int data){
    
    while ( !(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

int main() {
/*
    // Configurando a porta B. Bit 7 para entrada e bit 6 para saída
    // Delocar o valor 7 posições: 1 << 7
    // Operação com bits em c/c++: and (&) or (|)
    // not ~
    DDRB |= (1 << 7);
    DDRB &= ~(1 << 6);
    //DDRF = 0x00;
    
    // PINB é usado quando é para leitura
    for(;;){
        // Comparando o pino 6 da porta B
        if (PINB & (1 << 6)){
            PORTB |= (1 << 7); // Acende bit 7 da porta B [10000000]
        }else{
            PORTB &= ~(1 << 7); // Apaga
        }
    }
    
    // configuração 8N1
    // UCSR0C = 000001100;
    
    */
    setup(MYUBRR);
    adc_init();
    unsigned int buffer;
    
    
    for(;;){
        //buffer = rx();
        buffer = readAnalog();
        tx(buffer);
    }
    return 0;
}

