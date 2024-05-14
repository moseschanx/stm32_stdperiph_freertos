
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
#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
//����delay_us,delay_ms
//V1.2�޸�˵��
//�������ж��е��ó�����ѭ���Ĵ���
//��ֹ��ʱ��׼ȷ,����do while�ṹ!
//////////////////////////////////////////////////////////////////////////////////	 
void delay_init();
void delay_ms(u32 nms);
void delay_us(u32 nus);

#endif





























