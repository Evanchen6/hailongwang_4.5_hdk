/*ui demo*/
#if defined(_MSC_VER)
#else
#include "stdio.h"
#endif


#include "gdi_font_engine.h"
#include "gdi.h"
//#include "graphic_interface.h"
#include "main_screen.h"
#include "bt_gap.h"
#include "mt25x3_hdk_lcd.h"
//add by chen
#include "stdint.h"
#include "stdbool.h"
#include <string.h>
#include "stdlib.h"
#include "memory_attribute.h"
#include "bsp_lcd.h"
#include "mt25x3_hdk_backlight.h"

#include "syslog.h"
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include "setting_lora.h"

#define LEFT_GAP 5
#define ITEM_HEIGHT 25

#define RESIZE_RATE LCD_CURR_HEIGHT/240
#define DEMO_ITEM_NAME_MAX_LEN 50

static struct {
  int32_t fota_title_x;
  int32_t fota_title_y;
  int32_t hr_title_x;
  int32_t hr_title_y;
  int32_t hrv_title_x;
  int32_t hrv_title_y;
  int32_t hrv_value_x;
  int32_t hrv_value_y;
  int32_t bt_name_x;
  int32_t bt_name_y;
  int32_t bt_status_x;
  int32_t bt_status_y;
  int32_t back_x1;
  int32_t back_y1;
  int32_t back_x2;
  int32_t back_y2;
  int32_t start_item;
  int32_t curr_item_num;
  int32_t one_screen_item_num;
  int32_t total_item_num;
  int32_t focus_point_index;
  gdi_color_t bg_color;
  gdi_color_t font_color;
  uint32_t width;
  uint32_t height;
} setting_lora_screen_cntx;

void show_setting_lora_screen(void);

//void swim_event_handler(message_id_enum event_id, int32_t param1, void* param2);
static void setting_lora_screen_cntx_init()
{
    if ((setting_lora_screen_cntx.height == 0) && (setting_lora_screen_cntx.width==0)) {

        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_HEIGHT, &(setting_lora_screen_cntx.height));
        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_WIDTH, &(setting_lora_screen_cntx.width));
//        LOG_I("width(%d), height(%d).\r\n", fota_screen_cntx.width, fota_screen_cntx.height);

        setting_lora_screen_cntx.bg_color = 0;
        setting_lora_screen_cntx.font_color = 0xFFFF;
        /* first */
        setting_lora_screen_cntx.fota_title_x = 5;
        setting_lora_screen_cntx.fota_title_y = 6;

        /* middle */
        setting_lora_screen_cntx.hr_title_x = LEFT_GAP;
        setting_lora_screen_cntx.hr_title_y = ITEM_HEIGHT*2 + setting_lora_screen_cntx.fota_title_y;
        setting_lora_screen_cntx.hrv_title_x = LEFT_GAP;
        setting_lora_screen_cntx.hrv_title_y = ITEM_HEIGHT + setting_lora_screen_cntx.hr_title_y;
        setting_lora_screen_cntx.hrv_value_x = LEFT_GAP;
        setting_lora_screen_cntx.hrv_value_y = ITEM_HEIGHT + setting_lora_screen_cntx.hrv_title_y;

        /* end */
        setting_lora_screen_cntx.bt_name_x = LEFT_GAP;
        setting_lora_screen_cntx.bt_name_y = setting_lora_screen_cntx.height - 6 - (ITEM_HEIGHT*3);
        setting_lora_screen_cntx.bt_status_x = LEFT_GAP;
        setting_lora_screen_cntx.bt_status_y = ITEM_HEIGHT*2 + setting_lora_screen_cntx.bt_name_y;
        setting_lora_screen_cntx.back_x1 = setting_lora_screen_cntx.width-80;
        setting_lora_screen_cntx.back_y1 = ITEM_HEIGHT*2 + setting_lora_screen_cntx.bt_name_y;
        setting_lora_screen_cntx.back_x2 = setting_lora_screen_cntx.width-1;
        setting_lora_screen_cntx.back_y2 = setting_lora_screen_cntx.height-1;

		setting_lora_screen_cntx.focus_point_index = 0;
		setting_lora_screen_cntx.start_item = 0;
		setting_lora_screen_cntx.one_screen_item_num = 2;
		setting_lora_screen_cntx.total_item_num = 2;
		setting_lora_screen_cntx.curr_item_num = 2;
    }

}

static uint8_t* setting_lora_convert_string_to_wstring(char* string)
{
    static uint8_t wstring[50];
    int32_t index = 0;
    if (!string) {
        return NULL;
    }
    while (*string) {
        wstring[index] = *((uint8_t*)string);
        wstring[index + 1] = 0;
        string++;
        index+=2;
    }
    return wstring;
}

void show_setting_lora_screen(void)
{
    int32_t x,y;

	x = 40 * RESIZE_RATE;
	y = 50 * RESIZE_RATE;

	setting_lora_screen_cntx_init();
	
	gdi_font_engine_display_string_info_t swim_string_info = {0};
    gdi_draw_filled_rectangle(0,0,setting_lora_screen_cntx.width-1,setting_lora_screen_cntx.height-1, setting_lora_screen_cntx.bg_color);

    gdi_font_engine_size_t font = GDI_FONT_ENGINE_FONT_MEDIUM;
    gdi_font_engine_color_t text_color = {0, 255, 255, 255};//white color

    gdi_font_engine_set_font_size(font);
    gdi_font_engine_set_text_color(text_color);

    swim_string_info.baseline_height = -1;
    swim_string_info.x = setting_lora_screen_cntx.fota_title_x;
    swim_string_info.y = setting_lora_screen_cntx.fota_title_y;
    swim_string_info.string = setting_lora_convert_string_to_wstring("swim..");
    swim_string_info.length = strlen("swim..");
    gdi_font_engine_display_string(&swim_string_info);

	gdi_lcd_update_screen(0,0,setting_lora_screen_cntx.width-1,setting_lora_screen_cntx.height-1);
}

