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
#include "custom_image_data_resource.h"
#include "custom_resource_def.h"

#include "syslog.h"
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include "traing_3km.h"

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
} running_3km_screen_cntx;

void show_running_3km_screen(void);

//void running_3km_event_handler(message_id_enum event_id, int32_t param1, void* param2);

static void running_3km_screen_cntx_init()
{
    if ((running_3km_screen_cntx.height == 0) && (running_3km_screen_cntx.width==0)) {

        BSP_LCD_GetParam(LCM_IOCTRL_QUERY__LCM_HEIGHT, &(running_3km_screen_cntx.height));
        BSP_LCD_GetParam(LCM_IOCTRL_QUERY__LCM_WIDTH, &(running_3km_screen_cntx.width));
//        LOG_I("width(%d), height(%d).\r\n", fota_screen_cntx.width, fota_screen_cntx.height);

        running_3km_screen_cntx.bg_color = 0;
        running_3km_screen_cntx.font_color = 0xFFFF;
        /* first */
        running_3km_screen_cntx.fota_title_x = 5;
        running_3km_screen_cntx.fota_title_y = 6;

        /* middle */
        running_3km_screen_cntx.hr_title_x = LEFT_GAP;
        running_3km_screen_cntx.hr_title_y = ITEM_HEIGHT*2 + running_3km_screen_cntx.fota_title_y;
        running_3km_screen_cntx.hrv_title_x = LEFT_GAP;
        running_3km_screen_cntx.hrv_title_y = ITEM_HEIGHT + running_3km_screen_cntx.hr_title_y;
        running_3km_screen_cntx.hrv_value_x = LEFT_GAP;
        running_3km_screen_cntx.hrv_value_y = ITEM_HEIGHT + running_3km_screen_cntx.hrv_title_y;

        /* end */
        running_3km_screen_cntx.bt_name_x = LEFT_GAP;
        running_3km_screen_cntx.bt_name_y = running_3km_screen_cntx.height - 6 - (ITEM_HEIGHT*3);
        running_3km_screen_cntx.bt_status_x = LEFT_GAP;
        running_3km_screen_cntx.bt_status_y = ITEM_HEIGHT*2 + running_3km_screen_cntx.bt_name_y;
        running_3km_screen_cntx.back_x1 = running_3km_screen_cntx.width-80;
        running_3km_screen_cntx.back_y1 = ITEM_HEIGHT*2 + running_3km_screen_cntx.bt_name_y;
        running_3km_screen_cntx.back_x2 = running_3km_screen_cntx.width-1;
        running_3km_screen_cntx.back_y2 = running_3km_screen_cntx.height-1;

		running_3km_screen_cntx.focus_point_index = 0;
		running_3km_screen_cntx.start_item = 0;
		running_3km_screen_cntx.one_screen_item_num = 2;
		running_3km_screen_cntx.total_item_num = 2;
		running_3km_screen_cntx.curr_item_num = 2;
    }

}

static void running_3km_screen_keypad_event_handler(hal_keypad_event_t* keypad_event,void* user_data)
{
		int32_t temp_index;
		int32_t max_item_num;
		int32_t temp_focus;
	/*
		keyvalue
		13 0xd ---enter
		14 0xe ---back
		17 0x11---up
		18 0x12---down
	*/
	
		GRAPHICLOG("[chenchen running_3km_screen_keypad_event_handler key state=%d, position=%d\r\n", (int)keypad_event->state, (int)keypad_event->key_data);
	
		if (keypad_event->key_data == 0xd && keypad_event->state == 0){
			temp_index = 1;
		} else if (keypad_event->key_data == 0xe && keypad_event->state == 0){
			temp_index = 2;
		} else if (keypad_event->key_data == 0x11 && keypad_event->state == 0){
			temp_index = 1;
		} else if (keypad_event->key_data == 0x12 && keypad_event->state == 0){
			temp_index = 1;
		}
		
		switch (temp_index){
			case -1:
				return;
			case -2:
//				main_screen_scroll_to_prevoius_page();
				break;
			case -3:
//				main_screen_scroll_to_next_page();
				break;
			case 0:
				break;
			case 2:
				show_traing_type_screen();
				return;
			default:
				break;
	
		}


}

uint8_t* running_3km_convert_string_to_wstring(char* string)
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

void show_running_3km_screen(void)
{
//	int32_t index = sensor_screen_cntx.start_item;
//   int32_t num = sensor_screen_cntx.curr_item_num;
    int32_t x,y;

	x = 40 * RESIZE_RATE;
	y = 50 * RESIZE_RATE;

	running_3km_screen_cntx_init();
	demo_ui_register_keypad_event_callback(running_3km_screen_keypad_event_handler, NULL);
	
	gdi_font_engine_display_string_info_t running_3km_string_info = {0};
    gdi_draw_filled_rectangle(0,0,running_3km_screen_cntx.width-1,running_3km_screen_cntx.height-1, running_3km_screen_cntx.bg_color);

	gdi_image_draw_by_id(0, 0, IMAGE_ID_ZBG_03_BMP);

    gdi_font_engine_size_t font = GDI_FONT_ENGINE_FONT_SMALL;
    gdi_font_engine_color_t text_color = {0, 0, 0, 0};//black color

    gdi_font_engine_set_font_size(font);
    gdi_font_engine_set_text_color(text_color);

    running_3km_string_info.baseline_height = -1;
    running_3km_string_info.x = running_3km_screen_cntx.fota_title_x;
    running_3km_string_info.y = running_3km_screen_cntx.fota_title_y;
    running_3km_string_info.string = running_3km_convert_string_to_wstring("RUN..");
    running_3km_string_info.length = strlen("3km..");
    gdi_font_engine_display_string(&running_3km_string_info);

	gdi_lcd_update_screen(0,0,running_3km_screen_cntx.width-1,running_3km_screen_cntx.height-1);
}

