/* 
 * File:   GPIO.cpp
 * Author: root
 * 
 * Created on 9 de Setembro de 2019, 09:10
 */

#include "GPIO.h"
#include <avr/io.h>
GPIO::GPIO() {
}

GPIO::GPIO(uint8_t id, PortDirection_t dir):_bit(id) {
    
    switch(_bit){
        case 0:
        case 1:
            _ddr->DDRE;
            
    
    
    
    
    }
    
}

GPIO::~GPIO() {
}

bool GPIO::get(){}

void GPIO::set(bool vaal){}

void GPIO::toggle(){}

void GPIO::clear(){}

