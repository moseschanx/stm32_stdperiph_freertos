#include "common.h"

#define DEBUG_UART USART1
void uart_printstr(uint8_t* str)
{
    while(*str!='\0')
    {
      while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET); // If dont wait TXE, The first character might not sent through.
      USART_SendData(DEBUG_UART,*str++);
      while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
    }
}

void uart_printchar(uint8_t c)
{
  while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
  USART_SendData(DEBUG_UART,c);
  while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
}

void uart_printf(uint8_t* fmt , ...)
{

  char* str[100] = {0};
  va_list ParamList;
  va_start(ParamList, fmt);

  while(*fmt != '\0')
  {
    if(*fmt == '%')
    {
      fmt++;
      switch((uint8_t)*fmt++)
      {
        case 'c':
          uart_printchar((uint8_t)va_arg(ParamList, int));
          break;
        case 'd':
          itos((uint32_t)va_arg(ParamList, int),str);
          uart_printstr(str);
          break;
        case 's':
          uart_printstr((uint8_t*)va_arg(ParamList, int));
      }
  }
  else
  {
      uart_printchar(*fmt++);
  }
}

}

/* Maximum decimal numbers to print (10 digits): 4294967295 */
void itos(uint32_t num, uint8_t *str)
{
  uint32_t i = 0;
  while(num)
  {
   *(str+i++) = (uint8_t)(num % 10 + '0'); 
    num /= 10;
  }
  str_reverse(str, i);
}

void str_reverse(uint8_t *str, uint32_t len)
{
  uint8_t i = 0 , j = 0 , temp = 0;
  i = len-- / 2;
  while(i-- != 0)
  temp = *(str+j) , *(str+j++) = *(str+len) , *(str+len--) = temp;
}