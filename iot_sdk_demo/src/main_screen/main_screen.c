/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

#include "stdint.h"
#include "stdbool.h"
#include <string.h>
#include "stdio.h"
#include "stdlib.h"
#include "FreeRTOS.h"
#include "gdi.h"
#include "gdi_font_engine.h"
#include "main_screen.h"
#include "memory_attribute.h"
#include "mt25x3_hdk_lcd.h"
#include "bsp_lcd.h"
#include "mt25x3_hdk_backlight.h"

//add by chenchen
#include "custom_image_data_resource.h"
#include "custom_resource_def.h"
#include "timers.h"
#include "hal_display_pwm.h"
#include "hal_display_pwm_internal.h"
#include "task.h"

#include "hal_keypad.h"
#include "battery_management.h"

#define CONFIG_INCLUDE_HEADER
#include "screen_config.h"
#undef CONFIG_INCLUDE_HEADER
#define CONFIG_INCLUD_BODY

#define DEMO_ITEM_NAME_MAX_LEN 50
#define PERVIOUS_PAGE_STRING_NAME "previous page"
#define NEXT_PAGE_STRING_NAME "next page"
#define DEMO_TITLE_STRING_NAME "Main menu:"

TimerHandle_t vWatchfaceTimer = NULL;
extern uint8_t sdkdemo_sleep_handle;


typedef struct list_item_struct {
    show_screen_proc_f show_screen_f;
    event_handle_func event_handle_f;
    uint8_t name[DEMO_ITEM_NAME_MAX_LEN];
} list_item_struct_t;


static const list_item_struct_t demo_item[] =
{
#include "screen_config.h"
};

static struct {
    int32_t start_item;
    int32_t curr_item_num;
    int32_t one_screen_item_num;
    int32_t total_item_num;
    int32_t top_gap;
    int32_t left_gap;
    int32_t right_gap;
    int32_t bottom_gap;
    int32_t line_gap;
    int32_t item_height;
    int32_t item_width;
    int32_t LCD_WIDTH;
    int32_t LCD_HEIGHT;
    int32_t has_previous_page;
    int32_t has_next_page;
	int32_t focus_point_index;   //add by chenchen
    gdi_font_engine_color_t color;
} main_screen_cntx;

ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint32_t LCD_CURR_HEIGHT = 320, LCD_CURR_WIDTH = 320;

static event_handle_func curr_event_handler;

#define RESIZE_RATE LCD_CURR_HEIGHT/240
ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN unsigned char frame_buffer[ScrnWidth*ScrnHeight*2];


static int32_t main_screen_get_index(int32_t x, int32_t y);
//static void main_screen_draw(void);
static void tui_main_screen_draw(void);

static void main_screen_scroll_to_prevoius_page(void);
static void main_screen_scroll_to_next_page(void);

static void main_screen_event_handle(message_id_enum event_id, int32_t param1, void* param2)
{
}

void vWatchfaceTimerCallback( TimerHandle_t xTimer )
{
	if (demo_item[3].show_screen_f) {
		demo_item[3].show_screen_f();
		GRAPHICLOG("show_main_wf");
	}

}

void show_watchface_timer_stop(void)
{
    if (vWatchfaceTimer && (xTimerIsTimerActive(vWatchfaceTimer) != pdFALSE)) {
        xTimerStop(vWatchfaceTimer, 0);
    }

}

void show_watchface_timer_init(uint32_t time)
{
    if (vWatchfaceTimer && (xTimerIsTimerActive(vWatchfaceTimer) != pdFALSE)) {
        xTimerStop(vWatchfaceTimer, 0);
    } else {
		vWatchfaceTimer = xTimerCreate( "vWatchfaceTimer",           // Just a text name, not used by the kernel.
                                      ( time*1000 / portTICK_PERIOD_MS), // The timer period in ticks.
                                      pdFALSE,                    // The timer is a one-shot timer.
                                      0,                          // The id is not used by the callback so can take any value.
                                      vWatchfaceTimerCallback     // The callback function that switches the LCD back-light off.
                                   );
    }
	xTimerStart(vWatchfaceTimer, 0);
}

static void main_need_lcd_init(void)
{

	hal_sleep_manager_lock_sleep(sdkdemo_sleep_handle);

	hal_display_pwm_deinit();
	hal_display_pwm_init(HAL_DISPLAY_PWM_CLOCK_26MHZ);
	hal_display_pwm_set_duty(20);
	bsp_lcd_exit_idle();

}


//add by chenchen for keypad
static void main_screen_keypad_event_handler(hal_keypad_event_t* keypad_event,void* user_data)
{
	static int32_t item_down_index = -1;
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
	main_need_lcd_init();

	GRAPHICLOG("[chenchen main_screen_keypad_event_handler key state=%d, position=%d\r\n", (int)keypad_event->state, (int)keypad_event->key_data);
	if( xTimerReset( vWatchfaceTimer, 100 ) != pdPASS ) {
		LOG_I(common, "chenchen main show wf_xTimerReset fail");
	}


	if (keypad_event->key_data == 0xd && keypad_event->state == 0){
		temp_index = 1;
	} else if (keypad_event->key_data == 0xe && keypad_event->state == 0){
		temp_index = -1;
	} else if (keypad_event->key_data == 0x11 && keypad_event->state == 0){
		temp_focus = main_screen_cntx.focus_point_index+1;
		max_item_num = main_screen_cntx.total_item_num;
		main_screen_cntx.focus_point_index = temp_focus%max_item_num;
		GRAPHICLOG("[chenchen[get key]main_screen_cntx.focus_point_index=%d,\r\n", main_screen_cntx.focus_point_index);
		if (main_screen_cntx.focus_point_index < 0)
			main_screen_cntx.focus_point_index = main_screen_cntx.total_item_num -1;
		
	} else if (keypad_event->key_data == 0x12 && keypad_event->state == 0){
		temp_focus = main_screen_cntx.focus_point_index-1;
		max_item_num = main_screen_cntx.total_item_num;
		main_screen_cntx.focus_point_index = temp_focus%max_item_num;
		
		if (main_screen_cntx.focus_point_index < 0)
			main_screen_cntx.focus_point_index = main_screen_cntx.total_item_num -1;
	}

	switch (temp_index){
		case -2:
			main_screen_scroll_to_prevoius_page();
			break;
		case -3:
			main_screen_scroll_to_next_page();
			break;
		case -1:
			show_watchface_timer_stop();
			curr_event_handler = demo_item[3].event_handle_f;
			if (demo_item[3].show_screen_f) {
				demo_item[3].show_screen_f();
			}

			return;

		case 1:
			show_watchface_timer_stop();
			curr_event_handler = demo_item[main_screen_cntx.focus_point_index].event_handle_f;
            if (demo_item[main_screen_cntx.focus_point_index].show_screen_f) {
                demo_item[main_screen_cntx.focus_point_index].show_screen_f();
            }
			return;
		default:
            break;

	}
//	main_screen_draw();
	tui_main_screen_draw();

}
/*****************************************************************************
 * FUNCTION
 *  main_screen_pen_event_handler
 * DESCRIPTION
 *  Process pen event
 * PARAMETERS
 *  touch_event     [in]
 *  user_data       [in]
 * RETURNS
 *  void
 *****************************************************************************/
static void main_screen_pen_event_handler(touch_event_struct_t* touch_event, void* user_data)
{
    static int32_t item_down_index = -1;
    int32_t temp_index;
	GRAPHICLOG("[chenchen pen_event_handler ");

    temp_index = main_screen_get_index(touch_event->position.x, touch_event->position.y);
    if (touch_event->type == TOUCH_EVENT_DOWN) {
        item_down_index = temp_index;
        return;
    } else if (touch_event->type == TOUCH_EVENT_UP) {
        if (item_down_index == -1) {
            return;
        }
    }

    if (item_down_index != temp_index) {
        item_down_index = -1;
        return;
    }
	

    item_down_index = -1;

    switch (temp_index) {
        case -1:
            return;
        case -2:
            main_screen_scroll_to_prevoius_page();
            break;
        case -3:
            main_screen_scroll_to_next_page();
            break;
        default:
            curr_event_handler = demo_item[temp_index].event_handle_f;
            if (demo_item[temp_index].show_screen_f) {
                demo_item[temp_index].show_screen_f();
            }
            return;
    }
//    main_screen_draw();
}

/*****************************************************************************
 * FUNCTION
 *  common_event_handler
 * DESCRIPTION
 *  dispatch event to current screen
 * PARAMETERS
 *  event_id     [in]
 *  param1       [in]
 *  param2       [in]
 * RETURNS
 *  void
 *****************************************************************************/
void common_event_handler(message_id_enum event_id, int32_t param1, void* param2)
{
    if (curr_event_handler) {
        curr_event_handler(event_id, param1, param2);
    }
}

/*****************************************************************************
 * FUNCTION
 *  convert_string_to_wstring
 * DESCRIPTION
 *  convert string to Wstring
 * PARAMETERS
 *  string     [in]
 * RETURNS
 *  uint8_t*
 *****************************************************************************/
static uint8_t* convert_string_to_wstring(uint8_t* string)
{
    static uint8_t wstring[50];
    int32_t index = 0;
    if (!string) {
        return NULL;
    }
    while (*string) {
        wstring[index] = *string;
        wstring[index + 1] = 0;
        string++;
        index+=2;
    }
    return wstring;
}

/*****************************************************************************
 * FUNCTION
 *  main_screen_cntx_init
 * DESCRIPTION
 *  Init main screen context
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
static void main_screen_cntx_init()
{
    static int32_t is_init;
    gdi_font_engine_string_info_t string_info;
    if (is_init)
        return;
    is_init = 1;
    
    main_screen_cntx.LCD_WIDTH = 240 * RESIZE_RATE;
    main_screen_cntx.LCD_HEIGHT = 240 * RESIZE_RATE;
    main_screen_cntx.top_gap = 130 * RESIZE_RATE;
    main_screen_cntx.left_gap = 80 * RESIZE_RATE;
    main_screen_cntx.right_gap = 3 * RESIZE_RATE;
    main_screen_cntx.bottom_gap = 3 * RESIZE_RATE;
    main_screen_cntx.line_gap = 15 * RESIZE_RATE;
    main_screen_cntx.total_item_num = sizeof(demo_item)/sizeof(list_item_struct_t);
    main_screen_cntx.start_item = 0;
    main_screen_cntx.color.alpha = 0xFF;
    main_screen_cntx.color.red = 0xFF;
    main_screen_cntx.color.green = 0xFF;
    main_screen_cntx.color.blue = 0xFF;
	main_screen_cntx.focus_point_index = 0;   //add by chenchen

    string_info.string = convert_string_to_wstring((uint8_t*) demo_item[0].name);
    string_info.count = strlen((char*) demo_item[0].name);
    gdi_font_engine_get_string_information(&string_info);
    main_screen_cntx.item_width = string_info.width;
    main_screen_cntx.item_height = string_info.height;

    if ((main_screen_cntx.LCD_WIDTH - main_screen_cntx.left_gap - main_screen_cntx.right_gap) < main_screen_cntx.item_width) {
        main_screen_cntx.item_width = main_screen_cntx.LCD_WIDTH - main_screen_cntx.left_gap - main_screen_cntx.right_gap;
    }
    main_screen_cntx.item_height += main_screen_cntx.line_gap;
    main_screen_cntx.one_screen_item_num = (main_screen_cntx.LCD_HEIGHT - main_screen_cntx.top_gap - main_screen_cntx.bottom_gap)/main_screen_cntx.item_height;
    if (main_screen_cntx.one_screen_item_num < main_screen_cntx.total_item_num) {
        main_screen_cntx.curr_item_num = main_screen_cntx.one_screen_item_num - 1;
        main_screen_cntx.has_next_page = 1;
    } else {
        main_screen_cntx.curr_item_num = main_screen_cntx.total_item_num;
        main_screen_cntx.has_next_page = 0;
    }
    main_screen_cntx.has_previous_page = 0;
    gdi_init(LCD_CURR_WIDTH, LCD_CURR_HEIGHT, GDI_COLOR_FORMAT_16, frame_buffer);
}

/*****************************************************************************
 * FUNCTION
 *  main_screen_scroll_to_next_page
 * DESCRIPTION
 *  Change to next page
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
static void main_screen_scroll_to_next_page()
{
    int32_t left_item;
    if (main_screen_cntx.has_next_page) {
        left_item = main_screen_cntx.total_item_num - (main_screen_cntx.start_item + main_screen_cntx.curr_item_num);
        if (left_item > 0) {
            main_screen_cntx.has_previous_page = 1;
            if (left_item <= main_screen_cntx.one_screen_item_num - main_screen_cntx.has_previous_page) {
                main_screen_cntx.has_next_page = 0;
            } else {
                main_screen_cntx.has_next_page = 1;
            }
            main_screen_cntx.start_item += main_screen_cntx.curr_item_num;
            main_screen_cntx.curr_item_num = main_screen_cntx.one_screen_item_num 
                                            - main_screen_cntx.has_previous_page - main_screen_cntx.has_next_page;
        } else {
            //error case, logic wrong, should not be hit
        }
    } else {
        return;
    }
}

/*****************************************************************************
 * FUNCTION
 *  main_screen_scroll_to_prevoius_page
 * DESCRIPTION
 *  Change to previous page
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
static void main_screen_scroll_to_prevoius_page()
{
    if (main_screen_cntx.has_previous_page) {
        if (main_screen_cntx.start_item == main_screen_cntx.one_screen_item_num -1) {
            main_screen_cntx.has_previous_page = 0;
        } else {
            main_screen_cntx.has_previous_page = 1;
        }
        
        main_screen_cntx.has_next_page = 1;
        main_screen_cntx.curr_item_num =  main_screen_cntx.one_screen_item_num 
                                            - main_screen_cntx.has_previous_page - main_screen_cntx.has_next_page;
        main_screen_cntx.start_item -= main_screen_cntx.curr_item_num;
    } else {
    }
}

/*****************************************************************************
 * FUNCTION
 *  my_itoa
 * DESCRIPTION
 *  convert int to string
 * PARAMETERS
 *  num     [in]
 *  str     [in]
 *  radix   [in]
 * RETURNS
 *  char*
 *****************************************************************************/
static char* my_itoa(int num,char* str,int radix)
{
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned unum;
    int i=0,j,k;
    char temp;

    if(radix==10 && num<0) {
        unum=(unsigned)-num;
        str[i++]='-';
    } else {
        unum=(unsigned)num;
    }

    do {
        str[i++] = index[unum%(unsigned)radix];
        unum /= radix;
    } while(unum);

    str[i]='\0';
    if(str[0]=='-') {
        k=1;
    } else {
        k=0;
    }

    for(j=k;j<=(i-1)/2;j++)
    {
        temp=str[j];
        str[j]=str[i-1+k-j];
        str[i-1+k-j]=temp;
    }
    return str;
}


static uint16_t main_get_battery_img_number(uint16_t num)
{
    uint16_t img_ptr;
    switch (num) {
        case 0:
        	   img_ptr = IMAGE_ID_BATTERY_NUMBER_0_BMP;
        	   break;
        case 1:
        	   img_ptr = IMAGE_ID_BATTERY_NUMBER_1_BMP;
        	   break;
        case 2:
        	   img_ptr = IMAGE_ID_BATTERY_NUMBER_2_BMP;
        	   break;
        case 3:
        	   img_ptr = IMAGE_ID_BATTERY_NUMBER_3_BMP;
        	   break;
        case 4:
        	   img_ptr = IMAGE_ID_BATTERY_NUMBER_4_BMP;
        	   break;
        case 5:
        	   img_ptr = IMAGE_ID_BATTERY_NUMBER_5_BMP;
        	   break;
        case 6:
        	   img_ptr = IMAGE_ID_BATTERY_NUMBER_6_BMP;
        	   break;
        case 7:
        	   img_ptr = IMAGE_ID_BATTERY_NUMBER_7_BMP;
        	   break;
        case 8:
        	   img_ptr = IMAGE_ID_BATTERY_NUMBER_8_BMP;
        	   break;
        case 9:
        	   img_ptr =  IMAGE_ID_BATTERY_NUMBER_9_BMP;
        	   break;
        case 0xff:
        	   img_ptr  = IMAGE_ID_BATTERY_NUMBER_0_BMP;
        	   break;
        default:
                   //LOG_I(common, "wrong big number");
                   img_ptr = IMAGE_ID_BATTERY_NUMBER_0_BMP;
        	   break;
    }
    return img_ptr;

}

static uint16_t main_get_battery_show_img(uint16_t num)
{
	uint16_t img_ptr;
	if (num <= 25 && num > 0) {
		img_ptr = IMAGE_ID_BATTERY_25_BMP;
	} else if (num <=50 && num > 25) {
		img_ptr = IMAGE_ID_BATTERY_50_BMP;
	} else if (num <= 99 && num > 50) {
		img_ptr = IMAGE_ID_BATTERY_75_BMP;
	}
	return img_ptr;
}


static void get_battery_information(void)
{
    int32_t capacity, charger_current, charger_status, charger_type, battery_temperature, battery_volt, capacity_level;

    capacity = battery_management_get_battery_property(BATTERY_PROPERTY_CAPACITY);
    capacity_level = battery_management_get_battery_property(BATTERY_PROPERTY_CAPACITY_LEVEL);
    charger_current = battery_management_get_battery_property(BATTERY_PROPERTY_CHARGING_CURRENT);
    charger_status = battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_EXIST);
    charger_type = battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_TYPE);
    battery_temperature = battery_management_get_battery_property(BATTERY_PROPERTY_TEMPERATURE);
    battery_volt = battery_management_get_battery_property(BATTERY_PROPERTY_VOLTAGE);

	GRAPHICLOG("[chenchen battery capacity %d capacity_level %d charger_current %d charger_status %d charger_type %d\r\n", capacity,capacity_level,charger_current,charger_status,charger_type);

}
static void tui_main_screen_draw()
{
    int32_t index = main_screen_cntx.start_item;
    int32_t num = main_screen_cntx.curr_item_num;
	int32_t pre;
	int32_t next;
    int32_t x,y;
	int16_t bat_num1,bat_num2,bat_img;
	int32_t capacity;
	static int32_t is_fisrt_show;
    gdi_font_engine_display_string_info_t param;

	x = main_screen_cntx.left_gap;
	y = main_screen_cntx.top_gap;

	if ((main_screen_cntx.focus_point_index != 0) && (main_screen_cntx.focus_point_index != main_screen_cntx.total_item_num - 1)){
		pre = main_screen_cntx.focus_point_index - 1;
		next = main_screen_cntx.focus_point_index + 1;
	} else if (main_screen_cntx.focus_point_index == 0) {
		pre = main_screen_cntx.total_item_num - 1;
		next = main_screen_cntx.focus_point_index + 1;
	} else if (main_screen_cntx.focus_point_index == main_screen_cntx.total_item_num - 1) {
		pre = main_screen_cntx.focus_point_index - 1;
		next = main_screen_cntx.start_item;
	}

	gdi_font_engine_set_font_size(GDI_FONT_ENGINE_FONT_SMALL);
	
	gdi_draw_filled_rectangle(0,0,240 * RESIZE_RATE - 1,240 * RESIZE_RATE - 1,gdi_get_color_from_argb(0, 0, 0, 0));
	vTaskDelay(10);


//battary status 
//	get_battery_information();
	capacity = battery_management_get_battery_property(BATTERY_PROPERTY_CAPACITY);
	if (capacity == 100) {
		gdi_image_draw_by_id(11, 7, IMAGE_ID_BATTERY_FULL_BMP);
		gdi_image_draw_by_id(51, 8, IMAGE_ID_BATTERY_NUMBER_1_BMP);
		gdi_image_draw_by_id(61, 8, IMAGE_ID_BATTERY_NUMBER_0_BMP);
		gdi_image_draw_by_id(71, 8, IMAGE_ID_BATTERY_NUMBER_0_BMP);
		gdi_image_draw_by_id(81, 8, IMAGE_ID_BATTERY_NUMBER_PERCENT_BMP);

	} else if (capacity == 0) {
		gdi_image_draw_by_id(11, 7, IMAGE_ID_BATTERY_EMPTY_BMP);

	} else {
		bat_num1 = capacity / 10;
		bat_num2 = capacity % 10;
		bat_num1 = main_get_battery_img_number(bat_num1);
		bat_num2 = main_get_battery_img_number(bat_num2);
		bat_img = main_get_battery_show_img(capacity);

		gdi_image_draw_by_id(11, 7, bat_img);
		gdi_image_draw_by_id(51, 8, bat_num1);
		gdi_image_draw_by_id(61, 8, bat_num2);
		gdi_image_draw_by_id(71, 8, IMAGE_ID_BATTERY_NUMBER_PERCENT_BMP);
	}
	
	gdi_image_draw_by_id(8, 97, main_screen_cntx.focus_point_index+91);


    gdi_font_engine_color_t text_color = {0, 255, 255, 255};//white color
    gdi_font_engine_set_text_color(text_color);

	param.x = x;
	param.y = y - 90;
	param.string = (uint8_t*) demo_item[pre].name;
	param.length = 4;
	param.baseline_height = -1;
	gdi_font_engine_display_string(&param);

	gdi_image_draw_by_id(8, 74, IMAGE_ID_LINE_BMP);

	gdi_lcd_update_screen(0, 0, LCD_CURR_WIDTH - 1, y - 40);
/*-------------------------------------------------------------*/	

    gdi_font_engine_color_t text_color1 = {0, 255, 255, 255};//white color
    gdi_font_engine_set_text_color(text_color1);


	param.x = x;
	param.y = y + 73;
	param.string = (uint8_t*) demo_item[next].name;
	param.length = 4;
	param.baseline_height = -1;
	gdi_font_engine_display_string(&param);

	gdi_image_draw_by_id(8, 188, IMAGE_ID_LINE_BMP);

	gdi_lcd_update_screen(0, y + 41, LCD_CURR_WIDTH - 1, LCD_CURR_HEIGHT - 1);
/*-------------------------------------------------------------*/	


	gdi_font_engine_set_font_size(GDI_FONT_ENGINE_FONT_LARGE);
    gdi_font_engine_color_t text_color2 = {0, 0, 0, 255};
    gdi_font_engine_set_text_color(text_color2);	

	param.x = x;
	param.y = y - 17;
	param.string = (uint8_t*) demo_item[main_screen_cntx.focus_point_index].name;
	param.length = 4;
	param.baseline_height = -1;
	gdi_font_engine_display_string(&param);


	gdi_lcd_update_screen(0, y - 39, LCD_CURR_WIDTH - 1, y+ 40);

}

/*****************************************************************************
 * FUNCTION
 *  main_screen_draw
 * DESCRIPTION
 *  Draw main screen
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
static void main_screen_draw()
{
    int32_t index = main_screen_cntx.start_item;
    int32_t num = main_screen_cntx.curr_item_num;
    int32_t x,y;
    gdi_font_engine_display_string_info_t param;

    x = main_screen_cntx.left_gap;
    y = main_screen_cntx.top_gap;
    gdi_draw_filled_rectangle(0,0,240 * RESIZE_RATE - 1,240 * RESIZE_RATE - 1,0);

    param.x = 10 * RESIZE_RATE;
    param.y = 10 * RESIZE_RATE;
    param.string = convert_string_to_wstring((uint8_t*) DEMO_TITLE_STRING_NAME);
    param.length = strlen(DEMO_TITLE_STRING_NAME);
    param.baseline_height = -1;
    gdi_font_engine_display_string(&param);


    if (main_screen_cntx.has_previous_page) {
        
        param.x = x;
        param.y = y;
        param.string = convert_string_to_wstring((uint8_t*) PERVIOUS_PAGE_STRING_NAME);
        param.length = strlen(PERVIOUS_PAGE_STRING_NAME);
        param.baseline_height = -1;
        gdi_font_engine_display_string(&param);
        y += main_screen_cntx.item_height;
    }
    while (num) {
        uint8_t pre_index[10];
        int32_t str_len;
		//add by chenchen 
		if (index == main_screen_cntx.focus_point_index){
			my_itoa((int) index, (char*) pre_index,10);
			str_len = strlen((char*) pre_index);
			pre_index[str_len] = '.';
			pre_index[str_len + 1] = '*';
			pre_index[str_len + 2] = 0;

			gdi_image_draw_by_id(10, 100, main_screen_cntx.focus_point_index+41);

		}else {
        	my_itoa((int) index, (char*) pre_index,10);
        	str_len = strlen((char*) pre_index);
        	pre_index[str_len] = '.';        	
			pre_index[str_len + 1] = 0;
		}
		
        param.x = x - 30 * RESIZE_RATE;
        param.y = y;
        param.string = convert_string_to_wstring((uint8_t*) pre_index);
        param.length = strlen((char*) pre_index);
        param.baseline_height = -1;
        gdi_font_engine_display_string(&param);


        param.x = x;
        param.y = y;
        param.string = convert_string_to_wstring((uint8_t*) demo_item[index].name);
        param.length = strlen((char*) demo_item[index].name);
        param.baseline_height = -1;
        gdi_font_engine_display_string(&param);
                                
        y += main_screen_cntx.item_height;
        index++;
        num--;
    }
    
    if (main_screen_cntx.has_next_page) {
        
        param.x = x;
        param.y = y;
        param.string = (uint8_t*)convert_string_to_wstring((uint8_t *) NEXT_PAGE_STRING_NAME);
        param.length = strlen(NEXT_PAGE_STRING_NAME);
        param.baseline_height = -1;
        gdi_font_engine_display_string(&param);
        y += main_screen_cntx.item_height;
    }
    
    gdi_lcd_update_screen(0, 0, LCD_CURR_WIDTH - 1, LCD_CURR_HEIGHT - 1);
}

// -1 means not hit, -2 means prevoius page, -3 means next page
/*****************************************************************************
 * FUNCTION
 *  main_screen_get_index
 * DESCRIPTION
 *  get item index
 * PARAMETERS
 *  x       [in]
 *  y       [in]
 * RETURNS
 *  int32_t
 *****************************************************************************/
static int32_t main_screen_get_index(int32_t x, int32_t y)
{
    int32_t ui_index = -1;
    if (x > main_screen_cntx.left_gap && x < main_screen_cntx.LCD_WIDTH - main_screen_cntx.right_gap) {
        if (y > main_screen_cntx.top_gap + 1) {
            ui_index = (y - main_screen_cntx.top_gap)/main_screen_cntx.item_height;
        }
    }

    if (ui_index >= main_screen_cntx.curr_item_num + main_screen_cntx.has_previous_page + main_screen_cntx.has_next_page) {
        return -1;
    } 

    if (ui_index == 0 && main_screen_cntx.has_previous_page) {
        return -2;
    }

    if (ui_index == main_screen_cntx.one_screen_item_num - 1 && main_screen_cntx.has_next_page) {
        return -3;
    }

    ui_index -= main_screen_cntx.has_previous_page;

    return main_screen_cntx.start_item + ui_index;
}

/*****************************************************************************
 * FUNCTION
 *  show_main_screen
 * DESCRIPTION
 *  show main screen
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void show_main_screen()
{
    static int32_t is_init;
//	static int32_t temp_index;
	static int32_t is_wf_screen;
    curr_event_handler = main_screen_event_handle;
//    demo_ui_register_touch_event_callback(main_screen_pen_event_handler, NULL);
	demo_ui_register_keypad_event_callback(main_screen_keypad_event_handler, NULL);

    if (!is_init) {
        is_init = 1;
        bsp_lcd_init(0x0000);
        bsp_backlight_init();
		bsp_backlight_init_display_pwm();
        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_HEIGHT, &LCD_CURR_HEIGHT);
        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_WIDTH, &LCD_CURR_WIDTH);
    }


    gdi_font_engine_set_font_size(GDI_FONT_ENGINE_FONT_LARGE);

    main_screen_cntx_init();
	
    if (!is_wf_screen) {
		is_wf_screen = 1;
		gdi_draw_filled_rectangle(0,0,240 * RESIZE_RATE - 1,240 * RESIZE_RATE - 1,0);
		gdi_image_draw_by_id(0, 0, IMAGE_ID_ZBG_06_BMP); //logo by chen
		gdi_lcd_update_screen(0, 0, 240 * RESIZE_RATE - 1, 240 * RESIZE_RATE - 1);
		vTaskDelay(1000);
	}
    GRAPHICLOG("show_main_screen");
//    main_screen_draw();
	tui_main_screen_draw();
	show_watchface_timer_init(10);

/*
	if (!is_wf_screen) {
//	curr_event_handler = demo_item[4].event_handle_f;
		is_wf_screen = 1;
		if (demo_item[3].show_screen_f) {
	     	demo_item[3].show_screen_f();
			GRAPHICLOG("show_main_wf");
	 	}
	}
*/
}

