#include "common.h"
#include "bsp_init.h"

ErrorStatus RCM_ClockConfig(void)
{
	
	   /* RCM NVIC Config */

   NVIC_EnableIRQRequest(RCM_IRQn,0,0);

   RCM_Reset();
   RCM_ConfigHSE(RCM_HSE_OPEN);

   while(RCM_WaitHSEReady()!= SUCCESS);
   
        FMC_EnablePrefetchBuffer();
        FMC_ConfigLatency(FMC_LATENCY_2);

         /* AHB Bus Clock */
         RCM_ConfigAHB(RCM_AHB_DIV_1);
        /* APB2 clock : 72Mhz */
        RCM_ConfigAPB2(RCM_APB_DIV_1);
        /* APB1 CLock : 36Mhz */
        RCM_ConfigAPB1(RCM_APB_DIV_2);

         /* HSE 8Mhz * 9 = 72Mhz */
         RCM_ConfigPLL(RCM_PLLSEL_HSE,RCM_PLL2MF_9);


         RCM_EnablePLL();
         while(RCM_ReadStatusFlag(RCM_FLAG_PLLRDY) == RESET);

         RCM_ConfigSYSCLK(RCM_SYSCLK_SEL_PLL);

          while(RCM_ReadSYSCLKSource() != RCM_SYSCLK_SEL_PLL);

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