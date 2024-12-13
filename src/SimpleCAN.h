#if defined(ARDUINO_ARCH_ESP32)
#include "esp/twai/CAN.h"
#elif defined(ARDUINO_ARCH_STM32)
    #if defined(STM32G4xx) || defined(STM32H7xx) || defined(STM32L5xx)
        #ifndef HAL_FDCAN_MODULE_ENABLED
            #define HAL_FDCAN_MODULE_ENABLED
        #endif
        #include "stm/fdcan/CAN.h"
    #elif defined(HAL_CAN_MODULE_ENABLED)
        #include "stm/can/CAN.h"
    #else
        #error "This STM32 family does not support CAN or FDCAN"
    #endif
#elif defined(ARDUINO_ARCH_GD32)
#include "gd/can2b/CAN.h"
#else
#error "No CAN module is enabled, expecting a define for ARDUINO_ARCH_ESP32 | ARDUINO_ARCH_STM32 | ARDUINO_ARCH_GD32"
#endif