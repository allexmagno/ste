#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "UART.h"
#include <avr/interrupt.h>



void SPI_Escravo_Inic( )
{
    DDRB = (1<<PB4);//ajusta o pino MISO como saída, demais pinos como entrada
    SPCR = (1<<SPE);//habilita SPI
}

char SPI_Escravo_Recebe( )
{
    while(!(SPSR & (1<<SPIF)));//espera a recepção estar completa
    return SPDR;
    //retorna o registrador de dados
}

UART uart(9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1);

int main() {
    sei();

    SPI_Escravo_Inic();
    while(true){
        uart.put(SPI_Escravo_Recebe());
    }
    return 0;
}

