#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1. We renamed the macro to match our custom hardware */
#define MY_LED_NODE DT_ALIAS(my_custom_led)

/* 2. We renamed the variable to my_led */
static const struct gpio_dt_spec my_led = GPIO_DT_SPEC_GET(MY_LED_NODE, gpios);

int main(void)
{
    /* 3. Pass the new my_led variable to the Zephyr functions */
    if (!gpio_is_ready_dt(&my_led)) {
        return 0;
    }

    if (gpio_pin_configure_dt(&my_led, GPIO_OUTPUT_ACTIVE) < 0) {
        return 0;
    }

    while (1) {
        gpio_pin_toggle_dt(&my_led);
        k_msleep(100); 
        gpio_pin_toggle_dt(&my_led);
        k_msleep(2000); 
    }
    return 0;
}