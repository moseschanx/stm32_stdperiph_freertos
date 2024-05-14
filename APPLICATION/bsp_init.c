#include "common.h"
#include "bsp_init.h"

__IO uint16_t ADCConvertedValue[8] = {0,1,2,3,4,5,6,7};

static ADC_InitTypeDef ADC_InitStructure = {0};
static DMA_InitTypeDef DMA_InitStructure = {0};
static GPIO_InitTypeDef GPIO_InitStructure ={0};
static NVIC_InitTypeDef NVIC_InitStructure = {0};
static USART_InitTypeDef USART_InitStructure = {0};

ErrorStatus RCC_ClockConfig(void)
{
	
	   /* RCC NVIC Config */
   NVIC_InitStructure.NVIC_IRQChannel = RCC_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   RCC_DeInit();
   RCC_HSEConfig(RCC_HSE_ON);

   while(RCC_WaitForHSEStartUp()!= SUCCESS){}
   
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        /* Due to manual range specifies */
        FLASH_SetLatency(FLASH_Latency_2);

         /* AHB Bus Clock */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        /* APB2 clock : 72Mhz */
        RCC_PCLK2Config(RCC_HCLK_Div1);
        /* APB1 CLock : 36Mhz */
        RCC_PCLK1Config(RCC_HCLK_Div2);

         /* HSE 8Mhz * 9 = 72Mhz */
         RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);

         RCC_PLLCmd(ENABLE);

         RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

         /* 0x08: PLL used as system clock */
         while(RCC_GetSYSCLKSource() != 0x08);

    return SUCCESS;
   
}

void RCC_PeriphClock_Init(void)
{

   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);        // Enable DMA1 Clock
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);      // Enable ADC1 Clock
   RCC_ADCCLKConfig(RCC_PCLK2_Div6);                        // Set ADC Clock Speed to : 12Mhz

   /* To use USART1 */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

}



void SysTick_Init(void)
{
  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }

}

void USER_GPIO_Init(void)
{

/* ADC Analog input pins */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = ADC_CO_OP_BIAS_Channel | ADC_CO_OP_AMP_OUT_Channel |  \
                                ADC_H2_OP_BIAS_Channel | ADC_H2_OP_AMP_OUT_Channel | \
                                ADC_WINSEN_TO_VOC_Channel | ADC_SMOKE_Channel ; 

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA,&GPIO_InitStructure);

  /* Sensor Test pins */
  GPIO_InitStructure.GPIO_Pin = CO_SENSOR_TEST_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(CO_SENSOR_TEST_GPIO_Port,&GPIO_InitStructure);
  GPIO_ResetBits(CO_SENSOR_TEST_GPIO_Port,CO_SENSOR_TEST_Pin);

  GPIO_InitStructure.GPIO_Pin = H2_SENSOR_TEST_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(H2_SENSOR_TEST_GPIO_Port,&GPIO_InitStructure);
  GPIO_ResetBits(H2_SENSOR_TEST_GPIO_Port,H2_SENSOR_TEST_Pin);

  /* USART1 Pins */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // USART1 Tx pin
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  GPIO_ResetBits(GPIOA,GPIO_Pin_9);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // USART1 Rx pin
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  GPIO_ResetBits(GPIOA,GPIO_Pin_10);

  // //GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);

  // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // USART2 Tx pin
  // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // GPIO_Init(GPIOA,&GPIO_InitStructure);
  // GPIO_ResetBits(GPIOA,GPIO_Pin_9);


  // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; // USART2 Rx pin
  // GPIO_Init(GPIOA,&GPIO_InitStructure);
  // GPIO_ResetBits(GPIOA,GPIO_Pin_10);
  // GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);



}

void USER_ADC_Init(void)
{

  ADC_TempSensorVrefintCmd(ENABLE);
  
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 8;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_17, 2, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_CO_OP_BIAS_Channel, 3, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_CO_OP_AMP_OUT_Channel, 4, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_H2_OP_BIAS_Channel, 5, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_H2_OP_AMP_OUT_Channel, 6, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_WINSEN_TO_VOC_Channel, 7, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_SMOKE_Channel, 8, ADC_SampleTime_239Cycles5);


  ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);


  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  
}

void USER_DMA_Init(void)
{


 /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 8;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);

  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);

}

void USER_USART_Init(void)
{

  /* USART1 Init */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

  USART_Init(USART1,&USART_InitStructure);
  USART_Cmd(USART1,ENABLE);
  

}
