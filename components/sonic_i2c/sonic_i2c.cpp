#include"sonic_i2c.h"


namespace esphome{
static const char * TAG = "SONIC SENSOR" ;
//static SONIC_I2C sensor ;
namespace sonic_i2c_sensor{
 SonicI2C::SonicI2C(){
  // Init the sensor class 
  this->sensor = new SONIC_I2C();
}



void SonicI2C::setup(){
    // Init the sensor 
    ESP_LOGI(TAG, "Sonic Sensor Setup begin");
    this->sensor->begin();
    
}


void SonicI2C::loop(){
  long delay_ms = 2000 ;
  long last = 0 ;

   while(1){

      
      
       this->value = this->sensor->getDistance();
       if(millis()-last>delay_ms){
         if(this->value>=4500|| this->value<=20){
            ESP_LOGI(TAG, "Incorrect Distance Reading");
         }else{
            ESP_LOGI(TAG, "Distance value : %.2f", this->value);
         }
          
          last = millis();
       }
       
       
   }
}

}

}