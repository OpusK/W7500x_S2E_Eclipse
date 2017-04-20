/*
 * W7500x_board.h
 *
 *  Created on: 2017. 3. 24.
 *      Author: KEI
 */

#ifndef W7500X_BOARD_H_
#define W7500X_BOARD_H_


#include <stdint.h>
#include "common.h"

////////////////////////////////
// Available board list       //
////////////////////////////////
#define WIZwiki_W7500       1
#define WIZwiki_W7500P      2
#define WIZwiki_W7500ECO    3
#define WIZ750SR            4
#define WIZ750JR            5
#define W7500P_S2E          6
#define WIZ750MINI          7
#define UNKNOWN_DEVICE      0xff

////////////////////////////////
// Product Configurations     //
////////////////////////////////
/* Target Board Selector */
#define DEVICE_BOARD_NAME WIZwiki_W7500
//#define DEVICE_BOARD_NAME WIZwiki_W7500P
//#define DEVICE_BOARD_NAME WIZwiki_W7500ECO
//#define DEVICE_BOARD_NAME WIZ750SR
//#define DEVICE_BOARD_NAME WIZ750JR
//#define DEVICE_BOARD_NAME WIZ750MINI
//#define DEVICE_BOARD_NAME W7500P_S2E


#ifdef DEVICE_BOARD_NAME
    #if (DEVICE_BOARD_NAME == WIZwiki_W7500)
        #define __W7500__
        #define __USE_APPBACKUP_AREA__
        //#define UART_DEBUG UART0
        #define UART_DATA UART1
        #define DEVICE_CLOCK_SELECT          CLOCK_SOURCE_EXTERNAL
        #define DEVICE_PLL_SOURCE_CLOCK      PLL_SOURCE_8MHz
        #define DEVICE_TARGET_SYSTEM_CLOCK   SYSTEM_CLOCK_48MHz
        #define DEVICE_ID_DEFAULT            "WIZwiki"
    #elif (DEVICE_BOARD_NAME == WIZwiki_W7500P)
        #define __W7500P__
        #define __USE_APPBACKUP_AREA__
        //#define UART_DEBUG UART0
        #define UART_DATA UART0
        #define DEVICE_CLOCK_SELECT          CLOCK_SOURCE_EXTERNAL
        #define DEVICE_PLL_SOURCE_CLOCK      PLL_SOURCE_8MHz
        #define DEVICE_TARGET_SYSTEM_CLOCK   SYSTEM_CLOCK_48MHz
        #define DEVICE_ID_DEFAULT            "WIZwiki_P"
    #elif (DEVICE_BOARD_NAME == WIZwiki_W7500ECO)
        #define __W7500__
        #define __USE_EXT_EEPROM__          // External EEPROM or Internal Data flash (DAT0/1)
        #define __USE_APPBACKUP_AREA__
        //#define UART_DEBUG UART0
        #define UART_DATA UART1
        #define DEVICE_CLOCK_SELECT          CLOCK_SOURCE_EXTERNAL
        #define DEVICE_PLL_SOURCE_CLOCK      PLL_SOURCE_8MHz
        #define DEVICE_TARGET_SYSTEM_CLOCK   SYSTEM_CLOCK_48MHz
        #define DEVICE_ID_DEFAULT            "WIZwiki_ECO"
    #elif (DEVICE_BOARD_NAME == WIZ750SR)
        #define __W7500P__
        #define __USE_UART_IF_SELECTOR__    // RS-232/TTL or RS-422/485 selector using UART IF selector pin
        #define __USE_EXT_EEPROM__          // External EEPROM or Internal Data flash (DAT0/1)
        #define __USE_BOOT_ENTRY__          // Application boot mode entry pin activated
        #define __USE_APPBACKUP_AREA__      // If this option activated, Application firmware area is consists of App (50kB) and App backup (50kB). If not, user's application can be 100kB size. (Does not use the backup area)
        #define __USE_GPIO_HARDWARE_FLOWCONTROL__
        #define __USE_USERS_GPIO__
        #define UART_DATA UART0
        #define DEVICE_CLOCK_SELECT          CLOCK_SOURCE_EXTERNAL
        #define DEVICE_PLL_SOURCE_CLOCK      PLL_SOURCE_12MHz
        #define DEVICE_TARGET_SYSTEM_CLOCK   SYSTEM_CLOCK_48MHz
        #define DEVICE_ID_DEFAULT            "WIZ750SR" // Device name
    #elif (DEVICE_BOARD_NAME == WIZ750JR)
        //#define __USE_UART_IF_SELECTOR__  // RS-232/TTL or RS-422/485 selector using UART IF selector pin
        #define __USE_EXT_EEPROM__          // External EEPROM or Internal Data flash (DAT0/1)
        #define __USE_BOOT_ENTRY__          // Application boot mode entry pin activated
        #define __USE_APPBACKUP_AREA__      // If this option activated, Application firmware area is consists of App (50kB) and App backup (50kB). If not, user's application can be 100kB size. (Does not use the backup area)
        #define __USE_GPIO_HARDWARE_FLOWCONTROL__
        //#define __USE_USERS_GPIO__
        #define UART_DATA UART0
        #define DEVICE_CLOCK_SELECT          CLOCK_SOURCE_EXTERNAL
        #define DEVICE_PLL_SOURCE_CLOCK      PLL_SOURCE_12MHz
        #define DEVICE_TARGET_SYSTEM_CLOCK   SYSTEM_CLOCK_48MHz
        #define DEVICE_ID_DEFAULT            "WIZ750Jr" // Device name
    #elif (DEVICE_BOARD_NAME == W7500P_S2E) // Chip product
        #define __W7500P__
        #define __USE_UART_IF_SELECTOR__    // RS-232/TTL or RS-422/485 selector using UART IF selector pin
        #define __USE_BOOT_ENTRY__          // Application boot mode entry pin activated
        #define __USE_APPBACKUP_AREA__
        #define __USE_GPIO_HARDWARE_FLOWCONTROL__
        #define __USE_USERS_GPIO__
        #define UART_DATA UART1
        #define DEVICE_CLOCK_SELECT          CLOCK_SOURCE_EXTERNAL
        #define DEVICE_PLL_SOURCE_CLOCK      PLL_SOURCE_12MHz
        #define DEVICE_TARGET_SYSTEM_CLOCK   SYSTEM_CLOCK_48MHz
        #define DEVICE_ID_DEFAULT            "W7500P-S2E"
    #elif (DEVICE_BOARD_NAME == WIZ750MINI)
        #define __W7500P__
        #define __USE_UART_IF_SELECTOR__    // RS-232/TTL or RS-422/485 selector using UART IF selector pin
        #define __USE_EXT_EEPROM__          // External EEPROM or Internal Data flash (DAT0/1)
        #define __USE_BOOT_ENTRY__          // Application boot mode entry pin activated
        #define __USE_APPBACKUP_AREA__      // If this option activated, Application firmware area is consists of App (50kB) and App backup (50kB). If not, user's application can be 100kB size. (Does not use the backup area)
        #define __USE_GPIO_HARDWARE_FLOWCONTROL__
        //#define __USE_USERS_GPIO__
        #define UART_DATA UART0
        #define DEVICE_CLOCK_SELECT          CLOCK_SOURCE_EXTERNAL
        #define DEVICE_PLL_SOURCE_CLOCK      PLL_SOURCE_12MHz
        #define DEVICE_TARGET_SYSTEM_CLOCK   SYSTEM_CLOCK_48MHz
        #define DEVICE_ID_DEFAULT            "WIZ750Mini" // Device name
    #else
        //#define __USE_UART_IF_SELECTOR__
        #define __USE_EXT_EEPROM__
        #define __USE_APPBACKUP_AREA__
        #define __USE_GPIO_HARDWARE_FLOWCONTROL__
        #define UART_DATA UART1
        #define DEVICE_CLOCK_SELECT          CLOCK_SOURCE_EXTERNAL
        #define DEVICE_PLL_SOURCE_CLOCK      PLL_SOURCE_8MHz
        #define DEVICE_TARGET_SYSTEM_CLOCK   SYSTEM_CLOCK_48MHz
        #define DEVICE_ID_DEFAULT            "W7500-S2E" // Device name: WIZwiki_W7500 or WIZwiki_W7500ECO Board
    #endif
#else
    #define __USE_APPBACKUP_AREA__
    #define UART_DATA UART1
    #define DEVICE_CLOCK_SELECT              CLOCK_SOURCE_INTERNAL
    #define DEVICE_PLL_SOURCE_CLOCK          PLL_SOURCE_8MHz
    #define DEVICE_TARGET_SYSTEM_CLOCK       SYSTEM_CLOCK_48MHz
    #define DEVICE_BOARD_NAME                UNKNOWN_DEVICE
    #define DEVICE_ID_DEFAULT                "UNKNOWN"
#endif

// PHY init defines: USE MDC/MDIO
#define __DEF_USED_MDIO__

#ifdef __DEF_USED_MDIO__ // MDC/MDIO defines
    #ifndef __W7500P__ // W7500
        //#define __DEF_USED_IC101AG__ // PHY initialize for WIZwiki-W7500 Board
        #define W7500x_MDIO    GPIO_Pin_14
        #define W7500x_MDC     GPIO_Pin_15
    #else // W7500P
        #define W7500x_MDIO    GPIO_Pin_15
        #define W7500x_MDC     GPIO_Pin_14
    #endif
#endif

/* PHY Link check  */
#define PHYLINK_CHECK_CYCLE_MSEC    1000

////////////////////////////////
// Pin definitions            //
////////////////////////////////
// PHY link status pin: Input (PHYLINK_IN_PIN -> STATUS_PHYLINK_PIN)
#define PHYLINK_IN_PIN              GPIO_Pin_9
#define PHYLINK_IN_PORT             GPIOA
#define PHYLINK_IN_PAD_AF           PAD_AF1 // PAD Config - LED used 2nd Function

#if (DEVICE_BOARD_NAME == WIZ750JR) // ##20161031 WIZ750Jr

    // Connection status indicator pins
    // Direction: Output
    #define STATUS_PHYLINK_PIN          GPIO_Pin_10
    #define STATUS_PHYLINK_PORT         GPIOA
    #define STATUS_PHYLINK_PAD_AF       PAD_AF1

    #define STATUS_TCPCONNECT_PIN       GPIO_Pin_1
    #define STATUS_TCPCONNECT_PORT      STATUS_PHYLINK_PORT
    #define STATUS_TCPCONNECT_PAD_AF    STATUS_PHYLINK_PAD_AF

    #define DTR_PIN                     GPIO_Pin_0
    #define DTR_PORT                    GPIOB
    #define DTR_PAD_AF                  PAD_AF1

    #define DSR_PIN                     GPIO_Pin_15
    #define DSR_PORT                    GPIOA
    #define DSR_PAD_AF                  PAD_AF1

    // HW_TRIG - Command mode switch enable pin
    // Direction: Input (Shared pin with TCP connection status pin)
    #define HW_TRIG_PIN                 GPIO_Pin_15
    #define HW_TRIG_PORT                GPIOC
    #define HW_TRIG_PAD_AF              PAD_AF1

#else // Original pins

    // Connection status indicator pins
    // Direction: Output
    #define STATUS_PHYLINK_PIN          GPIO_Pin_10
    #define STATUS_PHYLINK_PORT         GPIOA
    #define STATUS_PHYLINK_PAD_AF       PAD_AF1

    #define STATUS_TCPCONNECT_PIN       GPIO_Pin_1
    #define STATUS_TCPCONNECT_PORT      STATUS_PHYLINK_PORT
    #define STATUS_TCPCONNECT_PAD_AF    STATUS_PHYLINK_PAD_AF

    // DTR / DSR - Handshaking signals, Shared with PHYLINK_PIN and TCPCONNECT_PIN (selectable)
    // > DTR - Data Terminal Ready, Direction: Output (= PHYLINK_PIN)
    //      >> This signal pin asserted when the device could be possible to transmit the UART inputs
    //      >> [O], After boot and initialize
    //      >> [X], nope (E.g., TCP connected (Server / client mode) or TCP mixed mode or UDP mode)
    // > DSR - Data Set Ready, Direction: Input (= TCPCONNECT_PIN)
    //      >> [O] Ethet_to_UART() function control

    #define DTR_PIN                     STATUS_PHYLINK_PIN
    #define DTR_PORT                    STATUS_PHYLINK_PORT
    #define DTR_PAD_AF                  STATUS_PHYLINK_PAD_AF

    #define DSR_PIN                     STATUS_TCPCONNECT_PIN
    #define DSR_PORT                    STATUS_TCPCONNECT_PORT
    #define DSR_PAD_AF                  STATUS_TCPCONNECT_PAD_AF

    // HW_TRIG - Command mode switch enable pin
    // Direction: Input (Shared pin with TCP connection status pin)
    #define HW_TRIG_PIN                 STATUS_TCPCONNECT_PIN
    #define HW_TRIG_PORT                STATUS_TCPCONNECT_PORT
    #define HW_TRIG_PAD_AF              STATUS_TCPCONNECT_PAD_AF

#endif

// UART Interface Selector Pin (temporary pin)
// [Pull-down] RS-232/TTL mode
// [Pull-up  ] RS-422/485 mode
// if does not use this pin, UART interface is fixed RS-232 / TTL mode
#ifdef __USE_UART_IF_SELECTOR__
    #define UART_IF_SEL_PIN         GPIO_Pin_6
    #define UART_IF_SEL_PORT        GPIOC
    #define UART_IF_SEL_PAD_AF      PAD_AF1 // Used 2nd Function, GPIO
#endif

// Configuration Storage Selector
// Internal data flash (DAT0/DAT1) or External EEPROM (I2C bus interface via GPIO pins)
#ifdef __USE_EXT_EEPROM__
    //#include "i2cHandler.h"
    #define EEPROM_I2C_SCL_PIN      I2C_SCL_PIN
    #define EEPROM_I2C_SCL_PORT     I2C_SCL_PORT
    #define EEPROM_I2C_SDA_PIN      I2C_SDA_PIN
    #define EEPROM_I2C_SDA_PORT     I2C_SDA_PORT
    #define EEPROM_I2C_PAD_AF       I2C_PAD_AF // GPIO
#endif

#ifdef __USE_BOOT_ENTRY__
    #define BOOT_ENTRY_PIN          GPIO_Pin_14
    #define BOOT_ENTRY_PORT         GPIOC
    #define BOOT_ENTRY_PAD_AF       PAD_AF1
#endif

// Expansion GPIOs (4-Pins, GPIO A / B / C / D)

#ifdef __USE_USERS_GPIO__

    //#define MAX_USER_IOn    16
    #define USER_IOn       4
    #define USER_IO_A      (uint16_t)(0x01 <<  0)     // USER's I/O A
    #define USER_IO_B      (uint16_t)(0x01 <<  1)     // USER's I/O B
    #define USER_IO_C      (uint16_t)(0x01 <<  2)     // USER's I/O C
    #define USER_IO_D      (uint16_t)(0x01 <<  3)     // USER's I/O D

    #define USER_IO_DEFAULT_PAD_AF      PAD_AF1 // [2nd] GPIO
    #define USER_IO_AIN_PAD_AF          PAD_AF3 // [4th] AIN

    #define USER_IO_NO_ADC              0xff

    // USER IO pins for WIZ750SR / WIZwiki-W7500ECO
    #define USER_IO_A_PIN               GPIO_Pin_13 // ECO: P28, AIN2
    #define USER_IO_A_PORT              GPIOC
    #define USER_IO_A_ADC_CH            ADC_CH2

    #define USER_IO_B_PIN               GPIO_Pin_12 // ECO: P27, AIN3
    #define USER_IO_B_PORT              GPIOC
    #define USER_IO_B_ADC_CH            ADC_CH3

    #define USER_IO_C_PIN               GPIO_Pin_9 // ECO: P26, AIN6
    #define USER_IO_C_PORT              GPIOC
    #define USER_IO_C_ADC_CH            ADC_CH6

    #define USER_IO_D_PIN               GPIO_Pin_8 // ECO: P25, AIN7
    #define USER_IO_D_PORT              GPIOC
    #define USER_IO_D_ADC_CH            ADC_CH7

#endif
#if 0
/*
// Status LEDs define
#if ((DEVICE_BOARD_NAME == WIZ750SR) || (DEVICE_BOARD_NAME == W7500P_S2E) || (DEVICE_BOARD_NAME == WIZ750MINI))

    #define LED1_PIN            GPIO_Pin_2
    #define LED1_GPIO_PORT      GPIOB
    #define LED1_GPIO_PAD       PAD_PB
    #define LED1_GPIO_PAD_AF    PAD_AF1     // PAD Config - LED used 2nd Function

    #define LED2_PIN            GPIO_Pin_3
    #define LED2_GPIO_PORT      GPIOB
    #define LED2_GPIO_PAD       PAD_PB
    #define LED2_GPIO_PAD_AF    PAD_AF1

#elif (DEVICE_BOARD_NAME == WIZ750JR) // ##20161031 WIZ750Jr

    #define LED1_PIN            GPIO_Pin_8
    #define LED1_GPIO_PORT      GPIOC
    #define LED1_GPIO_PAD       PAD_PC
    #define LED1_GPIO_PAD_AF    PAD_AF1     // PAD Config - LED used 2nd Function

    #define LED2_PIN            GPIO_Pin_9
    #define LED2_GPIO_PORT      GPIOC
    #define LED2_GPIO_PAD       PAD_PC
    #define LED2_GPIO_PAD_AF    PAD_AF1

#elif (DEVICE_BOARD_NAME == WIZwiki_W7500ECO)

    #define LED1_PIN            GPIO_Pin_1
    #define LED1_GPIO_PORT      GPIOA
    #define LED1_GPIO_PAD       PAD_PA
    #define LED1_GPIO_PAD_AF    PAD_AF1     // PAD Config - LED used 2nd Function

    #define LED2_PIN            GPIO_Pin_2
    #define LED2_GPIO_PORT      GPIOA
    #define LED2_GPIO_PAD       PAD_PA
    #define LED2_GPIO_PAD_AF    PAD_AF1

#else // WIZwiki-W7500 board

    // [RGB LED] R: PC_08, G: PC_09, B: PC_05
    #define LED1_PIN            GPIO_Pin_8 // RGB LED: RED
    #define LED1_GPIO_PORT      GPIOC
    #define LED1_GPIO_PAD       PAD_PC
    #define LED1_GPIO_PAD_AF    PAD_AF1

    #define LED2_PIN            GPIO_Pin_9 // RGB LED: GREEN
    #define LED2_GPIO_PORT      GPIOC
    #define LED2_GPIO_PAD       PAD_PC
    #define LED2_GPIO_PAD_AF    PAD_AF1
*/
/*
    #define LED_R_PIN           GPIO_Pin_8
    #define LED_R_GPIO_PORT     GPIOC
    #define LED_R_GPIO_PAD      PAD_PC
    #define LED_R_GPIO_PAD_AF   PAD_AF1

    #define LED_G_PIN           GPIO_Pin_9
    #define LED_G_GPIO_PORT     GPIOC
    #define LED_G_GPIO_PAD      PAD_PC
    #define LED_G_GPIO_PAD_AF   PAD_AF1

    #define LED_B_PIN           GPIO_Pin_5
    #define LED_B_GPIO_PORT     GPIOC
    #define LED_B_GPIO_PAD      PAD_PC
    #define LED_B_GPIO_PAD_AF   PAD_AF1

    // LED
    #define LEDn        3
    typedef enum
    {
      LED_R = 0,
      LED_G = 1,
      LED_B = 2
    } Led_TypeDef;
*/

/*
    // LED
    #define LEDn        2
    typedef enum
    {
      LED1 = 0, // PHY link status
      LED2 = 1  // TCP connection status
    } Led_TypeDef;

    extern volatile uint16_t phylink_check_time_msec;
    extern uint8_t flag_check_phylink;
    extern uint8_t flag_hw_trig_enable;

    void W7500x_Board_Init(void);
    void Supervisory_IC_Init(void);
*/
#endif

#endif /* W7500X_BOARD_H_ */
