/**
  ******************************************************************************
  * @file    main.c
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h2>
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "W7500x_crg.h"
#include "W7500x_wztoe.h"
#include "W7500x_miim.h"
#include "W7500x_i2c.h"
#include "W7500x_adc.h"
#include "W7500x_rng.h"
#include "common.h"
#include "uartHandler.h"
#include "flashHandler.h"
#include "storageHandler.h"
#include "gpioHandler.h"
#include "timerHandler.h"
#include "tftp.h"
#include "ConfigData.h"
#include "ConfigMessage.h"
#include "extiHandler.h"
#include "DHCP/dhcp.h"
#include "DNS/dns.h"
#include "S2E.h"
#include "dhcp_cb.h"
#include "atcmd.h"
#include "W7500x_board.h"

/* Private typedef -----------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;
I2C_ConfigStruct conf;

/* Private define ------------------------------------------------------------*/
#ifndef __W7500P__ // for W7500
	#define __DEF_USED_IC101AG__ //for W7500 Test main Board V001
#endif

///////////////////////////////////////
// Debugging Message Printout enable //
///////////////////////////////////////
#define _MAIN_DEBUG_

///////////////////////////
// Demo Firmware Version //
///////////////////////////
#define VER_H		1
#define VER_L		00

/* Private function prototypes -----------------------------------------------*/
void initW7500x();
void initBoardIO();
void initNetDevice();
void delay(__IO uint32_t milliseconds); //Notice: used ioLibray
void TimingDelay_Decrement(void);


/* Private variables ---------------------------------------------------------*/
/* Transmit and receive buffers */
static __IO uint32_t TimingDelay;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
uint8_t g_send_buf[WORK_BUF_SIZE];
uint8_t g_recv_buf[WORK_BUF_SIZE];

uint8_t run_dns = 1;
uint8_t op_mode;
volatile uint8_t factory_flag;
volatile uint32_t factory_time;

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main()
{
	S2E_Packet *value = get_S2E_Packet_pointer();
	uint8_t dns_server_ip[4];

	initW7500x();

    initBoardIO();

	/* Load Configure Information */
	load_S2E_Packet_from_storage();

	UART_Configuration();

	//  UART_StructInit(&UART_InitStructure);
	//  UART_Init(UART_DEBUG, &UART_InitStructure);

	Timer0_Configuration();

    initNetDevice();

	/* Initialize Network Information */
	if(value->options.dhcp_use) {		// DHCP
		uint32_t ret;
		uint8_t dhcp_retry = 0;

		DHCP_init(SOCK_DHCP, g_send_buf);
		//printf("Start DHCP...\r\n");
		while(1) {
			ret = DHCP_run();

			if(ret == DHCP_IP_LEASED)
				break;
			else if(ret == DHCP_FAILED)
				dhcp_retry++;

			if(dhcp_retry > 3) {
				Net_Conf();
				break;
			}
			do_udp_config(SOCK_CONFIG);
		}
	} else{  // Static
	        Net_Conf();
	}


	if(value->options.dns_use) {
		uint8_t dns_retry = 0;

		DNS_init(SOCK_DNS, g_send_buf);

		memcpy(dns_server_ip, value->options.dns_server_ip, sizeof(dns_server_ip));

		while(1) {
			if(DNS_run(dns_server_ip, (uint8_t *)value->options.dns_domain_name, value->network_info[0].remote_ip) == 1)
				break;
			else
				dns_retry++;

			if(dns_retry > 3) {
				break;
			}

			do_udp_config(SOCK_CONFIG);

			if(value->options.dhcp_use)
				DHCP_run();
		}
	}

	display_Net_Info();

	atc_init();
	op_mode = OP_DATA;

	while (1) {
	    do_udp_config(SOCK_CONFIG);

		if(op_mode == OP_COMMAND) {			// Command Mode
			atc_run();
			sockwatch_run();
		} else {							// DATA Mode
			s2e_run(SOCK_DATA);
		}

		if(value->options.dhcp_use)
			DHCP_run();

		if(value->options.dns_use && run_dns == 1) {
			memcpy(dns_server_ip, value->options.dns_server_ip, sizeof(dns_server_ip));

			if(DNS_run(dns_server_ip, (uint8_t *)value->options.dns_domain_name, value->network_info[0].remote_ip) == 1) {
				run_dns = 0;
			}
		}
	}
    return 0;
}


/*****************************************************************************
 * Function Definition
 ****************************************************************************/

/**
  * @brief
  * @param
  * @retval None
  */
void initW7500x()
{
    /* Set System init */
    SystemInit_User(DEVICE_CLOCK_SELECT, DEVICE_PLL_SOURCE_CLOCK, DEVICE_TARGET_SYSTEM_CLOCK);

    /* UART2 Init */
    S_UART_Init(115200);

    /* SysTick_Config */
    SysTick_Config((GetSystemClock()/1000));

    /* Set WZ_100US Register */
    setTIC100US((GetSystemClock()/10000));
    //getTIC100US();
    //printf(" GetSystemClock: %X, getTIC100US: %X, (%X) \r\n",
    //      GetSystemClock, getTIC100US(), *(uint32_t *)TIC100US);

#ifdef _MAIN_DEBUG_
    printf("============================================\r\n");
    printf(" WIZ750S2E Platform based S2E App           \r\n");
    printf("============================================\r\n");
#endif
}

/**
  * @brief
  * @param
  * @retval None
  */
void initBoardIO()
{
    LED_Init(LED1);
    LED_Init(LED2);
    LED_Init(LED3);

#if defined(ENABLE_RS485)
    RS485_Init(RS485RE);
    RS485_Init(RS485DE);
    RS485Tx_Off();
#endif

    LED_Off(LED1);
    LED_Off(LED2);
    LED_Off(LED3);

    //BOOT_Pin_Init();
    //Board_factory_Init();
    //EXTI_Configuration();

#if defined(__USE_EXT_EEPROM__) // __USE_EXT_EEPROM__
    I2C1_Init();
#endif
}

/**
  * @brief
  * @param
  * @retval None
  */
void initNetDevice()
{
#ifdef __DEF_USED_IC101AG__ //For using IC+101AG
    *(volatile uint32_t *)(0x41003068) = 0x64; //TXD0 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x4100306C) = 0x64; //TXD1 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003070) = 0x64; //TXD2 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003074) = 0x64; //TXD3 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003050) = 0x64; //TXE  - set PAD strengh and pull-up
#endif
#ifdef __W7500P__
    *(volatile uint32_t *)(0x41003070) = 0x61;
    *(volatile uint32_t *)(0x41003054) = 0x61;
#endif

#ifdef __DEF_USED_MDIO__
    /* mdio Init */
    mdio_init(GPIOB, MDC, MDIO);
//    printf("%d \r\n", PHY_ADDR);
    /* PHY Link Check via gpio mdio */
    while( link() == 0x0)
    {
        printf(".");
        delay(500);
    }
    printf("[APP] PHY is linked. \r\n");
#else
    delay(1000);
    delay(1000);
#endif

    Mac_Conf();
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void delay(__IO uint32_t milliseconds)
{
  TimingDelay = milliseconds;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
