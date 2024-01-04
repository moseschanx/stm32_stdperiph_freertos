#include "common.h"



int main()
{
  
 rtt_printf("System Initialization Begin.\n ");

  /* RCC Config */
  if(RCM_ClockConfig() != SUCCESS)
   {
      // Error message here.
      rtt_printf("Systemclock configuration failed.\n");
   }
   RCM_EnableCSS(); //Clock security system


   SysTick_Init();



 rtt_printf("System Initialization End.\n");

 SWO_PrintString("Test printing\n");


   while(1)
   {

   rtt_printf("Hello,APM32\n"); 
 
   delay_ms(500);
   }
	 



}
