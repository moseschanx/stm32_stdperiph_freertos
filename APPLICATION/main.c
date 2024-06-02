#include "common.h"

void uart_printf(uint8_t* fmt , ...);

#define buffer1_size  sizeof(buffer1)
#define buffer2_size  sizeof(buffer2)

const uint8_t buffer1[] = "Buffer 1 content abcdefg.";
const uint8_t buffer2[] = "Buffer 2 content hijklmn.xx";
uint8_t buffer1_satus, buffer2_satus;

uint8_t rx_buffer1[buffer1_size] = {0};
uint8_t rx_buffer2[buffer2_size] = {0};


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

int main()
{
  
  MCU_Init();
  //delay_ms(62);
// Buffer memory test.
{
// buffer 1 test 
  dbg_printf("buffer1 size : %d\n",buffer1_size);
  for(int i=0;i<buffer1_size;++i)
  {
    rx_buffer1[i] = (uint8_t)('0' + i);
  }
  dbg_printf("rx_buffer1 content :");
  for(int i=0;i<buffer1_size;++i)
  {
    //uart_printchar(rx_buffer1[i]);
    dbg_printf("%c",rx_buffer1[i]);
  }
  dbg_printf("\n");
  
// buffer 2 test
  dbg_printf("buffer2 size : %d\n",buffer2_size);
  for(int i=0;i<buffer2_size;++i)
  {
    rx_buffer2[i] = (uint8_t)('0' + i);
  }
  dbg_printf("rx_buffer2 content :");
  for(int i=0;i<buffer2_size;++i)
  {
   // uart_printchar(rx_buffer2[i]);
   dbg_printf("%c",rx_buffer2[i]);
  }
  dbg_printf("\n");
}


  
//  English_Font_test();
  //LCD_Init();
 // Touch_Test();
 #if USE_SGL
  sgl_main();
#endif

  //English_Font_test();

   uint32_t i = 4294967295;
   while(1)
   {

  //Touch_Test();
#if USE_SGL
        sgl_tick_inc(5);
        sgl_task_handler();
#endif

  /* blinky */
	 GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	 delay_ms(20);
	 GPIO_SetBits(GPIOA,GPIO_Pin_8);
	 delay_ms(20);

   dbg_printf("Program main loop! %d\n",i++);


 
   }

}
