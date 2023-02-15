#pragma once 

#include<esphome.h>
#include<Arduino.h>
#include "Unit_Sonic.h"


namespace esphome{
namespace sonic_i2c_sensor{
 

class SonicI2C: public Component {
    private:
    SONIC_I2C *sensor ;
    float value ;
    public:
    SonicI2C();
    void setup() override ;
    void loop() override ;

};

}

}