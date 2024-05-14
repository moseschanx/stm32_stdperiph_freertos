#include "common.h"



sgl_color_t tft_draw_buffer[20 * 240] = {0};

void tft_show_window(int16_t x1, int16_t y1, int16_t x2, int16_t y2, const sgl_color_t *src)
 {
    LCD_Fill(x1, y1, x2, y2, src);
 }

int stdout_device(const char *str)
{
    dbg_printf(str);
    return 0;
}

sgl_obj_t* sw;
static sgl_obj_t *msg;
void arcbar_anim_cb(struct sgl_anim *anim, void *data)
{
    static int value = 0;
    if(value > 100) {
        value = 0;
    }
    sgl_arcbar_set_value(anim->obj, value++);
    sgl_obj_event_press(sw);
}


extern const unsigned char icon_test[5000];
static sgl_img_t app_icon = {.bitmap = icon_test, .width = 50, .height = 50,};

int sgl_main()
{

    dbg_printf("STM32F103 SGL DEMO Start.\r\n");

    sgl_device_panel_t tft_panel = {
                                    .framebuffer = tft_draw_buffer,
                                    .buffer_size = sizeof(tft_draw_buffer),
                                    .xres = 240,
                                    .yres = 320,
                                    .xres_virtual = 240,
                                    .yres_virtual = 320,
                                    .flush_area = tft_show_window 
                                    };
    sgl_device_stdout_t stdout_dev = {
                                    .put = stdout_device,
                                    };


    sgl_device_register(&tft_panel, NULL);

    sgl_device_stdout_register(&stdout_dev);

      LCD_Init();

    sgl_init();


    sgl_style_t btn_style = {.body_color = SGL_BLUE, .text_color = SGL_RED, .radius = 16};
    sgl_obj_t* btn;
    sgl_obj_t *main_page;

    main_page = sgl_page_create();

    //sgl_obj_set_bg_img(main_page, &bg_img);

    sgl_page_set_active(main_page);

    SGL_LOG_INFO("button demo\r\n");
    //定义一个样式，主体颜色为SGL_BLUE，文本颜色为SGL_RED，圆角半径为16
    //创建一个按钮对象
    btn = sgl_button_create(main_page);
    //设置按钮的尺寸为宽98和高32
    sgl_obj_set_size(btn, 98, 32);
    //设置按钮的位置为x坐标100, y坐标50
    sgl_obj_set_pos(btn, 100, 50);
    //设置按钮的样式为btn_style
    sgl_obj_set_style(btn, &btn_style);
    //设置按钮的事件回调函数为btn_event，参数无
   // sgl_obj_set_event_cb(btn, btn_event, NULL);
    //设置按钮的按下后的颜色为SGL_GREEN
    sgl_button_set_toggle_color(btn, SGL_GREEN);
    //设置按钮的字体为song12
    sgl_button_set_font(btn, &song23);
    // //设置按钮的显示文本为Button
    sgl_button_set_text(btn, "Button");


    SGL_LOG_INFO("switch demo\r\n");
    sgl_style_t sw_style = {.body_color = sgl_rgb(10,200,20), .radius = 17};
    
     //创建一个开关对象，默认是开启状态
    sw = sgl_switch_create(main_page, true);
    //设置开关的大小为宽124和高34
    sgl_obj_set_size(sw, 80, 34);
    //设置开关的位置为中心向左对齐
    sgl_obj_set_pos_align(sw, SGL_ALIGN_CENTER_LEFT);
    //设置开关的样式
    sgl_obj_set_style(sw, &sw_style);
    //设置开关的点击事件
    //sgl_obj_set_event_cb(sw, sw_event, NULL);
    //设置开关的关闭状态下的颜色
    sgl_switch_set_toggle_color(sw, sgl_rgb(50,50,50));
    //设置开关的初始状态
    sgl_switch_set_status(sw, false);
    sgl_switch_set_anim(sw, true);


    //定义一个样式，主体颜色为SGL_BLUE，文本颜色为SGL_RED，圆角半径为16
    sgl_style_t arcbar_style = {.body_color = SGL_BLUE, .text_color = SGL_RED};
    //创建一个弧形指示器对象
    sgl_obj_t *arcbar = sgl_arcbar_create(main_page, 46);
    //设置弧形指示器的大小为宽100和高100
    sgl_obj_set_size(arcbar, 55, 55);
    //设置弧形指示器的样式为arcbar_style
    sgl_obj_set_style(arcbar, &arcbar_style);
    //设置弧形指示器的位置为x坐标170, y坐标120
    sgl_obj_set_pos(arcbar, 120, 120);
    //设置弧形指示器的字体
    sgl_arcbar_set_font(arcbar, &song23);
    //设置弧形指示器的厚度为10
    sgl_arcbar_set_thick(arcbar, 5);

    sgl_anim_t arcbar_anim;
    sgl_anim_set_interval(&arcbar_anim, 500);
    sgl_anim_set_endless(&arcbar_anim, true);
    sgl_anim_bind_obj(&arcbar_anim, arcbar);
    sgl_anim_set_anim_cb(&arcbar_anim, arcbar_anim_cb, NULL);
    sgl_anim_exec(&arcbar_anim);


    sgl_style_t app_style = {.body_color = SGL_BLUE, .text_color = SGL_RED, .radius = 10};
    sgl_obj_t *app = sgl_appstart_create(main_page);
    sgl_obj_set_style(app, &app_style);
    sgl_obj_set_size(app, 46, 46);
    sgl_obj_set_pos(app, 20, 160);
    sgl_obj_set_bg_img(app, &app_icon);
    sgl_obj_set_alpha(app, 0);
    sgl_appstart_set_text(app, "APP");
    sgl_appstart_set_font(app, &song10);

    while (1)
    {
        sgl_tick_inc(5);
        sgl_task_handler();
    }
}
