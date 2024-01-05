#ifndef BSP_INIT_H
#define BSP_INIT_H

#define ADC1_DR_Address    ((uint32_t)0x4001244C)

ErrorStatus RCC_ClockConfig(void);

void RCC_PeriphClock_Init(void);

void SysTick_Init(void);

void USER_DMA_Init(void);

void USER_ADC_Init(void);

void ADC1_2_IRQHandler(void);

#endif

