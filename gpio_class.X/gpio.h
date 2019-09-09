/* 
 * File:   gpio.h
 * Author: root
 *
 * Created on 9 de Setembro de 2019, 07:39
 */

#ifndef GPIO_H
#define	GPIO_H
#include <stdint.h>


class gpio {
public:
    
    enum PortDirection_t{
        INPUT = 0,
        OUTPUT = 1
    };
    gpio();
    gpio(uint8_t id, PortDirection_t dir);
    virtual ~gpio();
    
    bool get();
    void set(bool val = 1);
    void clear();
    void toggle();
private:
    uint8_t _id;
    uint8_t _bit;

};

#endif	/* GPIO_H */

