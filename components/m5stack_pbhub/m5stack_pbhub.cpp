#include "m5stack_pbhub.h"
#include "esphome/core/log.h"

namespace esphome {
namespace m5stack_pbhub {

static const char *const TAG = "m5stack_pbhub";

void M5StackPBHUBComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up M5Stack PBHUB...");

  this->portHub = new PortHub(/*this->address_, &Wire*/);
  if (!this->read_gpio_()) {
    ESP_LOGE(TAG, "PBHUB not available under 0x%02X", this->address_);
    this->mark_failed();
    return;
  }

  this->write_gpio_();
  this->read_gpio_();
}
void M5StackPBHUBComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "PBHUB:");
  //LOG_I2C_DEVICE(this)
  
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with PBHUB failed!");
  }
}
bool M5StackPBHUBComponent::digital_read(uint8_t pin) {
  this->read_gpio_();
  return this->input_mask_ & (1 << pin);
}
void M5StackPBHUBComponent::digital_write(uint8_t pin, bool value) {
  if (value) {
    this->output_mask_ |= (1 << pin);
  } else {
    this->output_mask_ &= ~(1 << pin);
  }

  this->write_gpio_();
}
void M5StackPBHUBComponent::pin_mode(uint8_t pin, gpio::Flags flags) {
  if (flags == gpio::FLAG_INPUT) {
    // Clear mode mask bit
    this->mode_mask_ &= ~(1 << pin);
    // Write GPIO to enable input mode
    this->write_gpio_();
  } else if (flags == gpio::FLAG_OUTPUT) {
    // Set mode mask bit
    this->mode_mask_ |= 1 << pin;
  }
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
