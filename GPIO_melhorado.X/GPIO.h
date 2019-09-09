/* 
 * File:   GPIO.h
 * Author: root
 *
 * Created on 9 de Setembro de 2019, 09:10
 */

#ifndef GPIO_H
#define	GPIO_H

#include <stdint.h>

class GPIO {
public:
    
    enum PortDirection_t{
        INPUT = 0,
        OUTPUT = 1
    };
    GPIO();
    GPIO(uint8_t id, PortDirection_t dir);
    virtual ~GPIO();
    
    bool get();
    void set(bool val = 1);
    void clear();
    void toggle();
private:
    volatile uint8_t * _pin;
    volatile uint8_t * _ddr;
    volatile uint8_t * _port;
    
    uint8_t _bit;

};

#endif	/* GPIO_H */

