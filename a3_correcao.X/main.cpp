/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on 25 de Setembro de 2019, 08:23
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "GPIO.h"
#include "UART.h"
#include "Timer.h"
 
GPIO sw54(54, GPIO::INPUT); 
GPIO_PORT::GPIO_Port *PK = GPIO_PORT::AllPorts[9];
UART uart(9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1);
Timer t = Timer(1000);
uint8_t pk_value = 0x01; 

const char msg[] = "O valor atual da porta PK e: ";

void timeout_handler(void){
	PK->toogle_byte();
}

void rotate_pk(void){
    PK->write_byte(pk_value);
    
    if(pk_value == 128){
        pk_value = 0x01;
    }else{
        pk_value <<= 1;
    }
}

void check_sw4(void){
    if(sw54.get()){
        uart.put('X');
    }

}

void check_sw4_msg(void){
    char s[4];
    
    if(sw54.get()){
        uart.puts(msg);
        //sprintf(s, "%d\n", pk_value);
        itoa(pk_value,s,10);
        s[3] = '\0';
        uart.puts(s);
        uart.put('\n');
    }

}


int main(){
 
    PK->dir_byte(GPIO::OUTPUT);
    PK->write_byte(pk_value);
   
	t.addTimeout(1000, &rotate_pk);
    t.addTimeout(200, &check_sw4_msg);
    sei();
	while(true){
		t.timeoutManager();
	}
 }