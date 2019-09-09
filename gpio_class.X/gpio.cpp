/* 
 * File:   gpio.cpp
 * Author: root
 * 
 * Created on 9 de Setembro de 2019, 07:39
 */

#include "gpio.h"
#include <avr/io.h>

gpio::gpio() {
}

gpio::gpio(uint8_t id, PortDirection_t dir) {
    
    switch(id){
        case 0:
            _id = id;
            _bit = PE0;
            if(dir)
                DDRE |= (1 << PE0);
            else
                DDRE &= ~(1 << PE0);
            break;
            
        case 1:
            _id = id;
            _bit = (1 << _id);
            if(dir)
                DDRE |= _bit;
            else
                DDRE &= ~_bit;
            break;
        
        case 2:
            _id = id;
            _bit = PE4;
            if (dir == OUTPUT)
                DDRE |= (1 << PE4);
            else
                DDRE &= ~(1 << PE4);
            break;
        
        case 3:
            _id = id;
            if (dir == OUTPUT)
                DDRE |= (1 << PE5);
            else
                DDRE &= ~(1 << PE5);
            break;
            
        case 4:
            _id = id;
            if (dir == OUTPUT)
                DDRG |= (1 << PG5);
            else
                DDRG &= (1 << PG5);
            break;
                        
        case 5:
            _id = id;
            if (dir == OUTPUT)
                DDRE |= (1 << PE3);
            else
                DDRE &= ~(1 << PE3);
            break;    
            
        case 6:
            _id = id;
            if (dir == OUTPUT)
                DDRH |= (1 << PH3);
            else
                DDRH &= ~(1 << PH3);
            break;    
        
        case 7:
            _id = id;
            if (dir == OUTPUT)
                DDRH |= (1 << PH4);
            else
                DDRH &= ~(1 << PH4);
            break;
            
        case 8:
            _id = id;
            if (dir == OUTPUT)
                DDRH |= (1 << PH5);
            else
                DDRH &= ~(1 << PH5);
            break;   
            
        case 9:
            _id = id;
            if (dir == OUTPUT)
                DDRH |= (1 << PH6);
            else
                DDRH &= ~(1 << PH6);
            break;
            
        case 10:
            _id = id;
            if (dir == OUTPUT)
                DDRB |= (1 << PB4);
            else
                DDRB &= ~(1 << PB4);
            break;
            
        case 11:
            _id = id;
            if (dir == OUTPUT)
                DDRB |= (1 << PB5);
            else
                DDRB &= ~(1 << PB5);
            break;
            
        case 12:
            _id = id;
            if(dir == OUTPUT)
                DDRB |= (1 << PB6);
            else
                DDRB &= ~(1 << PB6);
            break;
            
        case 13:
            _id = id;
            if (dir == OUTPUT)
                DDRB |= (1 << PB7);
            else
                DDRB &= ~(1 << PB7);
            break;
            
        default:
            break;
    }    
    
}

gpio::~gpio() {
}

void gpio::clear(){}

bool gpio::get(){
    return true;
}

void gpio::set(bool val){
    
}

void gpio::toggle(){
    
}

