//////////////////////////////////////////////////////////////////////////////////	 
//???????????????δ????????????????????????κ????
//??????????????STM32F103RCT6,???????MiniSTM32??????,???72MHZ??????12MHZ
//QDtech-TFT??????? for STM32 IO???
//xiao??@ShenZhen QDtech co.,LTD
//??????:www.qdtft.com
//????????http://qdtech.taobao.com
//wiki?????????http://www.lcdwiki.com
//??????????????κμ?????????????????
//???(????) :+86 0755-23594567 
//???:15989313508?????? 
//????:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//???????QQ:3002773612  3002778157
//????????QQ?:324828016
//????????:2018/08/09
//?汾??V1.0
//??????У?????????
//Copyright(C) ?????????????????????? 2018-2028
//All rights reserved
/****************************************************************************************************
//?????????????????????MiniSTM32??????TFTLCD???????????????
//STM32???????????TFTLCD???????????????STM32????
//=========================================???????================================================//
//     LCD???             TFTLCD???????        STM32????????
//      VDD       --->         5V/3.3              DC5V/3.3V          //???
//      GND       --->          GND                  GND              //?????
//=======================================??????????????==========================================//
//?????????????????????16λ?????????8λ??????8λ????????DB8~DB15??D8~D15?? 
//     LCD???             TFTLCD???????        STM32????????
//     DB0~DB15   --->         D0~D15               PB0~PB15          //?????16λ???????????
//=======================================??????????????==========================================//
//     LCD??? 				     TFTLCD???????        STM32???????? 
//       WR       --->          WR                   PC7             //?????д??????????
//       RD       --->          RD                   PC6             //?????????????????
//       RS       --->          RS                   PC8             //?????????/??????????
//       RST      --->          RST                  PC4             //???????λ???????
//       CS       --->          CS                   PC9             //??????????????
//       BL       --->          BL                   PC10            //???????????????
//=========================================????????????=========================================//
//?????鲻???????????????д?????????????????????????????????д?????????
//	   LCD???             TFTLCD???????        STM32???????? 
//      PEN       --->          PEN                  PC1             //???????????ж????
//      MISO      --->          MISO                 PC2             //??????SPI????????
//      MOSI      --->          MOSI                 PC3             //??????SPI????д???
//      T_CS      --->          TCS                  PC13            //???????????????
//      CLK       --->          CLK                  PC0             //??????SPI??????????
**************************************************************************************************/			
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
static volatile u8  fac_us=0;//us?????????
static volatile u32 fac_ms=0;//ms?????????
//???????????
//SYSTICK????????HCLK????1/8
//SYSCLK:?????
void delay_init(void)
{
//	SysTick->CTRL&=0xfffffffb;//bit2???,????????  HCLK/8
	 // SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//????????  HCLK/8
	// fac_us=SYSCLK/8;		    
	// fac_ms=(u16)fac_us*1000;
	fac_us = SystemCoreClock/1000000;
	fac_ms = SystemCoreClock/1000;

}								    
//???nms
//???nms???Χ
//SysTick->LOAD?24λ?????,????,???????:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK??λ?Hz,nms??λ?ms
//??72M??????,nms<=1864 
void delay_ms(u32 nms)
{	 		  	  
	volatile u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//??????(SysTick->LOAD?24bit)
	SysTick->VAL =0x00;           //????????
	SysTick->CTRL|= 0x01 ;          //???????  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//????????   
	SysTick->CTRL &= 0x10006;       //????????
	SysTick->VAL =0X00;       //????????	  	    
}   
//???nus
//nus???????us??.		    								   
void delay_us(u32 nus)
{		
	volatile u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //??????	  		 
	SysTick->VAL=0x00;        //????????
	SysTick->CTRL |= 0x01 ;      //??????? 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//????????   
	SysTick->CTRL &= 0x10006;       //????????
	SysTick->VAL =0X00;       //????????	 
}




































