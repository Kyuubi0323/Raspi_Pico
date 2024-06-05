#include "pico/stdlib.h"
#include <stdio.h>
#define BUILTIN_LED PICO_DEFAULT_LED_PIN
typedef struct repeating_timer repeating_timer;
bool led_timer_callback(repeating_timer *timer);
uint8_t led_state = 0;

int main()
{
    stdio_init_all();
    sleep_ms(2000);
    printf("LED_BLINK\r\n");
    gpio_init(BUILTIN_LED);
    gpio_set_dir(BUILTIN_LED, GPIO_OUT);
    repeating_timer led_timer;

    add_repeating_timer_ms(500, led_timer_callback, NULL, &led_timer);
    while (1)
    {
    //     gpio_put(BUILTIN_LED, 1);
    //     sleep_ms(100);
    //     gpio_put(BUILTIN_LED, 0);
    //     sleep_ms(100);
    }
}
bool led_timer_callback(repeating_timer *timer)
{
    led_state = !led_state;
    gpio_put(BUILTIN_LED, led_state);
    printf("TURN %s LED\r\n", led_state ? "ON" : "OFF");
    return true;
}
