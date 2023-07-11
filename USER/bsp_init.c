#include "common.h"
#include "bsp_init.h"

ErrorStatus RCC_ClockConfig(void)
{
	
	   /* RCC NVIC Config */
   NVIC_InitTypeDef NVIC_InitStructure;
   NVIC_InitStructure.NVIC_IRQChannel = RCC_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   RCC_DeInit();
   RCC_HSEConfig(RCC_HSE_ON);

   while(RCC_WaitForHSEStartUp()!= SUCCESS);
   
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



void SysTick_Init(void)
{
  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }

}
