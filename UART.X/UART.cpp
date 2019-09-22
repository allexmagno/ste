/* 
 * File:   UART.cpp
 * Author: root
 * 
 * Created on 16 de Setembro de 2019, 08:11
 */

#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>

FILA<uint8_t> UART::_tx_buffer(10);
FILA<uint8_t> UART::_rx_buffer(10);
bool UART::has_data = false;

UART::UART() {
}

UART::UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb) {
    UBRR0 = F_CPU/16/baud-1;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= db | parity | sb;
}

/*UART::~UART() { 
    
}*/

void UART::put(uint8_t data){
    // UDRIE0 verifica se o buffer está livre
    //_tx_buffer = data;
    _tx_buffer.enfileira(data)
    UCSR0B |= (1 << UDRIE0);
    //while ( !(UCSR0A & (1 << UDRE0)));
    //UDR0 = data;
    // UDRIE0 = true
};

void UART::puts(const char * msg){
    // Criar uma fila para tx_buffer
    while ( !(UCSR0A & (1 << UDRE0)));
    for(int i = 0; msg[i] != 0; i++){
        put((uint8_t) msg[i]);
    }
};

FILA<uint8_t> UART::get(){
    has_data = false;
    return _rx_buffer;
    //return UDR0;
};

bool UART::get_has_data(){
    return has_data;
    //return !(UCSR0A & (1 << RXC0));
};

void UART::rx_isr_handler(){
    //_rx_buffer = UDR0;
    _rx_buffer.enfileira(UDR0);
    has_data = true;
    
};
void UART::tx_isr_handler(){
    if (!_tx_buffer.vazia()){
        UDR0 = _tx_buffer.desenfileira();
    
        // Antes verificar se a fila ta vazia
        //UDRIE0 = false;
        UCSR0A &= ~(1 << UDRIE0);
    }
};

ISR(USART0_RX_vect)
{
    UART::rx_isr_handler();
}
