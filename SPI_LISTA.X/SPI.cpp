#include "SPI.h"
#include <avr/io.h>
#include <avr/interrupt.h>

LISTA<GPIO> SPI::_slaves;
SPI::SPI() {
}

SPI::SPI(Mode_t md, ClockRate_t sck, DataMode_t dtm, DataOrder_t dto) {
    _msk = (sck % 4);
    if (sck > 4){
        SPSR |=  1;
    }
    
    if (md){
        SPCR |= (1 << MSTR);
        DDRB |= (1 << PB2) | (1 << PB1); // Configura MOSI e SCK
        
    }else{
        SPCR &= ~(1 << MSTR);
        DDRB = (1<<PB3);
    }
    SPCR |= _msk | (1 << SPE); // Habilita SPI mestre com clk de 16
}

void SPI::put(uint8_t data){
    SPDR = data; // Envia dado para o registrador
    while(!(SPSR & (1 << SPIF))); 
};

void SPI::puts(const char * msg){
    // Criar uma fila para tx_buffer
    for(int i = 0; msg[i] != 0; i++){
        put((uint8_t) msg[i]);
    }
};


uint8_t SPI::get(){
    return 0;
}


void SPI::set_slave(GPIO slave){
    _slaves.insere(slave);
}


