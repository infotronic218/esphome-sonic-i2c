#include"sonic_i2c.h"
#include<Wire.h>

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
  ESP_LOGI(TAG," SDA Pin: %d", this->sda_pin_);
  ESP_LOGI(TAG," SCL Pin: %d", this->scl_pin_);
  //ESP_LOGCONFIG(TAG, "  Timeout: %u µs", this->timeout_us_);
  LOG_UPDATE_INTERVAL(this);
}


void SonicI2C::setup(){
    // Init the sensor 
    ESP_LOGI(TAG, "Sonic Sensor Setup begin");
    this->sensor = new SONIC_I2C();
    this->sensor->begin(&Wire, 0x57, this->sda_pin_,this->scl_pin_);
    
}


void SonicI2C::update() {
   
    float result =  this->sensor->getDistance();
    if(result>=4500|| result<=20)
    {
            ESP_LOGI(TAG, "Incorrect Distance Reading");
         }else{
            ESP_LOGD(TAG, "'%s' - Got distance: %.2f m", this->name_.c_str(), result);
           
      }
    
    publish_state(result);
  
}
/*
void SonicI2C::loop(){
  long delay_ms = 2000 ;
  long last = 0 ;

   while(1){

      
      
       this->value = 
       if(millis()-last>delay_ms){
         if(this->value>=4500|| this->value<=20){
            ESP_LOGI(TAG, "Incorrect Distance Reading");
         }else{
            ESP_LOGI(TAG, "Distance value : %.2f", this->value);
         }
          
          last = millis();
       }
       
       
   }
}*/

}

}