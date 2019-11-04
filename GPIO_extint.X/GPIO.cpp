
#include <avr/io.h>
#include "GPIO.h"


GPIO::GPIO(uint8_t id, PortDirection_t dir)
{
	_bit = GPIO_PORT::id_to_bit[id];
	_port = GPIO_PORT::AllPorts[GPIO_PORT::id_to_port[id]];
	_port->dir(_bit, dir);
}

void gpio_handler(void){
        p4.toggle();
}
GPIO::GPIO(uint8_t id, PortDirection_t dir, uint8_i extint_id, uint8_t extint_cnf, CALLBACK_t pCallback){
    
    _bit = GPIO_PORT::id_to_bit[id];
	_port = GPIO_PORT::AllPorts[GPIO_PORT::id_to_port[id]];
	_port->dir(_bit, dir);
    
    _ext_int = EXT_INT(extint_id, extint_cnf, pCallback);
    _ext_int->enable();
    
}

//GPIO::~GPIO() {}

bool GPIO::get() {
    return _port->get(_bit);
}

void GPIO::set(bool val) {
    _port->set(_bit,val);
    
}

void GPIO::clear() {
    _port->clear(_bit);
}

void GPIO::toggle() {
    _port->toggle(_bit);
}