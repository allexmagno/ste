#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include <avr/interrupt.h>
#include <util/delay.h>

UART uart(9600, UART::DATABITS_7, UART::ODD, UART::STOPBIT_1);
 
int main(){
    sei();
	uint8_t echo;
	char msg[] = "Byte Received: ";
 
	while(1){
		//echo = uart.get();
		uart.puts(msg);
		//uart.put(echo);
		//uart.put('\n');
        _delay_ms(1000);
	}
 
	return 1;
}