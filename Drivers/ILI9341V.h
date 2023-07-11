#ifndef ILI9341V_H
#define ILI9341V_H

#include "common.h"

/* ILI9341 LCD Control Lines Porting */
#define LCD_CS_L() GPIO_ResetBits(LCD_CTRL_PORT,LCD_CS_PIN)
#define LCD_CS_H() GPIO_SetBits(LCD_CTRL_PORT,LCD_CS_PIN)

#define LCD_WR_L() GPIO_ResetBits(LCD_CTRL_PORT,LCD_WR_PIN)
#define LCD_WR_H() GPIO_SetBits(LCD_CTRL_PORT,LCD_WR_PIN)

#define LCD_RD_L() GPIO_ResetBits(LCD_CTRL_PORT,LCD_RD_PIN)
#define LCD_RD_H() GPIO_SetBits(LCD_CTRL_PORT,LCD_RD_PIN)

/* Data or command selection */
#define LCD_RS_L() GPIO_ResetBits(LCD_CTRL_PORT,LCD_RS_PIN)
#define LCD_RS_H() GPIO_SetBits(LCD_CTRL_PORT,LCD_RS_PIN)

/* Information structures */
typedef struct {
    uint8_t id;             //LCD module/driver ID.
    uint8_t id_version;     //LCD module/driver version ID.
    uint8_t id_manufacture; //LCD module¡¯s manufacturer ID.
}disp_id_infos;

#
typedef union {
    uint32_t disp_status;
    struct {
        uint32_t booster_voltage_status : 32;
        uint32_t row_address_order : 31;
        uint32_t column_address_order : 30;
        uint32_t row_or_column_exchange : 29;

    }discrete_disp_status;
}testuion;

/* Function prototypes */

void __ili9341v_command_write_ll(uint8_t dat);

void __ili9341v_parameter_write_ll(uint16_t dat);

void __ili9341v_write(uint8_t command , uint8_t param_size , ...);

uint16_t __ili9341v_read_single(uint8_t command);

uint16_t* __ili9341v_read_ll(uint8_t command, uint8_t param_size);

disp_id_infos ILI9341V_ReadDisplayIDInfos(void);

void ILI9341V_GPIO_Init(void);

void ILI9341V_Init(void);


#endif

