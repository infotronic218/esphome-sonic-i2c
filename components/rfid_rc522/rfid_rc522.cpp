#include"rfid_rc522.h"

namespace esphome {
    static const char *TAG = "RFID_RC522_I2C";
    namespace rfid_rc522_i2c{
          public class RFID_RC522_I2C{

            void RFID_RC522_I2C::setup(){
                 ESP_LOGI(TAG, "RFID RC522 I2C Setup begin");
            }

            void RFID_RC522_I2C:: dump_config(){
                LOG_SENSOR("", "RFID RC522 Sensor", this);
                LOG_UPDATE_INTERVAL(this);
            }

            void RFID_RC522_I2C::update(){

            }

            

         }
    }
}