#include "common.h"
#include "board_test.h"

static void 
dummy_task1(void* args __attribute((unused)) );
static void 
dummy_task2(void* args __attribute((unused)) );


int main()
{
   // LIGTH_TEST();
  //SEGGER_RTT_TEST(); 
 rtt_printf("System Initialization Begin.\n ");

  /* RCC Config */
  if(RCC_ClockConfig() != SUCCESS)
   {
      // Error message here.
      rtt_printf("Systemclock configuration failed.\n");
   }

   SysTick_Init();

   ILI9341V_Init();


    /* LCD Backlight GPIO Init */
    RCC_APB2PeriphClockCmd(LCD_BL_PERIPH_CLK,ENABLE);
    
    GPIO_InitTypeDef io_struct;
    io_struct.GPIO_Pin = LCD_BL_PIN;
    io_struct.GPIO_Mode = GPIO_Mode_Out_PP;
    io_struct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(LCD_BL_PORT,&io_struct);

 rtt_printf("System Initialization End.\n");
	 
    // Stucking Point
//   uint8_t* maclloc_test = malloc(sizeof(uint8_t));
//             delay_ms(1000);

// Enable LCD backlight 
  //GPIO_SetBits(LCD_BL_PORT,LCD_BL_PIN);



  /* Malloc address test */
  /*
   uint8_t* val = (uint8_t*)malloc(sizeof(uint8_t));
   *val = 0xFF;

   rtt_printf("The address of val is %x \n",&val);
   rtt_printf("The address inside of val is %x \n",val);
   rtt_printf("The value of val is %d \n",*val);

   uint8_t* val1 = (uint8_t*)malloc(sizeof(uint8_t));
   *val1 = 0xFF;
   rtt_printf("The address of val1 is %x \n",&val1);
   rtt_printf("The address inside of val is %x \n",val1);
   rtt_printf("The value of val1 is %d \n",*val1);

   rtt_printf("\n");

   free(val1);
   rtt_printf("val1 freed\n");
   uint8_t* val2 = (uint8_t*)malloc(sizeof(uint8_t));
   *val2 = 0xFF;
   rtt_printf("The address of val2 is %x \n",&val2);
   rtt_printf("The address inside of val2 is %x \n",val2);
   rtt_printf("The value of val2 is %d \n",*val2);
   rtt_printf("size of val2 is %d , %d , %d \n",sizeof(&val1),sizeof(val1),sizeof(*val1));

   */



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

  volatile uint16_t test_temp=0;

  uint8_t* maclloc_test = malloc(sizeof(uint8_t));

         while (1)
         {
            //rtt_print("Testing ILI9341 LCD.\n ");

            __ili9341v_write(0x51,1,0xF2);
            test_temp = __ili9341v_read_single(0x52);
            rtt_printf("memroy content %x \n",(uint8_t)test_temp&0x00FF);

            test_temp = __ili9341v_read_single(0xDA);
            rtt_printf("manufacture ID : %x\n",(uint8_t)test_temp&0x00FF);

            test_temp = __ili9341v_read_single(0xDB);
            rtt_printf("version ID : %x\n",(uint8_t)test_temp&0x00FF);

            test_temp = __ili9341v_read_single(0xDC);
            rtt_printf("module ID : %x\n",(uint8_t)test_temp&0x00FF);
            delay_ms(1000);

            // disp_id_infos info = ILI9341V_ReadDisplayIDInfos();
            // rtt_printf("Display module id : %x \n  \
            //             Display module version id %x \n \
            //             Display module manufacture id %x\n", \
            //             info.id, \
            //             info.id_version, \
            //             info.id_manufacture);

            rtt_printf("done.\n");
            delay_ms(1000);

         }

}


static void 
dummy_task2(void* args __attribute((unused)) )
{

      while(1)
      {

         rtt_printf("This is in dummy_task2.\n");
         delay_ms(2000);
      }


}