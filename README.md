# esphome Component implementation
Custom components implementation for esphome 
# Implemented components
* [SONIC I2C] Ultra sonic sensor over the I2C interface

* [MFRC522 RFID I2C] Ultra sonic sensor over the I2C interface

* [MLX90614 ] Infrared Temperature sensor from Adafruit implementation

# Components Usage 

Refer to the  [test_update.yaml](test_update.yaml) as configuration examples for the implemented compoments. 

* Loading dependencies  and components loading
``` yaml
esphome:
  name: esp32_test

  libraries:
    - Wire
    - SPI
    - adafruit/Adafruit BusIO @ 1.9.6
    #- "Adafruit MLX90614 Library"

  
external_components:
    - source:
        type: local
        path: components 

      components: [sonic_i2c, mfrc522_i2c, mlx90614]
```

* Sonic I2C sensor Configuration

``` yaml
sonic_i2c: 
   i2c_id: bus_i2c
   address: 0x57
   name: Distance Sensor
   unit_of_measurement: mm
   update_interval: 5s
```

* RFID SENSOR with binary sensor

``` yaml
mfrc522_i2c:
  i2c_id: bus_i2c
  address: 0x28 # I2C adress 
  on_tag:
    then:
      - homeassistant.tag_scanned: !lambda 'return x;'
# Link the RFID reader to binary sensor
binary_sensor:
  - platform: rc522
    uid: 74-10-37-94 # Change this to match the TAG ID 
    name: "RC522 RFID Tag"
```

*  MLX90614 Configuration

``` yaml
mlx90614:
  ambient_temperature: # Ambient temperature
    name: "Ambient temperature"
    unit_of_measurement: °C
    accuracy_decimals: 1
  object_temperature: # Object temperature
    name: "Object temperature"
    unit_of_measurement: °C
    accuracy_decimals: 1

```
