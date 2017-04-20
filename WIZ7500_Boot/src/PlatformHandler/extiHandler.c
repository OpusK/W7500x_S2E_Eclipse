
#include "common.h"
#include "extiHandler.h"

extern uint8_t factory_flag;

//void EXTI_Handler(void)
void Exti_IRQ_Handler(void)
{
	factory_flag = 1;

#if defined(ENABLE_ESINT)
	g_active_es = 1;

	if(GPIO_ReadInputDataBit(ES1_GPIO_PORT, ES1_PIN) == Bit_SET)
		g_active_es_pin = ES1_PIN;
	else if(GPIO_ReadInputDataBit(ES1_GPIO_PORT, ES2_PIN) == Bit_SET)
		g_active_es_pin = ES2_PIN;
	else if(GPIO_ReadInputDataBit(ES0_GPIO_PORT, ES0_PIN) == Bit_SET)
		g_active_es_pin = ES0_PIN;
#endif

	NVIC_DisableIRQ(EXTI_IRQn);
}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void EXTI_Configuration(void)
{
    NVIC_ClearPendingIRQ(EXTI_IRQn); // Pending bit Clear
    NVIC_EnableIRQ(EXTI_IRQn);       // EXTI Interrupt Enable
}
