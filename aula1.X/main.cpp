/* 
 * File:   main.cpp
 * Author: aluno
 *
 * Created on 21 de Agosto de 2019, 08:31
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
/*
 * 
 */
int main() {

    DDRB = 0xFF;
    
    for(;;){
        PORTB = 0x00;
        _delay_ms(1000);
        PORTB = 0xFF;
        _delay_ms(1000);
    }
    return 0;
}

