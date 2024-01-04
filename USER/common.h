#ifndef COMMON_H
#define COMMON_H

/* Common include files */
#include "SWO.h"
#include "apm32f10x.h"
#include "apm32f10x_conf.h"
#include "bsp_init.h"
#include "SEGGER_RTT.h"

/* 3rd Party Lib Support */
#include "ftos.h"

/* Driver include files */


/* Delay function prototypes porting */
#if defined(FREERTOS_CONFIG_H) && !defined(USE_PRIMITIVES)
#define delay_ms(ms) vTaskDelay((TickType_t)ms);
#else
void delay_ms(__IO uint32_t nTime);
#endif


/**** TODOs : Implement more useful macro portings here , especially with colors ****/

/* SEGGER RTT Printf */ 
/* 
    Problems : rtt_printf can not accept single arugment invocation , need physical porting.
*/
#ifdef DEBUG 
#define rtt_printf(fmt , ...)  SEGGER_RTT_printf(0 , fmt , ##__VA_ARGS__) 
#else
#define rtt_printf(fmt , ...)  
#endif

/* Memroy management function prototypes porting */
#define  malloc(size) pvPortMalloc(size)
#define  calloc(size) pvPortCalloc(size)
#define  free(pv)   vPortFree(pv)


/* Get current SysTick Values for counting CPU times. Usage as follows :
   	
    volatile uint32_t tick_begin , tick_end , tick_diff , elapsed_time;

      tick_begin = get_current_sys_tick_value();
        // Measuring code blocks here.
      tick_end = get_current_sys_tick_value(); // takes 33 ticks to execute
      tick_diff = tick_begin - tick_end - 33; 

      rtt_printf("Tick elapsed : %d. \n",tick_diff);
      rtt_printf("Time elapsed %d (us).\n",(tick_diff*14)/1000); // 14 for 13.9ns (1/72000ms)
        

*/
inline uint32_t get_current_sys_tick_value(void) { return (uint32_t) ((SysTick->VAL)&SysTick_VAL_CURRENT_Msk); }


#endif
