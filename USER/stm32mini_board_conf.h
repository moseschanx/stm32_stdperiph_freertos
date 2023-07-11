#ifndef STM32MINI_BOARD_CONF
#define STM32MINI_BOARD_CONF

// LCD Backlight pin defines
#define LCD_BL_PIN GPIO_Pin_10
#define LCD_BL_PORT GPIOC
#define LCD_BL_PERIPH_CLK RCC_APB2Periph_GPIOC

// LEDs pin defines 
#define LED0_PIN GPIO_Pin_8
#define LED0_PORT GPIOA
#define LED0_PERIPH_CLK RCC_APB2Periph_GPIOA

#define LED1_PIN GPIO_Pin_2
#define LED1_PORT GPIOD
#define LED1_PERIPH_CLK RCC_APB2Periph_GPIOD

/* LCD Screen pin defines */
#define LCD_CS_PIN GPIO_Pin_9
#define LCD_RS_PIN GPIO_Pin_8
#define LCD_WR_PIN GPIO_Pin_7
#define LCD_RD_PIN GPIO_Pin_6 // Data or command selection 

#define LCD_CTRL_PORT GPIOC
#define LCD_CTRL_PERIPH_CLK RCC_APB2Periph_GPIOC

#define LCD_D0_PIN GPIO_Pin_0
#define LCD_D1_PIN GPIO_Pin_1
#define LCD_D2_PIN GPIO_Pin_2
#define LCD_D3_PIN GPIO_Pin_3
#define LCD_D4_PIN GPIO_Pin_4
#define LCD_D5_PIN GPIO_Pin_5
#define LCD_D6_PIN GPIO_Pin_6
#define LCD_D7_PIN GPIO_Pin_7
#define LCD_D8_PIN GPIO_Pin_8
#define LCD_D9_PIN GPIO_Pin_9
#define LCD_D10_PIN GPIO_Pin_10
#define LCD_D11_PIN GPIO_Pin_11
#define LCD_D12_PIN GPIO_Pin_12
#define LCD_D13_PIN GPIO_Pin_13
#define LCD_D14_PIN GPIO_Pin_14
#define LCD_D15_PIN GPIO_Pin_15

#define LCD_DB_PORT GPIOB
#define LCD_DB_PERIPH_CLK RCC_APB2Periph_GPIOB




#endif


