#include "SPI.h"
#include <avr/io.h>
#include <avr/interrupt.h>

SPI::SPI(Mode_t md, ClockRate_t sck, DataMode_t dtm, DataOrder_t dto, GPIO *slaves) {
    _msk = (sck % 4);
    
    if (md){
        if (sck > 4){
            SPCR = _msk;
            SPSR = 1;
        }else{
            SPCR = _msk;
        }
        SPCR |= (1 << MSTR);
        DDRB |= (1 << PB2) | (1 << PB1); // Configura MOSI e SCK
        
    }else{
        DDRB = (1<<PB3);
    }
    SPCR |= (1<<SPE);
    _slaves = slaves;
}

void SPI::put(uint8_t data, uint8_t index){
    _slaves[index].toggle();
    SPDR = data; // Envia dado para o registrador
    while(!(SPSR & (1 << SPIF))); 
    _slaves[index].toggle();
};

void SPI::puts(const char * msg, uint8_t index){
    // Criar uma fila para tx_buffer
    for(int i = 0; msg[i] != 0; i++){
        put((uint8_t) msg[i], index);
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
