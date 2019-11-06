#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "SPI.h"
#include "UART.h"

UART uart(9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1);

GPIO slave0(22, GPIO::OUTPUT);	
GPIO slave1(53, GPIO::OUTPUT);	
    
//SPI spi(SPI::SLAVE, SPI::X_4, SPI::MODE_0, SPI::MSB, slaves);

int main(){
    slave0.set(1);
    slave1.set(1);
    GPIO slaves[] = {slave0, slave1};
    SPI spi(SPI::MASTER, SPI::X_4, SPI::MODE_0, SPI::MSB, slaves);
    sei();
    //char msg[] = (char) spi.get();    
    while(1){
        spi.select_slave(0);
        spi.put(1);
        if(spi.get_has_data()){
            uart.put(spi.get());
        }
        _delay_ms(1000);
        spi.select_slave(1);
        spi.put(2);
        if(spi.get_has_data()){
            uart.put(spi.get());
        }
        _delay_ms(1000);
      //  spi.puts(msg);
    }
}

/*
 
int main(){
    sei();
    SPI_SlaveInit(); 
	while(true){
        //uart.put('a');
        uart.put(SPI_SlaveReceive());        
	}
 }
*/