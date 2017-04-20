
#ifndef __TIMERHANDLER_H__
#define __TIMERHANDLER_H__


#define TICKRATE_HZ1    (1000)	/* 1000 ticks per second */

extern uint8_t nagle_flag;
extern uint32_t nagle_time;
extern uint32_t uart_recv_count;

extern uint8_t reconn_flag;
extern uint32_t reconn_time;

extern uint8_t inactive_flag;
extern uint32_t inactive_time;
extern uint32_t ether_send_prev;
extern uint32_t ether_recv_prev;
extern uint8_t keepsend_flag;
extern uint32_t keepsend_time;

extern uint8_t trigger_flag;
extern uint32_t trigger_time;

extern volatile uint8_t factory_flag;
extern volatile uint32_t factory_time;

extern uint8_t auth_flag;
extern uint32_t auth_time;

extern volatile uint8_t g_check_temp;
extern volatile uint8_t g_check_sensors;

void Timer0_Configuration(void);
void delay_cnt(uint32_t count);
void delay_ms(uint32_t ms);

void Timer_IRQ_Handler(void);

#endif
