import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import  uart
from esphome.const import CONF_DATA, CONF_SEND_EVERY
from esphome.const import CONF_ID
from esphome.core import CORE, coroutine_with_priority

sonic_sensor_ns = cg.esphome_ns.namespace("sonic_i2c_sensor")
SonicI2C = sonic_sensor_ns.class_("SonicI2C", cg.Component)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(SonicI2C),
        }
    )
    .extend(cv.COMPONENT_SCHEMA),
    cv.only_with_arduino,
    cv.only_on(["esp32", "esp8266"]),
)

@coroutine_with_priority(40.0)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    

    