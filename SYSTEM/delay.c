
/**************************************************************************************************/			
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/		
#include "common.h"
#include "delay.h"
static volatile u8  fac_us=0;
static volatile u32 fac_ms=0;
void delay_init(void)
{
	fac_us = SystemCoreClock/1000000;
	fac_ms = SystemCoreClock/1000;

}								    
void delay_ms(u32 nms)
{	 		  	  
	volatile u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;           
	SysTick->CTRL|= 0x01 ;        
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL &= 0x10006;       
	SysTick->VAL =0X00;       
}   
void delay_us(u32 nus)
{		
	volatile u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 
	SysTick->VAL=0x00;        
	SysTick->CTRL |= 0x01 ;      
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL &= 0x10006;  
	SysTick->VAL =0X00;      
}


