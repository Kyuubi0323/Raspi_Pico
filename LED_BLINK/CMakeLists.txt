cmake_minimum_required(VERSION 3.18)
include(pico_sdk_import.cmake)




project(LED_BLINK C CXX ASM)
pico_sdk_init()
add_executable(main main.c)
pico_add_extra_outputs(main)
target_link_libraries(main pico_stdlib)
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
