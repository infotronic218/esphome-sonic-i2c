import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import i2c
from esphome.const import (
    CONF_ID,
    CONF_INPUT,
    CONF_NUMBER,
    CONF_MODE,
    CONF_INVERTED,
    CONF_OUTPUT,
)

DEPENDENCIES = ["i2c"]
MULTI_CONF = True
CONF_SDA_PIN = "sda"
CONF_SCL_PIN = "scl"
CONF_ADDRESS = "address"

mstack_pbhub_ns = cg.esphome_ns.namespace("m5stack_pbhub")

M5StackPBHUBComponent = mstack_pbhub_ns.class_("M5StackPBHUBComponent", cg.Component)
PBHUBGPIOPin = mstack_pbhub_ns.class_("PBHUBGPIOPin", cg.GPIOPin)

CONF_M5StackPBHUB = "m5stack_pbhub"
CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.Required(CONF_ID): cv.declare_id(M5StackPBHUBComponent),
            cv.Required(CONF_SDA_PIN): int,
            cv.Required(CONF_SCL_PIN): int,
            cv.Required(CONF_ADDRESS): int,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    #.extend(i2c.i2c_device_schema(0x21))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    #await i2c.register_i2c_device(var, config)
    cg.add(var.set_sda_pin(config[CONF_SDA_PIN]))
    cg.add(var.set_scl_pin(config[CONF_SCL_PIN]))
    cg.add(var.set_address(config[CONF_ADDRESS]))
    


def validate_mode(value):
    if not (value[CONF_INPUT] or value[CONF_OUTPUT]):
        raise cv.Invalid("Mode must be either input or output")
    if value[CONF_INPUT] and value[CONF_OUTPUT]:
        raise cv.Invalid("Mode must be either input or output")
    return value


M5StackPBHUB_PIN_SCHEMA = cv.All(
    {
        cv.GenerateID(): cv.declare_id(PBHUBGPIOPin),
        cv.Required(CONF_M5StackPBHUB): cv.use_id(M5StackPBHUBComponent),
        cv.Required(CONF_NUMBER): cv.int_range(min=0, max=17),
        cv.Optional(CONF_MODE, default={}): cv.All(
            {
                cv.Optional(CONF_INPUT, default=False): cv.boolean,
                cv.Optional(CONF_OUTPUT, default=False): cv.boolean,
            },
            validate_mode,
        ),
        cv.Optional(CONF_INVERTED, default=False): cv.boolean,
    }
)


@pins.PIN_SCHEMA_REGISTRY.register("m5stack_pbhub", M5StackPBHUB_PIN_SCHEMA)
async def m5stack_pbhub_pin_to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    parent = await cg.get_variable(config[CONF_M5StackPBHUB])

    cg.add(var.set_parent(parent))

    num = config[CONF_NUMBER]
    cg.add(var.set_pin(num))
    cg.add(var.set_inverted(config[CONF_INVERTED]))
    cg.add(var.set_flags(pins.gpio_flags_expr(config[CONF_MODE])))
    return var
