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

#if defined(_MSC_VER)
#else
#include "stdio.h"
#endif



#include "gdi_font_engine.h"
#include "gdi.h"
//#include "graphic_interface.h"
#include "main_screen.h"
#include "bt_gap.h"
#include "sensor_demo.h"
#include "mt25x3_hdk_lcd.h"
//add by chen
#include "FreeRTOS.h"
#include "stdint.h"
#include "stdbool.h"
#include <string.h>
#include "stdlib.h"
#include "memory_attribute.h"
#include "bsp_lcd.h"
#include "mt25x3_hdk_backlight.h"
#include "about_screen.h"
#include "custom_image_data_resource.h"
#include "custom_resource_def.h"
#include "timers.h"
#include "nvdm.h"
#include "bt_system.h"


#include "syslog.h"
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#define LEFT_GAP 5
#define ITEM_HEIGHT 25

#define RESIZE_RATE LCD_CURR_HEIGHT/240
#define DEMO_ITEM_NAME_MAX_LEN 50
TimerHandle_t vAboutWatchfaceTimer = NULL;

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
} about_screen_cntx;

void show_about_screen(void);

void about_screen_event_handler(message_id_enum event_id, int32_t param1, void* param2)
{

}

void vAboutWatchfaceTimerCallback( TimerHandle_t xTimer )
{
	wf_app_task_enable_show();

}

void show_aboutwatchface_timer_stop(void)
{
    if (vAboutWatchfaceTimer && (xTimerIsTimerActive(vAboutWatchfaceTimer) != pdFALSE)) {
        xTimerStop(vAboutWatchfaceTimer, 0);
    }

}

void show_aboutwatchface_timer_init(uint32_t time)
{
    if (vAboutWatchfaceTimer && (xTimerIsTimerActive(vAboutWatchfaceTimer) != pdFALSE)) {
        xTimerStop(vAboutWatchfaceTimer, 0);
    } else {
		vAboutWatchfaceTimer = xTimerCreate( "vAboutWatchfaceTimer",           // Just a text name, not used by the kernel.
                                      ( time*1000 / portTICK_PERIOD_MS), // The timer period in ticks.
                                      pdFALSE,                    // The timer is a one-shot timer.
                                      0,                          // The id is not used by the callback so can take any value.
                                      vAboutWatchfaceTimerCallback     // The callback function that switches the LCD back-light off.
                                   );
    }
	xTimerStart(vAboutWatchfaceTimer, 0);
}

static void about_screen_cntx_init()
{
    if ((about_screen_cntx.height == 0) && (about_screen_cntx.width==0)) {

        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_HEIGHT, &(about_screen_cntx.height));
        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_WIDTH, &(about_screen_cntx.width));
//        LOG_I("width(%d), height(%d).\r\n", about_screen_cntx.width, about_screen_cntx.height);

        about_screen_cntx.bg_color = 0;
        about_screen_cntx.font_color = 0xFFFF;
        /* first */
        about_screen_cntx.fota_title_x = 5;
        about_screen_cntx.fota_title_y = 6;

        /* middle */
        about_screen_cntx.hr_title_x = LEFT_GAP;
        about_screen_cntx.hr_title_y = ITEM_HEIGHT*2 + about_screen_cntx.fota_title_y;
        about_screen_cntx.hrv_title_x = LEFT_GAP;
        about_screen_cntx.hrv_title_y = ITEM_HEIGHT + about_screen_cntx.hr_title_y;
        about_screen_cntx.hrv_value_x = LEFT_GAP;
        about_screen_cntx.hrv_value_y = ITEM_HEIGHT + about_screen_cntx.hrv_title_y;

        /* end */
        about_screen_cntx.bt_name_x = LEFT_GAP;
        about_screen_cntx.bt_name_y = about_screen_cntx.height - 6 - (ITEM_HEIGHT*3);
        about_screen_cntx.bt_status_x = LEFT_GAP;
        about_screen_cntx.bt_status_y = ITEM_HEIGHT*2 + about_screen_cntx.bt_name_y;
        about_screen_cntx.back_x1 = about_screen_cntx.width-80;
        about_screen_cntx.back_y1 = ITEM_HEIGHT*2 + about_screen_cntx.bt_name_y;
        about_screen_cntx.back_x2 = about_screen_cntx.width-1;
        about_screen_cntx.back_y2 = about_screen_cntx.height-1;

		about_screen_cntx.focus_point_index = 0;
		about_screen_cntx.start_item = 0;
		about_screen_cntx.one_screen_item_num = 2;
		about_screen_cntx.total_item_num = 2;
		about_screen_cntx.curr_item_num = 2;
    }

}

static uint8_t* about_convert_string_to_wstring(char* string)
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

static void about_screen_need_lcd_init(void)
{
	hal_display_pwm_deinit();
	hal_display_pwm_init(HAL_DISPLAY_PWM_CLOCK_26MHZ);
	hal_display_pwm_set_duty(20);

}

static void about_screen_keypad_event_handler(hal_keypad_event_t* keypad_event,void* user_data)
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
		about_screen_need_lcd_init();
		GRAPHICLOG("[chenchen about_screen_keypad_event_handler key state=%d, position=%d\r\n", (int)keypad_event->state, (int)keypad_event->key_data);
		if( xTimerReset( vAboutWatchfaceTimer, 100 ) != pdPASS ) {
		LOG_I(common, "chenchen show about screen timer fail");
		}
		
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
				show_aboutwatchface_timer_stop();
				show_main_screen();
				return;
			default:
				break;
	
		}


}

void  show_about_screen(void)
{
    int32_t x,y;
    uint8_t bt_buffer[18] = {0};
    uint32_t size = 12;
    nvdm_status_t status;

	x = 40 * RESIZE_RATE;
	y = 30 * RESIZE_RATE;

	about_screen_cntx_init();
	demo_ui_register_keypad_event_callback(about_screen_keypad_event_handler, NULL);	
 	show_aboutwatchface_timer_init(10);

	status = nvdm_read_data_item("BT", "address", bt_buffer, &size);
	if (NVDM_STATUS_OK == status) {
		LOG_I(common, "[about]Read from NVDM:%s\n", bt_buffer);

	}

	gdi_font_engine_display_string_info_t about_string_info = {0};
    gdi_draw_filled_rectangle(0,0,about_screen_cntx.width-1,about_screen_cntx.height-1, about_screen_cntx.bg_color);

    gdi_font_engine_size_t font = GDI_FONT_ENGINE_FONT_SMALL;
    gdi_font_engine_color_t text_color = {0, 255, 255, 255};//white color

    gdi_font_engine_set_font_size(font);
    gdi_font_engine_set_text_color(text_color);
	
//	gdi_image_draw_by_id(0, 0, IMAGE_ID_ZBG_02_BMP);

	
	uint8_t version[10]={0x48,0x72,0x2C,0x67,0x00};

	about_string_info.baseline_height = -1;
    about_string_info.x = x;
    about_string_info.y = y;
    about_string_info.string = version;
    about_string_info.length = 4;
    gdi_font_engine_display_string(&about_string_info);

    about_string_info.baseline_height = -1;
    about_string_info.x = x;
    about_string_info.y = y + 40;
    about_string_info.string = about_convert_string_to_wstring("v1.0");
    about_string_info.length = strlen("v1.0");
    gdi_font_engine_display_string(&about_string_info);


	uint8_t bt_addr[10]={0xDD,0x84,0x59,0x72,0x30,0x57,0x40,0x57,0x00};

	about_string_info.baseline_height = -1;
    about_string_info.x = x;
    about_string_info.y = y + 80;
    about_string_info.string = bt_addr;
    about_string_info.length = 4;
    gdi_font_engine_display_string(&about_string_info);

    about_string_info.baseline_height = -1;
    about_string_info.x = x;
    about_string_info.y = y + 120;
    about_string_info.string = about_convert_string_to_wstring((char*)bt_buffer);
    about_string_info.length = strlen((char*)bt_buffer);
    gdi_font_engine_display_string(&about_string_info);

	gdi_lcd_update_screen(0,0,about_screen_cntx.width-1,about_screen_cntx.height-1);
}

