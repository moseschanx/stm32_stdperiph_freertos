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

   USER_GPIO_Init();
   
   USER_ADC_Init();


 rtt_printf("System Initialization End.\n");

 SWO_PrintString("Test printing\n");
 

   while(1)
   {

   rtt_printf("Junction Temp : %d\tVref Bandgap :%d\n",ADCConvertedValue[0],ADCConvertedValue[1]);
   rtt_printf("CO_BIAS : %d\tCO : %d\tH2_BIAS : %d\t H2 : %d\n",ADCConvertedValue[2],ADCConvertedValue[3],\
                                                              ADCConvertedValue[4],ADCConvertedValue[5]\
                                                              );
   rtt_printf("VOC : %d\tSMOKE : %d\n\n",ADCConvertedValue[6],ADCConvertedValue[7]);
   delay_ms(500);
 
   }
	 

}




