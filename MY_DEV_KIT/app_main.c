#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include
#include "app_param.h"
#include "service/log/log.h"

#define FLAG_VALUE 123

#define BUILTIN_LED PICO_DEFAULT_LED_PIN
uint8_t led_state = 0;

typedef struct repeating_timer repeating_timer;

bool led_timer_callback(repeating_timer *timer)
{
    led_state = !led_state;
    gpio_put(BUILTIN_LED, led_state);
    printf("TURN %s LED\r\n", led_state ? "ON" : "OFF");
    return true;
}

int64_t init_info_callback(alarm_id_t id, void *user_data) {
    printf("Main app running -> DEV_KIT\r\n");
    return 0;
}

void task_core_entry()
{
    while (1) {
        // Function pointer is passed to us via the FIFO
        // We have one incoming int32_t as a parameter, and will provide an
        // int32_t return value by simply pushing it back on the FIFO
        // which also indicates the result is ready.
        int32_t (*func)() = (int32_t(*)()) multicore_fifo_pop_blocking();
        int32_t p = multicore_fifo_pop_blocking();
        int32_t result = (*func)(p);
        multicore_fifo_push_blocking(result);
    }
}

int main()
{
    stdio_init_all();
    /* Wait for Terminal USB Initialize*/
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    //add_alarm_in_ms(1000, init_info_callback, NULL, false);
    /* Main app firmware*/
    printf(MCU_INFO);
    printf(MCU_INFO_FM, FIRMWARE_VERSION, HARDWARE_VERSION, __DATE__, __TIME__);

    gpio_init(BUILTIN_LED);
    gpio_set_dir(BUILTIN_LED, GPIO_OUT);

    repeating_timer led_timer;
    add_repeating_timer_ms(2000, led_timer_callback, NULL, &led_timer);

    multicore_launch_core1(task_core_entry);
    uint32_t g = multicore_fifo_pop_blocking();
    printf("Size %d", g);
    // if (g != FLAG_VALUE)
    //     printf("Hmm, that's not right on core 0!\n");
    // else {
    //     multicore_fifo_push_blocking(FLAG_VALUE);
    //     printf("It's all gone well on core 0!");
    // }
}

