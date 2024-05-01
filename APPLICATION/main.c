#include <stdlib.h>
#include <stdio.h>
#include "common.h"
//#include <stdio.h>
#include "test.h"

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

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
// int fputc(int ch, FILE *f)
// {
//  /* Place your implementation of fputc here */
//  /* e.g. write a character to the USART */
//  USART_SendData(USART1, (uint8_t) ch);

//  /* Loop until the end of transmission */
//  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
//  {}

//  return ch;
// }

int main()
{
  
// rtt_printf("System Initialization Begin.\n ");

  /* RCC Config */
if (RCC_ClockConfig() != SUCCESS)
   HardFault_Handler();

RCC_PeriphClock_Init();

SysTick_Init();

 USER_DMA_Init();

 USER_GPIO_Init();

 USER_ADC_Init();

 USER_USART_Init();

//rtt_printf("System Initialization End.\n");

// SWO_PrintString("Test printing\n");

   delay_ms(62);
  LCD_Init();
  English_Font_test();

  
//
 rtt_printf("test\n");

   

	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);



	// GPIO_InitTypeDef gpio_init = {0};
	// gpio_init.GPIO_Mode = GPIO_Mode_Out_OD;
	// gpio_init.GPIO_Pin = GPIO_Pin_8;
	// gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

	// GPIO_Init(GPIOA, &gpio_init);

	// GPIO_ResetBits(GPIOA,GPIO_Pin_8);

	// gpio_init.GPIO_Mode = GPIO_Mode_Out_OD;
	// gpio_init.GPIO_Pin = GPIO_Pin_2;
	// gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

	// GPIO_Init(GPIOD, &gpio_init);
	// GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	

   


   while(1)
   {

  /* blinky */
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	delay_ms(100);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	delay_ms(100);



  //  USART_SendData(USART1,'X');
  // /* Loop until the end of transmission */
  // while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

//   delay_ms(500);
 
   }
	 

}




