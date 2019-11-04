#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "SPI.h"

void SPI_Master_setup(void){
    DDRB |= (1 << PB2) | (1 << PB1); // Configura MOSI e SCK
    SPCR |= (1 << MSTR) | (1 << SPE) | (1 << SPR0); // Habilita SPI mestre com clk de 16
    
}
void SPI_Master_tx(char data){
    SPDR = data; // Envia dado para o registrador
    while(!(SPSR & (1 << SPIF))); // Espera a transmissao (quando SPIF for 1)
}

void SPI_SlaveInit(void)
{
    /* Set MISO output, all others input */
    DDRB = (1<<PB3);
    /* Enable SPI */
    SPCR = (1<<SPE);
}

char SPI_SlaveReceive(void)
{
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF)))
    ;
    /* Return Data Register */
    return SPDR;
}
SPI spi(SPI::MASTER, SPI::X_4, SPI::MODE_0, SPI::MSB);
GPIO slave0(0, GPIO::OUTPUT);	
int main(){
    char msg[] = "spi msg";
    spi.set_slave(slave0);
    
    while(1){
        spi.puts(msg);
    }
}
/* 
int main(){
    sei();
    SPI_SlaveInit(); 
	while(true){
        uart.put('a');
        uart.put(SPI_SlaveReceive());        
	}
 }*/