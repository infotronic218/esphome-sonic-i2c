#pragma once 

#include<esphome.h>
#include <Arduino.h>




namespace esphome {
    namespace rfid_rc522_i2c{
          public class RFID_RC522_I2C{
            private:

            public:
                void setup() override ;
                void dump_config() override;
                void update() override ;
                
         }
    }
}