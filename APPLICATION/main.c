#include <stdlib.h>
#include <stdio.h>
#include "common.h"
//#include <stdio.h>
#include "test.h"
#include "sgl.h"

void uart_print(char* str, ...);


#ifndef dbg_printf(str,...)
#ifdef USE_SEGGER_RTT
#define dbg_printf(str,...) rtt_printf(fmt,__VA__ARGS__)
#else 
#define dbg_printf(str,...) uart_printf(fmt,__VA__ARGS__)
#endif
#endif


/* Memroy management function definitions */
void* memcpy(void *dst, const void *src, uint32_t size) {
    char *d = (char*) dst;
    const char *s = (const char*) src;

    for (int i = 0; i < size; ++i) {
        *d++ = *s++;
    }

    return dst;
}
void* memset(void *dst, int val, unsigned size) {
    uint8_t *byte_dst = (uint8_t*) dst; // Cast to uint8_t* for byte-level access

    for (unsigned i = 0; i < size; ++i) {
        byte_dst[i] = (uint8_t) val; // Assign the value to each byte, casting to uint8_t to ensure it's within range
    }

    return dst; // Return the destination pointer
}
uint32_t strlen(char *str)
{
  uint32_t len = 0;
  while(str[len] != '\0')
  {
    len++;
  }
  return len;
}


void MCU_Init(void)
{
  
 rtt_printf("System Initialization Begin.\n ");

  /* RCC Config */
if (RCC_ClockConfig() != SUCCESS)
   HardFault_Handler();

RCC_PeriphClock_Init();

SysTick_Init();

 USER_DMA_Init();

 USER_GPIO_Init();

 USER_ADC_Init();

 USER_USART_Init();

rtt_printf("System Initialization End.\n");

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

 void tft_show_window(int16_t x1, int16_t y1, int16_t x2, int16_t y2, const sgl_color_t *src)
 {
    LCD_Fill(x1, y1, x2, y2, src);
 }


int stdout_device(char *str)
{
    //return rtt_printf("%s\n", str);
    uart_print(str);
}


int main()
{
  
  MCU_Init();
  //delay_ms(62);
  LCD_Init();
  //English_Font_test();
//  Touch_Test();

  

  //English_Font_test();


   while(1)
   {

  /* blinky */
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	delay_ms(10);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	delay_ms(10);

  // uart_print("Program main loop!\n");

  // rtt_printf("Program main loop!\n");


  /* USART Test */
  //  USART_SendData(USART1,'X');
  // /* Loop until the end of transmission */
  // while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
 
   }
	 

}

void uart_print(char* str,...)
{

  va_list ParamList;

    while(*str!='\0')
    {
      USART_SendData(USART1,*str++);
      while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
    }

  va_end(ParamList);


}




