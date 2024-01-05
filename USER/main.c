#include "common.h"





int main()
{
  
 rtt_printf("System Initialization Begin.\n ");

  /* RCC Config */
  if(RCC_ClockConfig() != SUCCESS)
      HardFault_Handler();

   RCC_PeriphClock_Init();

   SysTick_Init();

   USER_DMA_Init();
   
   USER_ADC_Init();


 rtt_printf("System Initialization End.\n");

 SWO_PrintString("Test printing\n");
 

   while(1)
   {

   rtt_printf("Junction Temp : %d\tVref Bandgap :%d\n",ADCConvertedValue[0],ADCConvertedValue[1]);
   delay_ms(500);
 
   }
	 

}




