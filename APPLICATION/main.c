#include "common.h"

void uart_printf(char* str, ...);


void MCU_Init(void)
{
  
// dbg_printf("System Initialization Begin.\n ");   // This line must be commented out before USRAT Initialized.

  /* RCC Config */
if (RCC_ClockConfig() != SUCCESS)
   HardFault_Handler();

RCC_PeriphClock_Init();

  SysTick_Init();
  delay_init();

// USER_DMA_Init();

 USER_GPIO_Init();

 //USER_ADC_Init();

 USER_USART_Init();

dbg_printf("System Initialization End.\n");

// SWO_PrintString("Test printing\n");


  


   
  /* blinky subroutine hardware prepare */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);



	  GPIO_InitTypeDef gpio_init = {0};
	  gpio_init.GPIO_Mode = GPIO_Mode_Out_OD;
	  gpio_init.GPIO_Pin = GPIO_Pin_8;
	  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

	  GPIO_Init(GPIOA, &gpio_init);

	  GPIO_ResetBits(GPIOA,GPIO_Pin_8);

	  gpio_init.GPIO_Mode = GPIO_Mode_Out_OD;
	  gpio_init.GPIO_Pin = GPIO_Pin_2;
	  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

	  GPIO_Init(GPIOD, &gpio_init);
	  GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	

   
  
} 



// int stdout_device(char *str) {
//     //return rtt_printf("%s\n", str);
//     uart_printf(str);
// }


int main()
{
  
  MCU_Init();
  //delay_ms(62);

  
//  English_Font_test();
 // Touch_Test();
  sgl_main();


  
  
  

  //English_Font_test();


   while(1)
   {

  //Touch_Test();
        sgl_tick_inc(5);
        sgl_task_handler();

  /* blinky */
	// GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	// delay_ms(200);
	// GPIO_SetBits(GPIOA,GPIO_Pin_8);
	// delay_ms(200);

  // dbg_printf("Program main loop!\n");
  // uart_print("Program main loop!\n");

  // rtt_printf("Program main loop!\n");


  /* USART Test */
  //  USART_SendData(USART1,'X');
  // /* Loop until the end of transmission */
  // while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
 
   }
	 

}

void uart_printf(char* str,...)
{

  va_list ParamList;

    while(*str!='\0')
    {
      while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET); // If dont wait TXE, The first character might not sent through.
      USART_SendData(USART1,*str++);
      while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
    }

  va_end(ParamList);


}




