
#include <avr/io.h>
#include "GPIO.h"

gpio::gpio(uint8_t id, PortDirection_t dir):_bit(id){

    switch (_bit) {
        case 0:
        case 1:
            _ddr = &DDRE;
            _port = &PORTE;
            _pin = &PINE;
            break;
        case 2:
        case 3:
        case 5:{
            if (_bit == 5) {
                _bit -= 2;
            } 
            else {
                _bit += 2;
            }
            _ddr = &DDRE;
            _port = &PORTE;
            _pin = &PINE;
             break;
        }
        case 4:{
            _bit += 1;
            _ddr = &DDRG;
            _port = &PORTG;
            _pin = &PING;
            break;
        }
        case 6:
        case 7:
        case 8:
        case 9:{
            _bit -= 3;
            _ddr = &DDRH;
            _port = &PORTH;
            _pin = &PINH;
            break;
        }  
        case 10:
        case 11:
        case 12:
        case 13:{
            _bit -= 6;
            _ddr = &DDRB;
            _port = &PORTB;
            _pin = &PINB;
            break;
        }
    }
    if (dir) {
        *_ddr |= (1 << _bit);  //OUTPUT
    } 
    else {
        *_ddr &= ~(1 << _bit); //INPUT
    }
}


/*gpio::~gpio() {
}*/

bool gpio::get() {
    return *_pin & (1 << _bit);
}

void gpio::set(bool val) {
    if(val){
        *_port |= (1 << _bit);
    }
    else{
        *_port &= ~(1 << _bit);
    }

}

void gpio::clear() {
    this->set(0);
}

void gpio::toggle() {
    *_pin = (1 << _bit);
}