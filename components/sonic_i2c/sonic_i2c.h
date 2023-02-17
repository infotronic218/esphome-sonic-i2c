#pragma once 

#include<esphome.h>
#include<Arduino.h>
#include "Unit_Sonic.h"
#include "esphome/core/gpio.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome{
namespace sonic_i2c_sensor{
 

class SonicI2C: public i2c::I2CDevice, public sensor::Sensor, public PollingComponent {
    private:
    //uint8_t sda_pin_;
    //uint8_t scl_pin_;;
    //SONIC_I2C *sensor ;
    public:
    
     //void set_sda_pin(uint8_t sda_pin) { sda_pin_ = sda_pin; }
     //void set_scl_pin(uint8_t scl_pin) { scl_pin_ = scl_pin; }
     void setup() override ;
     void dump_config() override;
     void update() override ;
     float getDistance();

};

}

}