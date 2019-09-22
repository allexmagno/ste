/* 
 * File:   gpio.cpp
 * Author: root
 * 
 * Created on 9 de Setembro de 2019, 07:39
 */

#include "gpio.h"
#include <avr/io.h>

GPIO::GPIO() {
}

GPIO::GPIO(uint8_t id, PortDirection_t dir):_id(id) {
    
    switch(id){
        case 0:  
        case 1:
            _bit = (1 << _id);
            if(dir)
                DDRE |= _bit;
            else
                DDRE &= ~_bit;
            break;
        
        case 2:        
        case 3:
            _bit = id + 2;
            if (dir)
                DDRE |= _bit;
            else
                DDRE &= ~_bit;
            break;
        case 4:
            
            _bit = (1 << (_id+1));
            if (dir)
                DDRG |= _bit;
            else
                DDRG &= ~_bit;
            break; 
        case 5:
            _bit = (1 << (_id-2));
            if (dir)
                DDRE |= _bit;
            else
                DDRE &= ~_bit;
            break;    
            
        case 6:        
        case 7:
        case 8:     
        case 9:
            _bit  = (1 << (_id-3));
            if (dir)
                DDRH |= (1 << PH6);
            else
                DDRH &= ~(1 << PH6);
            break;
            
        case 10:
        case 11: 
        case 12:
        case 13:
            _id = id -6;
            _bit = (1 << _id);
            if (dir)
                DDRB |= _bit;
            else
                DDRB &= ~_bit;
            break;
    }    
    
}

void GPIO::clear(){
    this->set(0);
}

bool GPIO::get(){
    	switch (_id) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 5:
		return (bool) PINE & (1 << _bit);

	case 4:
		return (bool) PING & (1 << _bit);

	case 6:
	case 7:
	case 8:
	case 9:
		return (bool) PINH & (1 << _bit);

	case 10:
	case 11:
	case 12:
	case 13:
		return (bool) PINB & (1 << _bit);
	}
    return false;
}

void GPIO::set(bool val){
    
    switch (_id){
        case 0:            
        case 1:
        case 2:        
        case 3:
        case 5:
            PORTE = val ? PORTE |= (1 << _bit) : PORTE &= ~(1 << _bit);
            break;
            
        case 4:
            PORTG = val ? PORTG |= (1 << _bit) : PORTG &= ~(1 << _bit);
            break; 
                    
        case 6:        
        case 7:
        case 8:     
        case 9:
            PORTH = val ? PORTH |= (1 << _bit) : PORTH &= ~(1 << _bit);
            break; 
            
        case 10:
        case 11: 
        case 12:
        case 13:
            PORTH = val ? PORTH |= (1 << _bit) : PORTH &= ~(1 << _bit);
            break; 
            
        default:
            break;
    }
}

void GPIO::toggle(){
    switch (_id) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 5:
		PINE = (1 << _bit);
		break;

	case 4:
		PING = (1 << _bit);
		break;

	case 6:
	case 7:
	case 8:
	case 9:
		PINH = (1 << _bit);
		break;

	case 10:
	case 11:
	case 12:
	case 13:
		PINB = (1 << _bit);
		break;

	}
    
}