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

// Interrupções
#include <avr/interrupt.h>
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
    
    
   // Configuração para GPIO
    DDRB |= (1 << 7);
    DDRE &= ~(1 << 4);
    
    // Configuração do serial
    UBRR0 = ubrr;
    /* Frame format: 8N1*/
    //UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0C = (3 << UCSZ00); // Mesma configuração feita acima
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    
    // Configuração para conversor digital/Analogico
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN) & (7 << ADPS0);
    
    // Configuração de interrupções
    EICRB |= (3 << ISC40);
    EIMSK |= (1 << INT4);
    
    
    
}

// Configuração do A/D
void adc_init(void){
    
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN) | (7 << ADPS0);
    
}

// Piscar LED
void blink_led(){
    PORTB |= (1 << 7);
    //_delay_ms(1000);
    PORTB &= ~(1 << 7);
    //_delay_ms(1000);
}


// Leitor da portal analogica
unsigned int readAnalog(void){
    
   ADCSRA|=(1<<ADSC);

   while(ADCSRA & (1<<ADSC));
   
   return ADC;

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

// Lê valor do botão e envia P para a serial
void read_button(){
    if(PINE & (1 << 4));
        tx('P');
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
    // Configurações iniciais
    setup(MYUBRR);
    adc_init();
    sei();
    
    
    // Valor que será retonado após conversão serial em 16 bits
    unsigned int buffer;
    
    for(;;){
        blink_led();
//        buffer = rx();
        read_button();        
        //buffer = readAnalog();
        //tx(buffer);
    }
    return 0;
}

// Tx com interrupções
ISR(INT4_vect){
    tx('P');
}
