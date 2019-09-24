#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include "FILA.h"
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include <avr/interrupt.h>
#include <util/delay.h>

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