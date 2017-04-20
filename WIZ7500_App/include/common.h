
#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>

////////////////////////////////
// Product Version            //
////////////////////////////////
/* Application Firmware Version */
#define MAJOR_VER       1
#define MINOR_VER       0
#define MAINTENANCE_VER 0

//#define STR_VERSION_STATUS    "Develop" // or "Stable"
#define STR_VERSION_STATUS  "Stable"

////////////////////////////////
// W7500x HW Socket Definition//
////////////////////////////////
// 0 ~ 6, Changed the S2E data socket(0)'s buffer to double
#define SOCK_MAX_USED       7

#define SOCK_DATA       0
#define SOCK_TFTP       1
#define SOCK_CONFIG     2
#define SOCK_DHCP       3
#define SOCK_DNS        4

#define OP_COMMAND      0
#define OP_DATA         1

/* Buffer size */
#define WORK_BUF_SIZE   2048

////////////////////////////////
// In/External Clock Setting  //
////////////////////////////////
/* W7500x Board Internal / External OSC clock Settings */
#define CLOCK_SOURCE_INTERNAL   (0x0UL)
#define CLOCK_SOURCE_EXTERNAL   (0x1UL)

// Source clock frequency
#define PLL_SOURCE_8MHz     (8000000UL)     /* 8MHz Internal / External Oscillator Frequency   */
#define PLL_SOURCE_12MHz    (12000000UL)    /* 12MHz External Oscillator Frequency             */
#define PLL_SOURCE_24MHz    (24000000UL)    /* 24MHz External Oscillator Frequency             */

// Targer system clock frequency
#define SYSTEM_CLOCK_8MHz   (8000000UL)
#define SYSTEM_CLOCK_12MHz  (12000000UL)
#define SYSTEM_CLOCK_16MHz  (16000000UL)
#define SYSTEM_CLOCK_24MHz  (24000000UL)
#define SYSTEM_CLOCK_32MHz  (32000000UL)
#define SYSTEM_CLOCK_36MHz  (36000000UL)
#define SYSTEM_CLOCK_48MHz  (48000000UL)    // W7500x maximum clock frequency

#define DEVICE_BOOT_ADDR                    0x00000000
#define DEVICE_BOOT_SIZE                    (28*1024)
#define DEVICE_APP_MAIN_ADDR                (DEVICE_BOOT_ADDR + DEVICE_BOOT_SIZE)
#define APP_BASE        0x00007000          // Boot Size 28K

extern uint8_t op_mode;

#endif
