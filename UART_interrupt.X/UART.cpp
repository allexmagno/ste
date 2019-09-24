/* 
 * File:   UART.cpp
 * Author: root
 * 
 * Created on 16 de Setembro de 2019, 08:11
 */

#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t UART::_tx_buffer = 0;
uint8_t UART::_rx_buffer = 0;
bool UART::has_data = false;

UART::UART() {
}

UART::UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb) {
    UBRR0 = F_CPU/16/baud-1;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C |= db | parity | sb;
}

/*UART::~UART() { 
    
}*/

void UART::put(uint8_t data){
    _tx_buffer = data;
    UCSR0B |= (1 << UDRIE0);
};

void UART::puts(const char * msg){
    for(int i = 0; msg[i] != 0; i++){
        put((uint8_t) msg[i]);
    }
    
};

uint8_t UART::get(){
    has_data = false;
    return _rx_buffer;
    //return UDR0;
};

bool UART::get_has_data(){
    return has_data;
    //return !(UCSR0A & (1 << RXC0));
};

void UART::rx_isr_handler(){
    _rx_buffer = UDR0;
    has_data = true;
    
};
void UART::tx_isr_handler(){
    UDR0 = _tx_buffer;
    UCSR0B &= ~(1 << UDRIE0);
};

ISR(USART0_RX_vect)
{
    UART::rx_isr_handler();
}

ISR(USART0_UDRE_vect)
{
    UART::tx_isr_handler();
}