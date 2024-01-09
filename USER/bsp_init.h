#ifndef BSP_INIT_H
#define BSP_INIT_H

#define ADC1_DR_Address    ((uint32_t)0x4001244C)


#define CO_SENSOR_TEST_Pin GPIO_Pin_0
#define CO_SENSOR_TEST_GPIO_Port GPIOA

#define ADC_CO_OP_BIAS_Pin GPIO_Pin_1
#define ADC_CO_OP_BIAS_GPIO_Port GPIOA
#define ADC_CO_OP_BIAS_Channel  ADC_Channel_1

#define ADC_CO_OP_AMP_OUT_Pin GPIO_Pin_2
#define ADC_CO_OP_AMP_OUT_GPIO_Port GPIOA
#define ADC_CO_OP_AMP_OUT_Channel ADC_Channel_2


#define ADC_WINSEN_TO_VOC_Pin GPIO_Pin_4
#define ADC_WINSEN_TO_VOC_GPIO_Port GPIOA
#define ADC_WINSEN_TO_VOC_Channel ADC_Channel_4


#define ADC_SMOKE_Pin GPIO_Pin_5 
#define ADC_SMOKE_GPIO_Port GPIOA
#define ADC_SMOKE_Channel ADC_Channel_5

#define ADC_H2_OP_BIAS_Pin GPIO_Pin_6 
#define ADC_H2_OP_BIAS_GPIO_Port GPIOA
#define ADC_H2_OP_BIAS_Channel ADC_Channel_6


#define ADC_H2_OP_AMP_OUT_Pin GPIO_Pin_7
#define ADC_H2_OP_AMP_OUT_GPIO_Port GPIOA
#define ADC_H2_OP_AMP_OUT_Channel ADC_Channel_7


#define H2_SENSOR_TEST_Pin GPIO_Pin_0 
#define H2_SENSOR_TEST_GPIO_Port GPIOB

#define EXT_DBG_RXD_Pin GPIO_Pin_9
#define EXT_DBG_RXD_GPIO_Port GPIOA

#define EXT_DBG_TXD_Pin GPIO_Pin_10
#define EXT_DBG_TXD_GPIO_Port GPIOA

#define WHT20_SCL_Pin GPIO_Pin_6
#define WHT20_SCL_GPIO_Port GPIOB

#define WHT20_SDA_Pin GPIO_Pin_7
#define WHT20_SDA_GPIO_Port GPIOB

ErrorStatus RCC_ClockConfig(void);

void RCC_PeriphClock_Init(void);

void SysTick_Init(void);

void USER_DMA_Init(void);

void USER_GPIO_Init(void);

void USER_ADC_Init(void);

void ADC1_2_IRQHandler(void);

#endif

