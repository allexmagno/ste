#include <avr/io.h>
#include <util/delay.h>
//#include "UART.h"
#include "FILA.h"
#include <stdint.h>

//UART uart(115200, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1);
 
int main(){
	uint8_t echo;
	//char msg[] = "Byte Received: ";
 
    FILA<uint8_t> Fila(8);
    Fila.enfileira(echo);
    echo = Fila.desenfileira();
	/*while(uart.get_has_data()){
		echo = uart.get();
		uart.puts(msg);
		uart.put(echo);
		uart.put('\n');
	}
 
    */
	return 1;
}