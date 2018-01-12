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
#include "stdint.h"
#include "stdbool.h"
#include <string.h>
#include "stdlib.h"
#include "memory_attribute.h"
#include "bsp_lcd.h"
#include "mt25x3_hdk_backlight.h"
#include "fota_demo.h"

#include "syslog.h"
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

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
} fota_screen_cntx;

void show_fota_screen(void);

void fota_event_handler(message_id_enum event_id, int32_t param1, void* param2)
{

}
static void fota_screen_cntx_init()
{
    if ((fota_screen_cntx.height == 0) && (fota_screen_cntx.width==0)) {

        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_HEIGHT, &(fota_screen_cntx.height));
        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_WIDTH, &(fota_screen_cntx.width));
//        LOG_I("width(%d), height(%d).\r\n", fota_screen_cntx.width, fota_screen_cntx.height);

        fota_screen_cntx.bg_color = 0;
        fota_screen_cntx.font_color = 0xFFFF;
        /* first */
        fota_screen_cntx.fota_title_x = 5;
        fota_screen_cntx.fota_title_y = 6;

        /* middle */
        fota_screen_cntx.hr_title_x = LEFT_GAP;
        fota_screen_cntx.hr_title_y = ITEM_HEIGHT*2 + fota_screen_cntx.fota_title_y;
        fota_screen_cntx.hrv_title_x = LEFT_GAP;
        fota_screen_cntx.hrv_title_y = ITEM_HEIGHT + fota_screen_cntx.hr_title_y;
        fota_screen_cntx.hrv_value_x = LEFT_GAP;
        fota_screen_cntx.hrv_value_y = ITEM_HEIGHT + fota_screen_cntx.hrv_title_y;

        /* end */
        fota_screen_cntx.bt_name_x = LEFT_GAP;
        fota_screen_cntx.bt_name_y = fota_screen_cntx.height - 6 - (ITEM_HEIGHT*3);
        fota_screen_cntx.bt_status_x = LEFT_GAP;
        fota_screen_cntx.bt_status_y = ITEM_HEIGHT*2 + fota_screen_cntx.bt_name_y;
        fota_screen_cntx.back_x1 = fota_screen_cntx.width-80;
        fota_screen_cntx.back_y1 = ITEM_HEIGHT*2 + fota_screen_cntx.bt_name_y;
        fota_screen_cntx.back_x2 = fota_screen_cntx.width-1;
        fota_screen_cntx.back_y2 = fota_screen_cntx.height-1;

		fota_screen_cntx.focus_point_index = 0;
		fota_screen_cntx.start_item = 0;
		fota_screen_cntx.one_screen_item_num = 2;
		fota_screen_cntx.total_item_num = 2;
	fota_screen_cntx.curr_item_num = 2;
    }

}

static uint8_t* fota_convert_string_to_wstring(char* string)
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

void show_fota_screen(void)
{
//	int32_t index = sensor_screen_cntx.start_item;
//   int32_t num = sensor_screen_cntx.curr_item_num;
    int32_t x,y;

	x = 40 * RESIZE_RATE;
	y = 50 * RESIZE_RATE;

	fota_screen_cntx_init();
	
	gdi_font_engine_display_string_info_t fota_string_info = {0};
    gdi_draw_filled_rectangle(0,0,fota_screen_cntx.width-1,fota_screen_cntx.height-1, fota_screen_cntx.bg_color);

    gdi_font_engine_size_t font = GDI_FONT_ENGINE_FONT_MEDIUM;
    gdi_font_engine_color_t text_color = {0, 255, 255, 255};//white color

    gdi_font_engine_set_font_size(font);
    gdi_font_engine_set_text_color(text_color);

    fota_string_info.baseline_height = -1;
    fota_string_info.x = fota_screen_cntx.fota_title_x;
    fota_string_info.y = fota_screen_cntx.fota_title_y;
    fota_string_info.string = fota_convert_string_to_wstring("FOTA..");
    fota_string_info.length = strlen("FOTA..");
    gdi_font_engine_display_string(&fota_string_info);

	gdi_lcd_update_screen(0,0,fota_screen_cntx.width-1,fota_screen_cntx.height-1);
}