
#define DT_DRV_COMPAT raspberrypi_pico_gpio

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/sys_io.h>


#define INIT_PRIORITY_0 0


#define GPIO_BASE_ADDR 0x40014000


#define GPIO_OUT_OFFSET       0x10  /* GPIO output register */
#define GPIO_OUT_SET_OFFSET   0x14  /* GPIO output set register */
#define GPIO_OUT_CLR_OFFSET   0x18  /* GPIO output clear register */
#define GPIO_DIR_OFFSET       0x04  /* GPIO direction register */
#define GPIO_DIR_SET_OFFSET   0x08  /* GPIO direction set register */
#define GPIO_DIR_CLR_OFFSET   0x0C  /* GPIO direction clear register */

/* GPIO device configuration structure */
struct gpio_rpi_pico_config {
    uintptr_t base; /* Base address for GPIO registers */
};

/* GPIO driver data structure */
struct gpio_rpi_pico_data {
    uint32_t pinstate;
};

/* Function to configure a GPIO pin */
static int gpio_rpi_pico_configure(const struct device *dev, gpio_pin_t pin, gpio_flags_t flags)
{
    const struct gpio_rpi_pico_config *config = dev->config;

    /* Set direction */
    if (flags & GPIO_OUTPUT) {
        sys_write32((1 << pin), config->base + GPIO_DIR_SET_OFFSET); /* Set pin as output */
        if (flags & GPIO_OUTPUT_INIT_HIGH) {
            sys_write32((1 << pin), config->base + GPIO_OUT_SET_OFFSET); /* Set pin high */
        } else if (flags & GPIO_OUTPUT_INIT_LOW) {
            sys_write32((1 << pin), config->base + GPIO_OUT_CLR_OFFSET); /* Set pin low */
        }
    } else if (flags & GPIO_INPUT) {
        sys_write32((1 << pin), config->base + GPIO_DIR_CLR_OFFSET); /* Set pin as input */
    }


    return 0;
}

/* Function to set output state of a GPIO pin */
static int gpio_rpi_pico_port_set_bits(const struct device *dev, gpio_port_pins_t pins)
{
    const struct gpio_rpi_pico_config *config = dev->config;
    sys_write32(pins, config->base + GPIO_OUT_SET_OFFSET); /* Set bits high */
    return 0;
}

/* Function to clear output state of a GPIO pin */
static int gpio_rpi_pico_port_clear_bits(const struct device *dev, gpio_port_pins_t pins)
{
    const struct gpio_rpi_pico_config *config = dev->config;
    sys_write32(pins, config->base + GPIO_OUT_CLR_OFFSET); /* Clear bits */
    return 0;
}

/* Function to toggle output state of a GPIO pin */
static int gpio_rpi_pico_port_toggle_bits(const struct device *dev, gpio_port_pins_t pins)
{
    const struct gpio_rpi_pico_config *config = dev->config;
    uint32_t state = sys_read32(config->base + GPIO_OUT_OFFSET);
    sys_write32(state ^ pins, config->base + GPIO_OUT_OFFSET); /* Toggle bits */
    return 0;
}

/* GPIO driver API structure */
static const struct gpio_driver_api gpio_rpi_pico_driver_api = {
    .pin_configure = gpio_rpi_pico_configure,
    .port_set_bits_raw = gpio_rpi_pico_port_set_bits,
    .port_clear_bits_raw = gpio_rpi_pico_port_clear_bits,
    .port_toggle_bits = gpio_rpi_pico_port_toggle_bits,
};

/* Initialize the GPIO device */
static int gpio_rpi_pico_init(const struct device *dev)
{
    return 0;
}

/* Device configuration structure */
static const struct gpio_rpi_pico_config gpio_rpi_pico_config_0 = {
    .base = GPIO_BASE_ADDR,
};

/* Device data structure */
static struct gpio_rpi_pico_data gpio_rpi_pico_data_0;

/* Define the device */
DEVICE_DT_INST_DEFINE(0, gpio_rpi_pico_init, NULL, &gpio_rpi_pico_data_0,
                      &gpio_rpi_pico_config_0, POST_KERNEL,
                      INIT_PRIORITY_0, &gpio_rpi_pico_driver_api);

