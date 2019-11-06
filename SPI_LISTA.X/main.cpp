#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "SPI.h"
#include "UART.h"
/*
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
    // Set MISO output, all others input
    DDRB = (1<<PB3);
    // Enable SPI
    SPCR = (1<<SPE);
}

char SPI_SlaveReceive(void)
{
    //  Wait for reception complete
    while(!(SPSR & (1<<SPIF)));
    // Return Data Register 
    return SPDR;
}

UART uart(9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1);

GPIO slave0(0, GPIO::OUTPUT);	
int main(){
    GPIO slaves[] = {slave0};
    //slaves[0] = slave0;
    
    SPI spi(SPI::SLAVE, SPI::X_4, SPI::MODE_0, SPI::MSB, slaves);
    //char msg[] = (char) spi.get();    
    while(1){
       uart.put('a');
      //  spi.puts(msg);
    }
}
 */

UART uart(9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1);
 
int main(){
    sei();
	//uint8_t echo;
	char msg[] = "Byte Received: ";
 
    //FILA<uint8_t> Fila(8);
    //Fila.enfileira(echo);
    //echo = Fila.desenfileira();
	while(1){
		//echo = uart.get();
		uart.puts(msg);
		//uart.put(echo);
		//uart.put('\n');
        _delay_ms(1000);
	}
	return 1;
}
/* 
int main(){
    sei();
    SPI_SlaveInit(); 
	while(true){
        uart.put('a');
        uart.put(SPI_SlaveReceive());        
	}
 }
 
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
    // Set MISO output, all others input
    DDRB = (1<<PB3);
    // Enable SPI
    SPCR = (1<<SPE);
}

char SPI_SlaveReceive(void)
{
    //  Wait for reception complete
    while(!(SPSR & (1<<SPIF)));
    // Return Data Register 
    return SPDR;
}
 */
