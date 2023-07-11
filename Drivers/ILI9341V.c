#include "common.h"
   /* Timing notes : 
    For Cortex-m3 MCU at 72Mhz Clock freq. , nop instruction takes 1 cycle of cpu time ,
    which is 13.9 ns.

    This driver is currently developed under the 72Mhz clock freq. condition.
    Other CPU freq. might not work properly.
   */

/// @brief ILI9341V Low level Write , according to the datasheet timing diagram.
/// @param dat 
void __ili9341v_command_write_ll(uint8_t dat)
{
   LCD_RS_L();
   LCD_WR_L();
   // Write data to D[7:0]
   GPIO_Write(LCD_DB_PORT,(uint16_t)0x00FF&dat);
   __NOP(); __NOP(); // Write Control pluse L duration minimum 15ns
   LCD_WR_H();
   LCD_RS_H();

}
/// @brief This function can only invoked after ILI9341_Command_Write_LL due to Timing Continuity.
/// @param dat 
void __ili9341v_parameter_write_ll(uint16_t dat)
{
   LCD_WR_L();
   // Write data to D[15:0]
   GPIO_Write(LCD_DB_PORT,dat);
   __NOP(); __NOP(); // Write Control pluse L duration minimum 15ns
   LCD_WR_H();

}

/// @brief ILI9341V Register Write.
/// @param command 8-bit long command hex.
/// @param param_size How many parameters would be write.
/// @param ... Parameters being write to ILI9341V.
void __ili9341v_write(uint8_t command , uint8_t param_size , ...)
{
   va_list args;

   LCD_CS_L();
   __ili9341v_command_write_ll(command);
   va_start(args,param_size);

   for(int i=0; i<param_size; ++i)
      __ili9341v_parameter_write_ll(va_arg(args,int)); //int for supress warning

   va_end(args);

   __NOP();
   LCD_CS_H();
   
}


uint16_t __ili9341v_read_single(uint8_t command)
{
   GPIO_InitTypeDef io_struct;
  volatile uint16_t read_temp = 0;

   /* Set DB port as input for reading action */ {
   io_struct.GPIO_Pin = LCD_D0_PIN | LCD_D1_PIN | LCD_D2_PIN | LCD_D3_PIN | LCD_D4_PIN |
                        LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN | LCD_D8_PIN | LCD_D9_PIN |
                        LCD_D10_PIN | LCD_D11_PIN | LCD_D12_PIN | LCD_D13_PIN | LCD_D14_PIN |
                        LCD_D15_PIN;
   io_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(LCD_DB_PORT,&io_struct);
   }

   LCD_CS_L();
   // Write command for reading 
   LCD_RS_L();
   LCD_WR_L();
   __ili9341v_write((uint16_t)command,0);
   __NOP(); __NOP(); // Write Control pluse L duration minimum 15ns
   LCD_WR_H(); 
   LCD_RS_H();
   __NOP(); __NOP(); // Write Control pluse H duration minimum 15ns

   // First time read dummy data
   LCD_RD_L();
   __NOP(); __NOP(); __NOP();__NOP();  // Read Control pulse L duration minimum 45ns
   LCD_RD_H();
   read_temp = GPIO_ReadInputData(LCD_DB_PORT); // Dummy data 

   __NOP(); __NOP(); __NOP();__NOP(); __NOP();__NOP();__NOP(); // Read Control pulse H duration minimum 90ns

   // Second time read valid data 
   LCD_RD_L();
   __NOP(); __NOP(); __NOP();__NOP();  
   LCD_RD_H();
   read_temp = GPIO_ReadInputData(LCD_DB_PORT); // Valid data 

   /* Recover DB port to output mode after read action */ {
   io_struct.GPIO_Pin = LCD_D0_PIN | LCD_D1_PIN | LCD_D2_PIN | LCD_D3_PIN | LCD_D4_PIN |
                        LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN | LCD_D8_PIN | LCD_D9_PIN |
                        LCD_D10_PIN | LCD_D11_PIN | LCD_D12_PIN | LCD_D13_PIN | LCD_D14_PIN |
                        LCD_D15_PIN;
   io_struct.GPIO_Mode = GPIO_Mode_Out_PP;
   io_struct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(LCD_DB_PORT,&io_struct);
   }

   return read_temp;

}
/// @brief ILI9341V low level read 
/// @param command read command instruction code.
/// @param param_size  return parameters.
/// @return pointer to a specific memroy region allocated on heap 
//  @todo  remember to release the memroy in the outer level read functions.
uint16_t* __ili9341v_read_ll(uint8_t command, uint8_t param_size)  
{
   GPIO_InitTypeDef io_struct;
   uint16_t* read_temp = (uint16_t*)malloc(sizeof(uint16_t)*param_size);

   /* Set DB port as input for reading action */ {
   io_struct.GPIO_Pin = 0xFFFF;
   io_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(LCD_DB_PORT,&io_struct);
   }

   LCD_CS_L();
   // Write command for reading 
   LCD_RS_L();
   LCD_WR_L();
   __ili9341v_write((uint16_t)command,0);
   __NOP(); __NOP(); // Write Control pluse L duration minimum 15ns
   LCD_WR_H(); 
   LCD_RS_H();
   __NOP(); __NOP(); // Write Control pluse H duration minimum 15ns

   // First time read dummy data
   LCD_RD_L();
   __NOP(); __NOP(); __NOP();__NOP();  // Read Control pulse L duration minimum 45ns
   LCD_RD_H();
   *read_temp = GPIO_ReadInputData(LCD_DB_PORT); // Dummy data 

   while(--param_size)
   {
       __NOP(); __NOP(); __NOP();__NOP(); __NOP();__NOP();__NOP(); // Read Control pulse H duration minimum 90ns

      // nth time read valid data 
      LCD_RD_L();
      __NOP(); __NOP(); __NOP();__NOP();  
      LCD_RD_H();
      *(read_temp++) = GPIO_ReadInputData(LCD_DB_PORT); // Valid data 
   }
  

   /* Recover DB port to output mode after read action */ {
   io_struct.GPIO_Pin = 0xFFFF;
   io_struct.GPIO_Mode = GPIO_Mode_Out_PP;
   io_struct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(LCD_DB_PORT,&io_struct);
   }

   return read_temp;

}
/// @brief Read display identification information
/// @return Structure that describes the dispay identification info data.
disp_id_infos ILI9341V_ReadDisplayIDInfos(void){

   disp_id_infos infos = {0};
   uint16_t* infos_raw;
   infos_raw = __ili9341v_read_ll(0x04,3);
   infos.id_manufacture = *infos_raw++;
   infos.id_version = *infos_raw++;
   infos.id = *infos_raw;
   free(infos_raw);

   return infos;

}


void ILI9341V_GPIO_Init(void)
{

   RCC_APB2PeriphClockCmd(LCD_BL_PERIPH_CLK,ENABLE);
   RCC_APB2PeriphClockCmd(LCD_CTRL_PERIPH_CLK,ENABLE);
   RCC_APB2PeriphClockCmd(LCD_DB_PERIPH_CLK,ENABLE);

   GPIO_InitTypeDef io_struct;
   io_struct.GPIO_Pin = LCD_BL_PIN;
   io_struct.GPIO_Mode = GPIO_Mode_Out_OD;
   io_struct.GPIO_Speed = GPIO_Speed_10MHz;
   GPIO_Init(LCD_BL_PORT,&io_struct);

   io_struct.GPIO_Pin = LCD_CS_PIN | LCD_WR_PIN | LCD_RD_PIN | LCD_WR_PIN;
   io_struct.GPIO_Mode = GPIO_Mode_Out_PP;
   io_struct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(LCD_CTRL_PORT,&io_struct);

   io_struct.GPIO_Pin = 0xFFFF;
   io_struct.GPIO_Mode = GPIO_Mode_Out_PP;
   io_struct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(LCD_DB_PORT,&io_struct);
   

   GPIO_Write(LCD_DB_PORT,0x0000);

}

void ILI9341V_Init(void)
{
   ILI9341V_GPIO_Init();

}



