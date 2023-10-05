#include "common.h"

static void 
dummy_task1(void* args __attribute((unused)) );
static void 
dummy_task2(void* args __attribute((unused)) );
static void
adc_channel_aquire_sample(void* args __attribute((unused)));
static void
adc_junction_temp_aquire(void* args __attribute((unused)));


int main()
{
  
 rtt_printf("System Initialization Begin.\n ");

  /* RCC Config */
  if(RCC_ClockConfig() != SUCCESS)
   {
      // Error message here.
      rtt_printf("Systemclock configuration failed.\n");
   }

   SysTick_Init();



 rtt_printf("System Initialization End.\n");

 SWO_PrintString("Test printing\n");
	 


  /******
   * 
   *  FreeRTOS Initializations
   * 
   */


//   xTaskCreate(dummy_task1,"dummy taks1",configMINIMAL_STACK_SIZE*5,NULL,tskIDLE_PRIORITY,NULL);
//   xTaskCreate(dummy_task2,"dummy taks2",configMINIMAL_STACK_SIZE*5,NULL,tskIDLE_PRIORITY,NULL);
//   xTaskCreate(adc_channel_aquire_sample,"adc_inner_task",configMINIMAL_STACK_SIZE*5,NULL,tskIDLE_PRIORITY,NULL);
   xTaskCreate(adc_junction_temp_aquire,"junction_temp",configMINIMAL_STACK_SIZE*5,NULL,tskIDLE_PRIORITY,NULL);


   vTaskStartScheduler();

      for(;;);
  



}


static void 
dummy_task1(void* args __attribute((unused)) )
{


  const char* malloc_test = malloc(sizeof(uint8_t)*256);
  malloc_test = "This is dummy_task1.\n";
  

         while (1)
         {

            rtt_printf(malloc_test);
            SWO_PrintString(malloc_test);
            delay_ms(2000);
         }

}

static void 
dummy_task2(void* args __attribute((unused)) )
{


  const char* malloc_test = malloc(sizeof(uint8_t)*256);
  malloc_test = "This is dummy_task2.\n";
  

         while (1)
         {

            rtt_printf(malloc_test);
            SWO_PrintString(malloc_test);
            delay_ms(2000);
         }

}

static void
adc_channel_aquire_sample(void* args __attribute((unused)))
{
   RCC_ADCCLKConfig(RCC_PCLK2_Div8);  
  /* Enable ADC1 and GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PC.00 (ADC1 Channel10) as analog input -------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  ADC_InitTypeDef ADC_InitStructure;

    /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);

  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

      rtt_printf("INNER ADC AQUIRING : ADC0 Software Conversion Started\n");


   for(;;)
   {
   static uint16_t val = 0;
   val =  ADC_GetConversionValue(ADC1);
      rtt_printf("adc_channel_aquire_sample : %d\n",val);
         delay_ms(200);

  }


}

static void
adc_junction_temp_aquire(void* args __attribute((unused)))
{
   RCC_ADCCLKConfig(RCC_PCLK2_Div8);  
  /* Enable ADC1 and GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);

  ADC_InitTypeDef ADC_InitStructure;

    /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 16;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);

  ADC_TempSensorVrefintCmd(ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);



   for(;;)
   {
   static uint16_t val = 0;
   val =  ADC_GetConversionValue(ADC1);
      rtt_printf("JUNCTION TEMP AQUIRE: %d \n",val);
         delay_ms(500);

  }


}
