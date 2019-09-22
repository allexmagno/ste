#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"


//LEDS PLACA (acende com '0')
gpio led0(0, gpio::OUTPUT);		//PE0
gpio led1(1, gpio::OUTPUT);		//PE1
 
//LEDS PLACA (acende com '1')
gpio led13(13, gpio::OUTPUT);	//PB7m
 
//Adicionar LED
gpio led4(4, gpio::OUTPUT);		//PG5
gpio led6(6, gpio::OUTPUT);		//PH0
 
int main(void){
 
	UCSR0B = 0;
 
	led0.set(1);
	led1.set(1);
	led6.clear();
	led4.clear();
	led13.clear();
	_delay_ms(1000);
	led0.clear();
	led1.clear();
	led6.set(1);
	led4.set(1);
	led13.set(1);
	_delay_ms(1000);
 
	while (1){
		led0.toggle();
		led1.toggle();
		led6.toggle();
		led4.toggle();
		led13.toggle();
		_delay_ms(1000);
	}
}