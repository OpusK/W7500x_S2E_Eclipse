
#include <stdbool.h>
#include "W7500x_dualtimer.h"
#include "gpioHandler.h"
#include "uartHandler.h"
#include "timerHandler.h"
#include "tftp.h"
#include "socket.h"
#include "ConfigData.h"
#include "timerHandler.h"
#include "DHCP/dhcp.h"
#include "DNS/dns.h"

static uint32_t mill_sec = 0;
static volatile uint32_t time_cnt = 0;

void Time_Counter_Configuration(void)
{
	time_cnt = 0;
}

void Time_Counter(void)
{
	if(time_cnt++ >= DEFINED_COUNT_THRESHOLD_VAL)
	{
		Timer_IRQ_Handler();
		time_cnt = 0;
	}
}

/**
 * @brief  Configures the Timer
 * @param  None
 * @return None
 */
void Timer0_Configuration(void)
{
	DUALTIMER_InitTypDef Dualtimer_InitStructure;

	NVIC_EnableIRQ(DUALTIMER0_IRQn);

    /* Dualtimer 0_0 clock enable */
    DUALTIMER_ClockEnable(DUALTIMER0_0);

    /* Dualtimer 0_0 configuration */
    Dualtimer_InitStructure.TimerLoad = 3000;//20000;//0x4FFFF;
    Dualtimer_InitStructure.TimerControl_Mode = DUALTIMER_TimerControl_Periodic;
    Dualtimer_InitStructure.TimerControl_OneShot = DUALTIMER_TimerControl_Wrapping;
    Dualtimer_InitStructure.TimerControl_Pre = DUALTIMER_TimerControl_Pre_16;
    Dualtimer_InitStructure.TimerControl_Size = DUALTIMER_TimerControl_Size_32;

    DUALTIMER_Init(DUALTIMER0_0, &Dualtimer_InitStructure);

    /* Dualtimer 0_0 Interrupt enable */
    DUALTIMER_IntConfig(DUALTIMER0_0, ENABLE);

    /* Dualtimer 0_0 start */
    DUALTIMER_Start(DUALTIMER0_0);
}

//void DUALTIMER0_Handler(void)
void Timer_IRQ_Handler(void)
{
//	if(DUALTIMER_GetIntStatus(DUALTIMER0_0))
//	{
//		DUALTIMER_IntClear(DUALTIMER0_0);

		mill_sec++;

		if((mill_sec % 500) == 0) {
			LED_Toggle(LED1);
			LED_Toggle(LED2);
		}

		if((mill_sec % 1000) == 0) {
			mill_sec = 0;
			tftp_timeout_handler();
		}
//	}
}



void delay_cnt(uint32_t count)
{
	volatile uint32_t tmp = count;

	while(tmp--);
}

void delay_ms(uint32_t ms)
{
	volatile uint32_t nCount;

	nCount=(GetSystemClock()/10000)*ms;
	for (; nCount!=0; nCount--);
}

