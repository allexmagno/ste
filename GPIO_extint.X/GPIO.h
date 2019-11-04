

#ifndef GPIO_H
#define	GPIO_H

#include "GPIO_Port.h"
#include "GPIO.h"
#include "extint.h"

class GPIO {
public:
    enum PortDirection_t {
        INPUT = 0,
        OUTPUT = 1
    };
    
    GPIO(uint8_t id, PortDirection_t dir);
    GPIO(uint8_t id, PortDirection_t dir, uint8_i extint_id, uint8_t extint_cnf, CALLBACK_t pCallback);
    //~GPIO();

    bool get();
    void set(bool val = 1);
    void clear();
    void toggle();

private:
    GPIO_PORT::GPIO_Port * _port; 
    EXT_INT::ExtInt * _ext_int;
    uint8_t _bit;
};



#endif	/* GPIO_H */