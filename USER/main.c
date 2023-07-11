#include "common.h"

static void 
dummy_task1(void* args __attribute((unused)) );
static void 
dummy_task2(void* args __attribute((unused)) );


int main()
{
  
 rtt_printf("System Initialization Begin.\n ");

  /* RCC Config */
  if(RCC_ClockConfig() != SUCCESS)
   {
      // Error message here.
      rtt_printf("Systemclock configuration failed.\n");
   }

   SysTick_Init();



 rtt_printf("System Initialization End.\n");
	 


  /******
   * 
   *  FreeRTOS Initializations
   * 
   */


   xTaskCreate(dummy_task1,"dummy taks1",configMINIMAL_STACK_SIZE*5,NULL,tskIDLE_PRIORITY,NULL);
   xTaskCreate(dummy_task2,"dummy taks2",configMINIMAL_STACK_SIZE*5,NULL,tskIDLE_PRIORITY,NULL);

   vTaskStartScheduler();

      for(;;);
  



}


static void 
dummy_task1(void* args __attribute((unused)) )
{


  const char* malloc_test = malloc(sizeof(uint8_t)*256);
  malloc_test = "This is dummy_task1.\n";
  

         while (1)
         {

            rtt_printf(malloc_test);
            delay_ms(2000);
         }

}

static void 
dummy_task2(void* args __attribute((unused)) )
{


  const char* malloc_test = malloc(sizeof(uint8_t)*256);
  malloc_test = "This is dummy_task2.\n";
  

         while (1)
         {

            rtt_printf(malloc_test);
            delay_ms(2000);
         }

}

