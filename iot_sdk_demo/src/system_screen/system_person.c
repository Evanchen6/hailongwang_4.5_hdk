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
#include "system_person.h"

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
} system_person_screen_cntx;

void show_system_person_screen(void);

//void running_event_handler(message_id_enum event_id, int32_t param1, void* param2);

static void system_person_screen_cntx_init()
{
    if ((system_person_screen_cntx.height == 0) && (system_person_screen_cntx.width==0)) {

        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_HEIGHT, &(system_person_screen_cntx.height));
        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_WIDTH, &(system_person_screen_cntx.width));
//        LOG_I("width(%d), height(%d).\r\n", fota_screen_cntx.width, fota_screen_cntx.height);

        system_person_screen_cntx.bg_color = 0;
        system_person_screen_cntx.font_color = 0xFFFF;
        /* first */
        system_person_screen_cntx.fota_title_x = 5;
        system_person_screen_cntx.fota_title_y = 6;

        /* middle */
        system_person_screen_cntx.hr_title_x = LEFT_GAP;
        system_person_screen_cntx.hr_title_y = ITEM_HEIGHT*2 + system_person_screen_cntx.fota_title_y;
        system_person_screen_cntx.hrv_title_x = LEFT_GAP;
        system_person_screen_cntx.hrv_title_y = ITEM_HEIGHT + system_person_screen_cntx.hr_title_y;
        system_person_screen_cntx.hrv_value_x = LEFT_GAP;
        system_person_screen_cntx.hrv_value_y = ITEM_HEIGHT + system_person_screen_cntx.hrv_title_y;

        /* end */
        system_person_screen_cntx.bt_name_x = LEFT_GAP;
        system_person_screen_cntx.bt_name_y = system_person_screen_cntx.height - 6 - (ITEM_HEIGHT*3);
        system_person_screen_cntx.bt_status_x = LEFT_GAP;
        system_person_screen_cntx.bt_status_y = ITEM_HEIGHT*2 + system_person_screen_cntx.bt_name_y;
        system_person_screen_cntx.back_x1 = system_person_screen_cntx.width-80;
        system_person_screen_cntx.back_y1 = ITEM_HEIGHT*2 + system_person_screen_cntx.bt_name_y;
        system_person_screen_cntx.back_x2 = system_person_screen_cntx.width-1;
        system_person_screen_cntx.back_y2 = system_person_screen_cntx.height-1;

		system_person_screen_cntx.focus_point_index = 0;
		system_person_screen_cntx.start_item = 0;
		system_person_screen_cntx.one_screen_item_num = 2;
		system_person_screen_cntx.total_item_num = 2;
		system_person_screen_cntx.curr_item_num = 2;
    }

}

static void system_person_screen_keypad_event_handler(hal_keypad_event_t* keypad_event,void* user_data)
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
	
		GRAPHICLOG("[chenchen system_person_keypad_event_handler key state=%d, position=%d\r\n", (int)keypad_event->state, (int)keypad_event->key_data);
	
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
				show_system_screen();
				return;
			default:
				break;
	
		}


}

static uint8_t* system_person_convert_string_to_wstring(char* string)
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

void show_system_person_screen(void)
{
//	int32_t index = sensor_screen_cntx.start_item;
//   int32_t num = sensor_screen_cntx.curr_item_num;
    int32_t x,y;

	x = 40 * RESIZE_RATE;
	y = 30 * RESIZE_RATE;

	system_person_screen_cntx_init();
	demo_ui_register_keypad_event_callback(system_person_screen_keypad_event_handler, NULL);
	
	gdi_font_engine_display_string_info_t system_person_string_info = {0};
    gdi_draw_filled_rectangle(0,0,system_person_screen_cntx.width-1,system_person_screen_cntx.height-1, system_person_screen_cntx.bg_color);

    gdi_font_engine_size_t font = GDI_FONT_ENGINE_FONT_SMALL;
    gdi_font_engine_color_t text_color = {0, 255, 255, 255};//white color

    gdi_font_engine_set_font_size(font);
    gdi_font_engine_set_text_color(text_color);


	uint8_t person_id[10]={0x28,0x75,0x37,0x62,0x16,0x7F,0xF7,0x53,0x00};
    system_person_string_info.baseline_height = -1;
    system_person_string_info.x = x;
    system_person_string_info.y = y;
    system_person_string_info.string = person_id;
    system_person_string_info.length = 4;
    gdi_font_engine_display_string(&system_person_string_info);

    system_person_string_info.baseline_height = -1;
    system_person_string_info.x = x + 140;
    system_person_string_info.y = y;
    system_person_string_info.string = system_person_convert_string_to_wstring("00");
    system_person_string_info.length = strlen("00");
    gdi_font_engine_display_string(&system_person_string_info);

	uint8_t gender[10]={0x27,0x60,0x2B,0x52,0x00};
    system_person_string_info.baseline_height = -1;
    system_person_string_info.x = x;
    system_person_string_info.y = y + 40;
    system_person_string_info.string = gender;
    system_person_string_info.length = 4;
    gdi_font_engine_display_string(&system_person_string_info);

	uint8_t gender_txt[10]={0x37,0x75,0x00};
    system_person_string_info.baseline_height = -1;
    system_person_string_info.x = x + 140;
    system_person_string_info.y = y + 40;
    system_person_string_info.string = gender_txt;
    system_person_string_info.length = 4;
    gdi_font_engine_display_string(&system_person_string_info);

	uint8_t age[10]={0x74,0x5E,0x84,0x9F,0x00};
    system_person_string_info.baseline_height = -1;
    system_person_string_info.x = x;
    system_person_string_info.y = y + 80;
    system_person_string_info.string = age;
    system_person_string_info.length = 4;
    gdi_font_engine_display_string(&system_person_string_info);

    system_person_string_info.baseline_height = -1;
    system_person_string_info.x = x + 140;
    system_person_string_info.y = y + 80;
    system_person_string_info.string = system_person_convert_string_to_wstring("20");
    system_person_string_info.length = strlen("20");
    gdi_font_engine_display_string(&system_person_string_info);

	uint8_t weight[10]={0x53,0x4F,0xCD,0x91,0x00};
    system_person_string_info.baseline_height = -1;
    system_person_string_info.x = x;
    system_person_string_info.y = y + 120;
    system_person_string_info.string = weight;
    system_person_string_info.length = 4;
    gdi_font_engine_display_string(&system_person_string_info);

    system_person_string_info.baseline_height = -1;
    system_person_string_info.x = x + 140;
    system_person_string_info.y = y + 120;
    system_person_string_info.string = system_person_convert_string_to_wstring("70KG");
    system_person_string_info.length = strlen("70KG");
    gdi_font_engine_display_string(&system_person_string_info);

	gdi_lcd_update_screen(0,0,system_person_screen_cntx.width-1,system_person_screen_cntx.height-1);
}

