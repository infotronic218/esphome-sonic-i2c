import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import sensor
from esphome.const import (
 
    CONF_TIMEOUT,
    STATE_CLASS_MEASUREMENT,
    UNIT_METER,
    ICON_ARROW_EXPAND_VERTICAL,
)

CONF_SDA_PIN = "sda_pin"
CONF_SCL_PIN = "scl_pin"

CONF_PULSE_TIME = "pulse_time"

sonic_sensor_ns = cg.esphome_ns.namespace("sonic_i2c_sensor")
SonicI2C = sonic_sensor_ns.class_("SonicI2C",sensor.Sensor, cg.PollingComponent)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        SonicI2C,
        unit_of_measurement=UNIT_METER,
        icon=ICON_ARROW_EXPAND_VERTICAL,
        accuracy_decimals=2,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(
        {
            cv.Required(CONF_SDA_PIN): int,
            cv.Required(CONF_SCL_PIN): int,
            #cv.Optional(CONF_TIMEOUT, default="2m"): cv.distance,
            #cv.Optional(CONF_PULSE_TIME, default="10us"): cv.positive_time_period_microseconds,
        }
    )
    .extend(cv.polling_component_schema("60s"))
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)

    #trigger = await cg.gpio_pin_expression(config[CONF_sda_PIN])
    cg.add(var.set_sda_pin(config[CONF_SDA_PIN]))
    #echo = await cg.gpio_pin_expression(config[CONF_ECHO_PIN])
    cg.add(var.set_scl_pin(config[CONF_SCL_PIN]))

    #cg.add(var.set_timeout_us(config[CONF_TIMEOUT] / (0.000343 / 2)))
    #cg.add(var.set_pulse_time_us(config[CONF_PULSE_TIME]))

    

    