
#ifndef __TIMERHANDLER_H__
#define __TIMERHANDLER_H__

#define DEFINED_COUNT_THRESHOLD_VAL			35

void Timer0_Configuration(void);
void delay_cnt(uint32_t count);
void delay_ms(uint32_t ms);

void Time_Counter_Configuration(void);
void Time_Counter(void);

void Timer_IRQ_Handler(void);

#endif
