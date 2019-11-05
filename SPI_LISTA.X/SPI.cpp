#include "SPI.h"
#include <avr/io.h>
#include <avr/interrupt.h>

SPI::SPI(Mode_t md, ClockRate_t sck, DataMode_t dtm, DataOrder_t dto, GPIO slaves[]) {
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
    
    _slaves = slaves;
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
    //  Wait for reception complete
    while(!(SPSR & (1<<SPIF)));
    // Return Data Register 
    return SPDR;
}


GPIO SPI::select_slave(uint8_t index){
    return _slaves[index];
}
