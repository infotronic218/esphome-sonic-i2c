#include"sonic_i2c.h"
#include<Wire.h>
#include "pins_arduino.h"

namespace esphome{
static const char * TAG = "SONIC SENSOR" ;
//static SONIC_I2C sensor ;
namespace sonic_i2c_sensor{
 /*SonicI2C::SonicI2C(){
  // Init the sensor class 
  this->sensor = new SONIC_I2C();
}*/

void SonicI2C::dump_config() {
  LOG_SENSOR("", "Ultrasonic Sensor", this);
  //ESP_LOGI(TAG," SDA Pin: %d", this->sda_pin_);
  //ESP_LOGI(TAG," SCL Pin: %d", this->scl_pin_);
  //ESP_LOGCONFIG(TAG, "  Timeout: %u µs", this->timeout_us_);
  LOG_UPDATE_INTERVAL(this);
}


float SonicI2C::getDistance(){
    uint32_t data;
    uint8_t val = 0x01 ;
    this->write( &val, 1);
    //_wire->beginTransmission(_addr);  // Transfer data to 0x57. 将数据传输到0x57
    //_wire->write(0x01);
    //_wire->endTransmission();  // Stop data transmission with the Ultrasonic
                               // Unit. 停止与Ultrasonic Unit的数据传输
    delay(120);
    uint8_t data_buffer[]={0,0,0,0,0};
    
    this->read(data_buffer,3);
    //_wire->requestFrom(_addr,
    //                   (uint8_t)3);  // Request 3 bytes from Ultrasonic Unit.
                                     // 向Ultrasonic Unit请求3个字节。
    //data = _wire->read();
   // data <<= 8;
    //data |= _wire->read();
    //data <<= 8;
    //data |= _wire->read();
    data = data_buffer[0]<< 16 | data_buffer[1]<< 8 | data_buffer[2];
    float Distance = float(data) / 1000;
    if (Distance > 4500.00) {
        return 4500.00;
    } else {
        return Distance;
    }
  return  0 ;
}

void SonicI2C::setup(){
    // Init the sensor 
    ESP_LOGI(TAG, "Sonic Sensor Setup begin");
    //this->sensor = new SONIC_I2C();
    //this->sensor->begin(&Wire, 0x57, this->sda_pin_,this->scl_pin_);
    
}


void SonicI2C::update() {
   
    float result =  this->getDistance();
    if(result>=4500|| result<=20)
    {
            ESP_LOGI(TAG, "Incorrect Distance Reading");
         }else{
            ESP_LOGD(TAG, "'%s' - Got distance: %.2f m", this->name_.c_str(), result);
           
      }
    
    publish_state(result);
  
}

}

}