#include "pico/stdlib.h"
#include <stdio.h>





#define BUILTIN_LED PICO_DEFAULT_LED_PIN

int main()
{
    stdio_init_all();
    gpio_init(BUILTIN_LED);
    gpio_set_dir(BUILTIN_LED, GPIO_OUT);

    

    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    while (1)
    {
        printf("Hello, world!\n");
        gpio_put(BUILTIN_LED, 1);
        sleep_ms(1000);
        gpio_put(BUILTIN_LED, 0);
        sleep_ms(1000);
    }

}