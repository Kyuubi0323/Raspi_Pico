#include "pico/stdlib.h"
 
#define BUILTIN_LED PICO_DEFAULT_LED_PIN
 
int main()
{
    gpio_init(BUILTIN_LED);
    gpio_set_dir(BUILTIN_LED, GPIO_OUT);
    while (1)
    {
        gpio_put(BUILTIN_LED, 1);
        sleep_ms(100);
        gpio_put(BUILTIN_LED, 0);
        sleep_ms(100);
    }
}
