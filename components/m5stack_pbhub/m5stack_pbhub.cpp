#include "m5stack_pbhub.h"
#include "esphome/core/log.h"


static const uint8_t HUB_ADDR[6] = {HUB1_ADDR, HUB2_ADDR, HUB3_ADDR,
                       HUB4_ADDR, HUB5_ADDR, HUB6_ADDR};
namespace esphome {
namespace m5stack_pbhub {

static const char *const TAG = "m5stack_pbhub";

void M5StackPBHUBComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up M5Stack PBHUB...");
  ESP_LOGCONFIG(TAG, "I2C Address : %x ",this->address_);
  ESP_LOGCONFIG(TAG, "SDA : %d ; SCL :  %d ", this->sda_ , this->scl_);
  Wire.begin(this->sda_ , this->scl_) ;
  //this->scan_devices(&Wire);
  this->portHub = new PortHub(this->address_, &Wire);
  /*
  if (!this->read_gpio_()) {
    ESP_LOGE(TAG, "PBHUB not available under 0x%02X", this->address_);
    this->mark_failed();
    return;
  }*/
}
void M5StackPBHUBComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "PBHUB:");
  //LOG_I2C_DEVICE(this)
  
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with PBHUB failed!");
  }
}
bool M5StackPBHUBComponent::digital_read(uint8_t pin) {
  if (pin==0){
    return portHub->hub_d_read_value_B(HUB_ADDR[pin]);
  }else if(pin==1){
   return  portHub->hub_d_read_value_A(HUB_ADDR[pin]);
  }
  uint8_t pin2 = pin /10 ;
  if(pin%2==0){
   return  portHub->hub_d_read_value_B(HUB_ADDR[pin2]);
  }
  return portHub->hub_d_read_value_A(HUB_ADDR[pin2]);
  
}
void M5StackPBHUBComponent::digital_write(uint8_t pin, bool value) {
  uint8_t val = value?0xFF: 0 ;
  if (pin==0){
    portHub->hub_d_wire_value_B(HUB_ADDR[pin],val);
  }else if(pin==1){
   portHub->hub_d_wire_value_A(HUB_ADDR[pin],val);
  }
  uint8_t pin2 = pin /10 ;
  if(pin%2==0){
   portHub->hub_d_wire_value_B(HUB_ADDR[pin],val);
  }
  portHub->hub_d_wire_value_A(HUB_ADDR[pin],val);
}
void M5StackPBHUBComponent::pin_mode(uint8_t pin, gpio::Flags flags) {
  /*if (flags == gpio::FLAG_INPUT) {
    // Clear mode mask bit
    this->mode_mask_ &= ~(1 << pin);
    // Write GPIO to enable input mode
    this->write_gpio_();
  } else if (flags == gpio::FLAG_OUTPUT) {
    // Set mode mask bit
    this->mode_mask_ |= 1 << pin;
  }*/
}
bool M5StackPBHUBComponent::read_gpio_() {
  /*
  if (this->is_failed())
    return false;
  bool success;
  uint8_t data[2];
  if (false) {
    success = this->read_bytes_raw(data, 2);
    this->input_mask_ = (uint16_t(data[1]) << 8) | (uint16_t(data[0]) << 0);
  } else {
    success = this->read_bytes_raw(data, 1);
    this->input_mask_ = data[0];
  }

  if (!success) {
    this->status_set_warning();
    return false;
  }
  this->status_clear_warning();*/
  return true;
}
bool M5StackPBHUBComponent::write_gpio_() {/*
  if (this->is_failed())
    return false;

  uint16_t value = 0;
  // Pins in OUTPUT mode and where pin is HIGH.
  value |= this->mode_mask_ & this->output_mask_;
  // Pins in INPUT mode must also be set here
  value |= ~this->mode_mask_;

  uint8_t data[2];
  data[0] = value;
  data[1] = value >> 8;
  if (this->write(data, 1) != i2c::ERROR_OK) {
    this->status_set_warning();
    return false;
  }

  this->status_clear_warning();*/
  return true;
}
void M5StackPBHUBComponent::scan_devices(TwoWire *wire_ ){
  uint8_t error, address;
  int nDevices;

  ESP_LOGCONFIG(TAG,"Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    wire_->beginTransmission(address);
    error = wire_->endTransmission();

    if (error == 0)
    {
      ESP_LOGCONFIG(TAG,"I2C device found at address : %x", address);
      nDevices++;
    }
    else if (error==4) 
    {
     ESP_LOGCONFIG(TAG,"Unknown error at address : %x", address);
    }    
  }
  if (nDevices == 0)
   ESP_LOGCONFIG(TAG,"No I2C devices found");
  else
    ESP_LOGCONFIG(TAG, "done Searching \n");
}

float M5StackPBHUBComponent::get_setup_priority() const { return setup_priority::IO; }

void PBHUBGPIOPin::setup() { pin_mode(flags_); }
void PBHUBGPIOPin::pin_mode(gpio::Flags flags) { this->parent_->pin_mode(this->pin_, flags); }
bool PBHUBGPIOPin::digital_read() { return this->parent_->digital_read(this->pin_) != this->inverted_; }
void PBHUBGPIOPin::digital_write(bool value) { this->parent_->digital_write(this->pin_, value != this->inverted_); }
std::string PBHUBGPIOPin::dump_summary() const {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%u via M5Stack PBHUB", pin_);
  return buffer;
}

}  // namespace m5stack_pbhub
}  // namespace esphome
