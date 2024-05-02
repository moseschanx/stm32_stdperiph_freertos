#include <stdlib.h>
#include <stdio.h>
#include "common.h"
//#include <stdio.h>
#include "test.h"
#include "sgl.h"


/* SGL Program-wise macro definitions */
        #define FRAME_BUFFER_XRES   240
        #define FRAME_BUFFER_YRES   320
        #define FRAME_BUFFER_XRES_VIRTUAL   240
        #define FRAME_BUFFER_YRES_VIRTUAL   320

/* SGL Program-wise frame buffer declaration */
//sgl_color_t sdl2_frame_buffer[FRAME_BUFFER_XRES_VIRTUAL * FRAME_BUFFER_YRES_VIRTUAL] = {0};
sgl_color_t tft_draw_buffer[20 * FRAME_BUFFER_XRES] = {0};

const uint8_t test_bitmap[]  = {

0x00,0x00,0x00,0x3e,0xc0,0x00,0x00,0x00,  //.......@%......
0x00,0x00,0x00,0xaf,0xe5,0x00,0x00,0x00,  //......%@@+......
0x00,0x00,0x00,0xee,0xec,0x00,0x00,0x00,  //......@@@%......
0x00,0x00,0x08,0xc8,0xae,0x50,0x00,0x00,  //.....+%+%@+.....
0x00,0x35,0x8e,0xe0,0x3e,0xe8,0x53,0x00,  //...++@@..@@++...
0xef,0xff,0xca,0x50,0x08,0xce,0xff,0xfe,  //@@@@%%+..+%@@@@@
0xae,0xc0,0x00,0x00,0x00,0x00,0x3e,0xe5,  //%@%..........@@+
0x08,0xec,0x00,0x00,0x00,0x03,0xee,0x50,  //.+@%........@@+.
0x00,0x8e,0xc0,0x00,0x00,0x3e,0xe5,0x00,  //..+@%......@@+..
0x00,0x0a,0xe3,0x00,0x00,0x8c,0x80,0x00,  //...%@.....+%+...
0x00,0x0c,0xe0,0x00,0x00,0x5e,0xa0,0x00,  //...%@.....+@%...
0x00,0x0e,0xc0,0x5c,0xc3,0x3e,0xc0,0x00,  //...@%.+%%..@%...
0x00,0x3e,0xcc,0xfc,0xee,0xce,0xe0,0x00,  //...@%%@%@@%@@...
0x00,0x5e,0xfc,0x50,0x05,0xef,0xe3,0x00,  //..+@@%+..+@@@...
0x00,0x5a,0x50,0x00,0x00,0x08,0xa3,0x00,  //..+%+......+%...

};
sgl_obj_t *two_page;
sgl_obj_t *main_page;
void btn_event(sgl_obj_t *obj, void *data)
{
    if(sgl_ev_stat(obj) == SGL_EVENT_PRESSED) {
        rtt_printf("buttton pressed\n");
    }
    else if(sgl_ev_stat(obj) == SGL_EVENT_RELEASED) {
        rtt_printf("buttton released\n");
        //sgl_page_set_active(two_page);
        // sgl_draw_round_rect_transp_on_bg(sgl_get_active_surf(NULL), rect1, 20, SGL_BLUE, 150);
        // sgl_draw_round_rect_transp_on_bg(sgl_get_active_surf(NULL), rect2, 20, SGL_RED, 150);
        // sgl_draw_round_rect_transp_on_bg(sgl_get_active_surf(NULL), rect3, 20, SGL_GREEN, 150);
    };
}
// extern unsigned char bg_test[460800];
sgl_img_t bg_img = {.bitmap = NULL, .width = 240, .height = 320,};
/* Memroy management function definitions */
void* memcpy(void *dst, const void *src, uint32_t size) {
    char *d = (char*) dst;
    const char *s = (const char*) src;

    for (int i = 0; i < size; ++i) {
        *d++ = *s++;
    }

    return dst;
}
void* memset(void *dst, int val, unsigned size) {
    uint8_t *byte_dst = (uint8_t*) dst; // Cast to uint8_t* for byte-level access

    for (unsigned i = 0; i < size; ++i) {
        byte_dst[i] = (uint8_t) val; // Assign the value to each byte, casting to uint8_t to ensure it's within range
    }

    return dst; // Return the destination pointer
}
uint32_t strlen(char *str)
{
  uint32_t len = 0;
  while(str[len] != '\0')
  {
    len++;
  }
  return len;
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
// int fputc(int ch, FILE *f)
// {
//  /* Place your implementation of fputc here */
//  /* e.g. write a character to the USART */
//  USART_SendData(USART1, (uint8_t) ch);

//  /* Loop until the end of transmission */
//  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
//  {}

//  return ch;
// }

void MCU_Init(void)
{
  
// rtt_printf("System Initialization Begin.\n ");

  /* RCC Config */
if (RCC_ClockConfig() != SUCCESS)
   HardFault_Handler();

RCC_PeriphClock_Init();

SysTick_Init();

 USER_DMA_Init();

 USER_GPIO_Init();

 USER_ADC_Init();

 USER_USART_Init();

//rtt_printf("System Initialization End.\n");

// SWO_PrintString("Test printing\n");


  


   
  /* blinky subroutine hardware prepare */
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);



	// GPIO_InitTypeDef gpio_init = {0};
	// gpio_init.GPIO_Mode = GPIO_Mode_Out_OD;
	// gpio_init.GPIO_Pin = GPIO_Pin_8;
	// gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

	// GPIO_Init(GPIOA, &gpio_init);

	// GPIO_ResetBits(GPIOA,GPIO_Pin_8);

	// gpio_init.GPIO_Mode = GPIO_Mode_Out_OD;
	// gpio_init.GPIO_Pin = GPIO_Pin_2;
	// gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

	// GPIO_Init(GPIOD, &gpio_init);
	// GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	

   
  
} 

 void tft_show_window(int16_t x1, int16_t y1, int16_t x2, int16_t y2, const sgl_color_t *src)
 {
    LCD_Fill(x1, y1, x2, y2, src);
 }


sgl_event_pos_t sdl_mouse_get(void *data)
{
  // TODO : Port to LCD.
//     sgl_event_pos_t ev_pos;
//     SDL_Event *event = (SDL_Event*)data;
//     switch (event->type)
//     {
//     case SDL_MOUSEBUTTONDOWN:
//         ev_pos.x = event->motion.x;
//         ev_pos.y = event->motion.y;
//         ev_pos.type = SGL_EVENT_PRESSED;
//         break;
//     case SDL_MOUSEBUTTONUP:
//         ev_pos.x = event->motion.x;
//         ev_pos.y = event->motion.y;
//         ev_pos.type = SGL_EVENT_RELEASED;
//         break;
//     default: ev_pos.type = SGL_EVENT_NULL;
//     }
//     return ev_pos;
// }
}
int stdout_device(char *str)
{
    return rtt_printf("%s\n", str);
}

void SGL_Init(void)
{
  

    int quit = 0;

    sgl_device_panel_t sdl_panel = {
                                    //.framebuffer = sdl2_frame_buffer,
                                    .framebuffer = tft_draw_buffer,
                                    .buffer_size = sizeof(tft_draw_buffer),
                                    .xres = FRAME_BUFFER_XRES,
                                    .yres = FRAME_BUFFER_YRES,
                                    .xres_virtual = FRAME_BUFFER_XRES_VIRTUAL,
                                    .yres_virtual = FRAME_BUFFER_YRES_VIRTUAL,
                                    .flush_area = tft_show_window
                                    };
    
    sgl_device_input_t sdl_mouse = {
                                    .get = sdl_mouse_get,
                                   };

    sgl_device_stdout_t stdout_dev = {
                                    .put = stdout_device,
                                    };

    sgl_device_register(&sdl_panel, &sdl_mouse);
    
    sgl_device_stdout_register(&stdout_dev);

    sgl_init();

    SGL_LOG_INFO("start sgl...");

    main_page = sgl_page_create();
    two_page = sgl_page_create();

   // sgl_page_set_background(main_page, &bg_img);

    sgl_page_set_active(main_page);

    sgl_style_t radio_style = {.body_color = SGL_BLACK, .text_color = SGL_BLUE, .radius = 3};
    sgl_obj_t *radio = sgl_radiobtn_create(main_page, true);
    sgl_obj_set_size(radio, 150, 16);
    sgl_obj_set_pos(radio, 50, 250);
    sgl_obj_set_event_cb(radio, btn_event, NULL);
    sgl_obj_set_style(radio, &radio_style);
    sgl_radiobtn_set_font(radio, &cascadia_mono17);
    sgl_radiobtn_set_text(radio, "SGL is good");

    // sgl_style_t icon_style = {.body_color = SGL_RED, .text_color = SGL_WHITE, .radius = 10};
    // sgl_obj_t* circle = sgl_rect_create(main_page);
    // sgl_obj_set_size(circle, 40, 40);
    // sgl_obj_set_pos(circle, 40, 40);
    // sgl_obj_set_style(circle, &icon_style);
    // sgl_obj_set_event_cb(circle, btn_event, NULL);
    // sgl_obj_set_alpha(circle, 200);
    // sgl_obj_set_bgimg(circle, &icon_img);


  
}

int main()
{
  
  MCU_Init();
  delay_ms(62);
  LCD_Init();
  English_Font_test();
  SGL_Init();

  

  //English_Font_test();


   while(1)
   {

    sgl_task_handler();

  /* blinky */
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	delay_ms(100);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	delay_ms(100);


  /* USART Test */
  //  USART_SendData(USART1,'X');
  // /* Loop until the end of transmission */
  // while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
 
   }
	 

}




