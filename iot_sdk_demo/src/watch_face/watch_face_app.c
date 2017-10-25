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

/*User self log api, to avoid wake log task*/

#include <stdarg.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "wf_image.h"
#include "hal_rtc.h"
#include "mt25x3_hdk_lcd.h"
#include "mt25x3_hdk_backlight.h"
#include "syslog.h"
#include "main_screen.h"
#include "hal_sleep_manager.h"
#include "task_def.h"
#include "memory_attribute.h"
#include "bsp_ctp.h"

//add by chenchen
#include "hal_keypad.h"
#include "gdi_font_engine.h"
#include "gdi.h"
#include "battery_management.h"
#include "timers.h"
#include "hal_display_pwm.h"
#include "hal_display_pwm_internal.h"
#include "task.h"


#define LCD_WIDTH   (240)
#define LCD_HEIGHT (240)

#include "custom_image_data_resource.h"
#include "custom_resource_def.h"

extern gdi_resource_custom_image_t	gdi_resource_custom_image_names[];
extern gdi_resource_custom_image_map_t gdi_resource_custom_image_id_map[];

extern uint8_t sdkdemo_sleep_handle;


#define IMG_UPDATE_HEIGHT 49
#define IMG_UPDATE_WIDTH 320  /* Set to the MAX LCD size for dynamic adjust the LCD size*/
/*40*4+16+24*2*/
#define NUM_OF_DIGIT 5
#define WF_EVENT_RTC 1


typedef enum{
    WF_APP_LCD_TYPE_HEIGHT,
    WF_APP_LCD_TYPE_WIDTH
}wf_app_lcd_type_t;

static QueueHandle_t g_wtf_queue_handle;
static bool g_wf_is_show_screen;
static bool g_wf_is_task_need_delete;
static bool g_wf_is_lcd_need_init;

ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN uint8_t g_wf_time_update_area_img[IMG_UPDATE_HEIGHT * IMG_UPDATE_WIDTH/8];
static uint8_t g_wf_witdh_offset;

TimerHandle_t vPopupTimer = NULL;
TimerHandle_t vBacklightTimer = NULL;

uint32_t g_wf_index_color_table[16] = 
{
	0x0,
	0xFFFF,
	0x7E0,
	0x1F,
	0x4208,
	0x8410,
	0xFFFF,
	0xFF00,
	0x0,
	0xF800,
	0x7E0,
	0x1F,
	0x4208,
	0x8410,
	0xFFFF,
	0xFF00
};

void wf_app_task(void *arg);
static void wf_app_update_time(hal_rtc_time_t *curr_time);
static uint32_t wf_app_get_lcd_size(wf_app_lcd_type_t type);
static void wf_app_rtc_time_callback(void *user_data);
static void wf_app_log(const char *format, ...);

void wf_app_rtc_time_callback(void *user_data)
{
     uint8_t event;
     event = WF_EVENT_RTC;
     BaseType_t xHigherPriorityTaskWoken;
	 //LOG_I(common,"app task receive rtc event");
     xQueueSendFromISR(g_wtf_queue_handle, (void *) &event , &xHigherPriorityTaskWoken);
     
     // Now the buffer is empty we can switch context if necessary.
     if( xHigherPriorityTaskWoken ) {
         // Actual macro used here is port specific.
         portYIELD_FROM_ISR (xHigherPriorityTaskWoken);
     }

}


static void wf_app_combine_buffer(uint8_t *dst, uint8_t *src, uint8_t width)
{
    uint32_t i;
    uint32_t lcd_width = wf_app_get_lcd_size(WF_APP_LCD_TYPE_WIDTH);
    for (i = 0; i < IMG_UPDATE_HEIGHT;i++) {
        memcpy(dst + g_wf_witdh_offset + i * lcd_width/8, src + i * width/8, width/8);
    }
    
}

static void wf_app_combine_small_buffer(uint8_t *dst, uint8_t *src, uint8_t width)
{
    uint32_t i;
    uint32_t lcd_width = wf_app_get_lcd_size(WF_APP_LCD_TYPE_WIDTH);

    for (i = 0; i < 20;i++) {
        memset(dst + g_wf_witdh_offset + i * lcd_width/8, 0x0, width/8);
    }
    for (i = 20; i < 49; i++) {
        memcpy(dst + g_wf_witdh_offset + i * lcd_width/8, src + (i-20) * width/8, width/8);
    }
    
}


static uint8_t *wf_app_get_number_buffer(uint8_t num)
{
    uint8_t *img_ptr = NULL;
    switch (num) {
        case 0:
        	   img_ptr = big_number_0;
        	   break;
        case 1:
        	   img_ptr = big_number_1;
        	   break;
        case 2:
        	   img_ptr = big_number_2;
        	   break;
        case 3:
        	   img_ptr = big_number_3;
        	   break;
        case 4:
        	   img_ptr = big_number_4;
        	   break;
        case 5:
        	   img_ptr = big_number_5;
        	   break;
        case 6:
        	   img_ptr = big_number_6;
        	   break;
        case 7:
        	   img_ptr = big_number_7;
        	   break;
        case 8:
        	   img_ptr = big_number_8;
        	   break;
        case 9:
        	   img_ptr =  big_number_9;
        	   break;
        case 0xff:
        	   img_ptr  = big_number_colon;
        	   break;
        default:
                   //LOG_I(common, "wrong big number");
                   img_ptr = big_number_0;
        	   break;
    }
    return img_ptr;
}

static uint8_t *wf_app_get_small_number_buffer(uint8_t num)
{
    uint8_t *img_ptr = NULL;
    switch (num) {
        case 0:
        	   img_ptr = small_number_0;
        	   break;
        case 1:
        	   img_ptr = small_number_1;
        	   break;
        case 2:
        	   img_ptr = small_number_2;
        	   break;
        case 3:
        	   img_ptr = small_number_3;
        	   break;
        case 4:
        	   img_ptr = small_number_4;
        	   break;
        case 5:
        	   img_ptr = small_number_5;
        	   break;
        case 6:
        	   img_ptr = small_number_6;
        	   break;
        case 7:
        	   img_ptr = small_number_7;
        	   break;
        case 8:
        	   img_ptr = small_number_8;
        	   break;
        case 9:
        	   img_ptr =  small_number_9;
        	   break; 
        default:
                   //LOG_I(common, "wrong small number");
                   img_ptr = small_number_0;
        	   break;
    }
    return img_ptr;
}
static uint8_t *wf_app_get_time_img_buffer(hal_rtc_time_t *time)
{
    uint8_t *temp_ptr;
    uint8_t temp_num;
    uint32_t lcd_width = wf_app_get_lcd_size(WF_APP_LCD_TYPE_WIDTH);

    if (lcd_width == 240) {
        g_wf_witdh_offset = 1;
    } else if (lcd_width == 320) {
        g_wf_witdh_offset = 5;
    } else {
        LOG_E(common, "wrongly lcd size");
        return NULL;
    }

    temp_num = time->rtc_hour/10;
    temp_ptr = wf_app_get_number_buffer(temp_num);
    wf_app_combine_buffer(g_wf_time_update_area_img, temp_ptr, 40);
    g_wf_witdh_offset += 5;

    temp_num = time->rtc_hour%10;
    temp_ptr = wf_app_get_number_buffer(temp_num);
    wf_app_combine_buffer(g_wf_time_update_area_img, temp_ptr, 40);
    g_wf_witdh_offset += 5;

    temp_num = 0xff; /*":"*/
    temp_ptr = wf_app_get_number_buffer(temp_num);
    wf_app_combine_buffer(g_wf_time_update_area_img, temp_ptr, 16);
    g_wf_witdh_offset += 2;

    temp_num = time->rtc_min/10;
    temp_ptr = wf_app_get_number_buffer(temp_num);
    wf_app_combine_buffer(g_wf_time_update_area_img, temp_ptr, 40);
    g_wf_witdh_offset += 5;

    temp_num = time->rtc_min%10;
    temp_ptr = wf_app_get_number_buffer(temp_num);
    wf_app_combine_buffer(g_wf_time_update_area_img, temp_ptr, 40);
    g_wf_witdh_offset += 5;
    
    temp_num = time->rtc_sec/10;
    temp_ptr = wf_app_get_small_number_buffer(temp_num);
    wf_app_combine_small_buffer(g_wf_time_update_area_img, temp_ptr, 24);
    g_wf_witdh_offset += 3;

    temp_num = time->rtc_sec%10;
    temp_ptr = wf_app_get_small_number_buffer(temp_num);
    wf_app_combine_small_buffer(g_wf_time_update_area_img, temp_ptr, 24);
  
    return g_wf_time_update_area_img;
    
    
}

static void wf_app_log(const char *format, ...)
 {
     char buffer[124];   /* Output buffer */
     va_list args;
 
     va_start(args, format);
     vsnprintf(buffer, sizeof(buffer), format, args);
     va_end(args);
     //LOG_I(common,"%s\n", buffer);
 }


static uint32_t wf_app_get_lcd_size(wf_app_lcd_type_t type)
{
    uint32_t height, width;
    if (type == WF_APP_LCD_TYPE_WIDTH) {
        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_WIDTH, &width);
        //LOG_I(common, "width = %d", width);
        return width;
    } else if (type == WF_APP_LCD_TYPE_HEIGHT) {
        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_HEIGHT, &height);
        //LOG_I(common, "height = %d", height);
        return height;
    } else {
        LOG_E(common, "wrongly lcd type");
        return 0;
    }
   
}
 
 static void wf_app_rtc_init(void)
 {
     hal_rtc_status_t result = hal_rtc_init();
     if (result != HAL_RTC_STATUS_OK) {
         wf_app_log("rtc init failed : %d", result);
         return;
     }

 /* Watch face need use RTC to register notification for waking up every 1 second.
  * If this option disabled, watch face can't work. */    
 #ifdef HAL_RTC_FEATURE_TIME_CALLBACK    
     hal_rtc_set_time_callback(wf_app_rtc_time_callback, NULL);
     hal_rtc_set_time_notification_period(HAL_RTC_TIME_NOTIFICATION_EVERY_SECOND);
 #endif
 }
 

void wf_app_init(void)
{

    g_wtf_queue_handle =  xQueueCreate(1, sizeof(uint8_t));
    //xTaskCreate(wf_app_task, "wf_task", 1024, NULL, 1, NULL);

}

void vBacklightTimerCallback( TimerHandle_t xTimer )
{
//	bsp_backlight_deinit();
	g_wf_is_lcd_need_init = true;

    hal_display_pwm_deinit();
	hal_display_pwm_init(HAL_DISPLAY_PWM_CLOCK_26MHZ);
	hal_display_pwm_set_duty(0);
	bsp_lcd_enter_idle();
	/* If the macro is enabled, Watch face app will power off CTP to reduce leakage. 
	 * User can close it for watch face app. */

	//task_def_delete_wo_curr_task();
	hal_sleep_manager_unlock_sleep(sdkdemo_sleep_handle);

}

void backlight_timer_stop(void)
{
	if (vBacklightTimer && (xTimerIsTimerActive(vBacklightTimer) != pdFALSE)){
		xTimerStop(vBacklightTimer, 0);
	}
}

void backlight_timer_init(uint32_t time)
{
    if (vBacklightTimer && (xTimerIsTimerActive(vBacklightTimer) != pdFALSE)) {
        xTimerStop(vBacklightTimer, 0);
    } else {
		vBacklightTimer = xTimerCreate( "vBacklightTimer",           // Just a text name, not used by the kernel.
                                      ( time*1000 / portTICK_PERIOD_MS), // The timer period in ticks.
                                      pdFALSE,                    // The timer is a one-shot timer.
                                      0,                          // The id is not used by the callback so can take any value.
                                      vBacklightTimerCallback     // The callback function that switches the LCD back-light off.
                                   );
    }
	xTimerStart(vBacklightTimer, 0);
}



void vPopupTimerCallback( TimerHandle_t xTimer )
{
	g_wf_is_show_screen = true;
	LOG_I(common, "chenchen vPopupTimerCallback true ");
	pop_timer_stop();
}

void pop_timer_stop(void)
{
    if (vPopupTimer && (xTimerIsTimerActive(vPopupTimer) != pdFALSE)){
		xTimerStop(vPopupTimer, 0);
    }
}


void pop_timer_init(uint32_t time)
{
    if (vPopupTimer && (xTimerIsTimerActive(vPopupTimer) != pdFALSE)) {
        xTimerStop(vPopupTimer, 0);
    } else {
		vPopupTimer = xTimerCreate( "vPopupTimer",           // Just a text name, not used by the kernel.
                                      ( time*1000 / portTICK_PERIOD_MS), // The timer period in ticks.
                                      pdFALSE,                    // The timer is a one-shot timer.
                                      0,                          // The id is not used by the callback so can take any value.
                                      vPopupTimerCallback     // The callback function that switches the LCD back-light off.
                                   );
    }
	xTimerStart(vPopupTimer, 0);
}



static void wf_show_pop_image(void)
{
	static uint8_t layer_buffer[LCD_WIDTH * LCD_HEIGHT * 2];
	
	if (g_wf_is_show_screen){
		gdi_init(LCD_WIDTH, LCD_HEIGHT, GDI_COLOR_FORMAT_16, layer_buffer);
		gdi_draw_filled_rectangle(0, 0, 320 - 1, 320 - 1, gdi_get_color_from_argb(0, 0, 0, 0)); // Clear the screen to black.


		gdi_image_draw_by_id(15, 39, IMAGE_ID_POP_UP_BMP);
//		gdi_image_draw_by_id(140, 200, IMAGE_ID_IDLE_GPS_BMP);

		gdi_lcd_update_screen(0, 30, 320 - 1, 205);
		g_wf_is_show_screen = false;
	}

}

static void wf_need_lcd_init(void)
{
	hal_sleep_manager_lock_sleep(sdkdemo_sleep_handle);

	hal_display_pwm_deinit();
	hal_display_pwm_init(HAL_DISPLAY_PWM_CLOCK_26MHZ);
	hal_display_pwm_set_duty(20);
	bsp_lcd_exit_idle();
	//bsp_backlight_init();
}

static void wf_need_bl_on(void)
{
	hal_display_pwm_deinit();
	hal_display_pwm_init(HAL_DISPLAY_PWM_CLOCK_26MHZ);
	hal_display_pwm_set_duty(20);
}

static void wf_app_powerkey_event_handler(hal_keypad_powerkey_event_t* powerkey_event,void* user_data)
{
	LOG_I(common, "chenchen wf_app_powerkey  %d",powerkey_event->key_data);

	if (powerkey_event->state == 0){
		return;
	} else if (powerkey_event->state == 1){
		if (g_wf_is_lcd_need_init){
			g_wf_is_lcd_need_init = false;
			wf_need_lcd_init();
		} else {
			wf_need_bl_on();
		}
		if( xTimerReset( vBacklightTimer, 100 ) != pdPASS ) {
			LOG_I(common, "chenchen wf powerkey_xTimerReset fail");
		}
		LOG_I(common, "chenchen powerkey  %d",powerkey_event->key_data);
	} else if (powerkey_event->state == 2){
			hal_rtc_set_time_notification_period(HAL_RTC_TIME_NOTIFICATION_NONE);
			hal_sleep_manager_enter_power_off_mode();

	}
}

static void wf_app_keypad_event_handler(hal_keypad_event_t* keypad_event,void* user_data)
{
    static int32_t temp_index;
/*
	keyvalue
	13 0xd ---enter
	14 0xe ---back
	17 0x11---up
	18 0x12---down
*/

	LOG_I(common, "chenchen wf_app_keypad handler %d",keypad_event->key_data);
	if (g_wf_is_lcd_need_init){
		g_wf_is_lcd_need_init = false;
		wf_need_lcd_init();
	} else {
		wf_need_bl_on();
	}

	if( xTimerReset( vBacklightTimer, 100 ) != pdPASS ) {
		LOG_I(common, "chenchen wf_xTimerReset fail");
	}
	vTaskDelay(100);

	temp_index = 0;
	if (keypad_event->state == 1){
		return;
	} else {
		if (keypad_event->key_data == 0xd && keypad_event->state == 0){
			temp_index = 1;
		} else if (keypad_event->key_data == 0xe && keypad_event->state == 0){
			temp_index = 2;
		} else if (keypad_event->key_data == 0x11 && keypad_event->state == 0){
			temp_index = 3;
		} else if (keypad_event->key_data == 0x12 && keypad_event->state == 0){
			temp_index = 4;
		}
	}
	
	switch (temp_index){
		case 1:
			g_wf_is_show_screen = false;
			pop_timer_stop();
			backlight_timer_stop();
			show_main_screen();
			return;
		case 2:
			g_wf_is_show_screen = false;
			pop_timer_stop();
			backlight_timer_stop();
			show_main_screen();

			return;
		case 3:
			wf_show_pop_image();
			pop_timer_init(5);

			break;
		case 4:
			wf_show_pop_image();
			pop_timer_init(5);

			break;
		default:
            break;
		}
//	g_wf_is_show_screen = false;
//	bsp_lcd_clear_screen(0);
//    show_main_screen();



}

//add by chenchen
void wf_event_handler(message_id_enum event_id, int32_t param1, void* param2)
{
	LOG_E(common, "chenchen wf event handler show");
	//wf_app_task_enable_show();
}

static uint16_t wf_get_year_time_img_number(uint16_t num)
{
	uint16_t img_ptr;
    switch (num) {
        case 0:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_0_BMP;
        	   break;
        case 1:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_1_BMP;
        	   break;
        case 2:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_2_BMP;
        	   break;
        case 3:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_3_BMP;
        	   break;
        case 4:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_4_BMP;
        	   break;
        case 5:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_5_BMP;
        	   break;
        case 6:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_6_BMP;
        	   break;
        case 7:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_7_BMP;
        	   break;
        case 8:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_8_BMP;
        	   break;
        case 9:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_9_BMP;
        	   break;
        default:
               img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_0_BMP;
        	   break;
    }
    return img_ptr;

}

static uint16_t wf_get_mon_time_img_number(uint16_t num)
{
	uint16_t img_ptr;
    switch (num) {
        case 0:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_0_BMP;
        	   break;
        case 1:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_1_BMP;
        	   break;
        case 2:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_2_BMP;
        	   break;
        case 3:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_3_BMP;
        	   break;
        case 4:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_4_BMP;
        	   break;
        case 5:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_5_BMP;
        	   break;
        case 6:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_6_BMP;
        	   break;
        case 7:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_7_BMP;
        	   break;
        case 8:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_8_BMP;
        	   break;
        case 9:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_9_BMP;
        	   break;
        default:
               img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_0_BMP;
        	   break;
    }
    return img_ptr;

}

static uint16_t wf_get_day_time_img_number(uint16_t num)
{
	uint16_t img_ptr;
    switch (num) {
        case 0:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_0_BMP;
        	   break;
        case 1:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_1_BMP;
        	   break;
        case 2:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_2_BMP;
        	   break;
        case 3:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_3_BMP;
        	   break;
        case 4:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_4_BMP;
        	   break;
        case 5:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_5_BMP;
        	   break;
        case 6:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_6_BMP;
        	   break;
        case 7:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_7_BMP;
        	   break;
        case 8:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_8_BMP;
        	   break;
        case 9:
        	   img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_9_BMP;
        	   break;
        default:
               img_ptr = IMAGE_ID_IDLE_DATE_NUMBER_0_BMP;
        	   break;
    }
    return img_ptr;

}

static uint16_t wf_get_week_time_img_number(uint16_t num)
{
	uint16_t img_ptr;
    switch (num) {
        case 0:
        	   img_ptr = IMAGE_ID_IDLE_WEEK_SUN_CN_BMP;
        	   break;
        case 1:
        	   img_ptr = IMAGE_ID_IDLE_WEEK_MON_CN_BMP;
        	   break;
        case 2:
        	   img_ptr = IMAGE_ID_IDLE_WEEK_TUES_CN_BMP;
        	   break;
        case 3:
        	   img_ptr = IMAGE_ID_IDLE_WEEK_WED_CN_BMP;
        	   break;
        case 4:
        	   img_ptr = IMAGE_ID_IDLE_WEEK_THUR_CN_BMP;
        	   break;
        case 5:
        	   img_ptr = IMAGE_ID_IDLE_WEEK_FRI_CN_BMP;
        	   break;
        case 6:
        	   img_ptr = IMAGE_ID_IDLE_WEEK_SAT_CN_BMP;
        	   break;
        default:
               img_ptr = IMAGE_ID_BATTERY_NUMBER_0_BMP;
        	   break;
    }
    return img_ptr;

}

static uint16_t wf_get_hour_time_img_number(uint16_t num)
{
	uint16_t img_ptr;
    switch (num) {
        case 0:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_HOUR_0_BMP;
        	   break;
        case 1:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_HOUR_1_BMP;
        	   break;
        case 2:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_HOUR_2_BMP;
        	   break;
        case 3:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_HOUR_3_BMP;
        	   break;
        case 4:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_HOUR_4_BMP;
        	   break;
        case 5:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_HOUR_5_BMP;
        	   break;
        case 6:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_HOUR_6_BMP;
        	   break;
        case 7:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_HOUR_7_BMP;
        	   break;
        case 8:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_HOUR_8_BMP;
        	   break;
        case 9:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_HOUR_9_BMP;
        	   break;
        default:
                   //LOG_I(common, "wrong big number");
               img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_HOUR_0_BMP;
        	   break;
    }
    return img_ptr;

}

static uint16_t wf_get_minute_time_img_number(uint16_t num)
{
	uint16_t img_ptr;
    switch (num) {
        case 0:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_MINUTE_0_BMP;
        	   break;
        case 1:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_MINUTE_1_BMP;
        	   break;
        case 2:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_MINUTE_2_BMP;
        	   break;
        case 3:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_MINUTE_3_BMP;
        	   break;
        case 4:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_MINUTE_4_BMP;
        	   break;
        case 5:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_MINUTE_5_BMP;
        	   break;
        case 6:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_MINUTE_6_BMP;
        	   break;
        case 7:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_MINUTE_7_BMP;
        	   break;
        case 8:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_MINUTE_8_BMP;
        	   break;
        case 9:
        	   img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_MINUTE_9_BMP;
        	   break;
        default:
                   //LOG_I(common, "wrong big number");
               img_ptr = IMAGE_ID_IDLE_TIME_NUMBER_MINUTE_0_BMP;
        	   break;
    }
    return img_ptr;

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

static void wf_show_test_image(void)
{
	int16_t bat_num1,bat_num2,bat_img;
	int32_t capacity;
	static uint8_t layer_buffer[LCD_WIDTH * LCD_HEIGHT * 2];
	if (g_wf_is_show_screen){
		gdi_init(LCD_WIDTH, LCD_HEIGHT, GDI_COLOR_FORMAT_16, layer_buffer);
		gdi_draw_filled_rectangle(0, 0, LCD_WIDTH, LCD_HEIGHT, gdi_get_color_from_argb(0, 0, 0, 0)); // Clear the screen to black.
	

		capacity = battery_management_get_battery_property(BATTERY_PROPERTY_CAPACITY);
		if (capacity == 100) {
			gdi_image_draw_by_id(90, 20, IMAGE_ID_BATTERY_FULL_BMP);
			gdi_image_draw_by_id(130, 21, IMAGE_ID_BATTERY_NUMBER_1_BMP);
			gdi_image_draw_by_id(140, 21, IMAGE_ID_BATTERY_NUMBER_0_BMP);
			gdi_image_draw_by_id(150, 21, IMAGE_ID_BATTERY_NUMBER_0_BMP);
			gdi_image_draw_by_id(160, 21, IMAGE_ID_BATTERY_NUMBER_PERCENT_BMP);
		
		} else if (capacity == 0) {
			gdi_image_draw_by_id(90, 20, IMAGE_ID_BATTERY_EMPTY_BMP);
		} else {
			bat_num1 = capacity / 10;
			bat_num2 = capacity % 10;
			bat_num1 = main_get_battery_img_number(bat_num1);
			bat_num2 = main_get_battery_img_number(bat_num2);
			bat_img = main_get_battery_show_img(capacity);
		
			gdi_image_draw_by_id(90, 20, bat_img);
			gdi_image_draw_by_id(130, 21, bat_num1);
			gdi_image_draw_by_id(140, 21, bat_num2);
			gdi_image_draw_by_id(150, 21, IMAGE_ID_BATTERY_NUMBER_PERCENT_BMP);
		}


		gdi_image_draw_by_id(90, 200, IMAGE_ID_IDLE_ALARM_BMP);
		gdi_image_draw_by_id(140, 200, IMAGE_ID_IDLE_GPS_BMP);

		gdi_lcd_update_screen(0, 0, LCD_WIDTH, LCD_HEIGHT);
		}
}

void wf_app_task_enable_show(void)
{
    bsp_lcd_clear_screen(0);
	demo_ui_register_keypad_event_callback(wf_app_keypad_event_handler, NULL);
	demo_ui_register_powerkey_event_callback(wf_app_powerkey_event_handler, NULL);


    g_wf_is_show_screen = true;
    g_wf_is_task_need_delete = true;
	g_wf_is_lcd_need_init = false;
    xTaskCreate(wf_app_task, WF_APP_TASK_NAME, WF_APP_TASK_STACKSIZE/(( uint32_t )sizeof( StackType_t )), NULL, WF_APP_TASK_PRIO, NULL);
}

//extern uint8_t sdkdemo_sleep_handle;

void wf_app_task(void *arg)
{
    uint8_t event;
    hal_rtc_time_t time;
    wf_app_rtc_init();
    while(1) { /*receive message/semphore from RTC LISR*/
    	   if ( xQueueReceive(g_wtf_queue_handle, &event, portMAX_DELAY) == pdPASS) {
               //LOG_I(common,"app task receive event %d", event);
            if (event == WF_EVENT_RTC) {
                if (g_wf_is_task_need_delete == true) {
#if 0
					bsp_backlight_deinit();
                    bsp_lcd_enter_idle();
/* If the macro is enabled, Watch face app will power off CTP to reduce leakage. 
 * User can close it for watch face app. */
#ifdef MTK_CTP_ENABLE
                    bsp_ctp_power_on(false);
#endif
                    //task_def_delete_wo_curr_task();
				    hal_sleep_manager_unlock_sleep(sdkdemo_sleep_handle);
#endif
					backlight_timer_init(10);

                    g_wf_is_task_need_delete  =  false;
					//g_wf_is_lcd_need_init = true;
                }
			//	wf_show_test_image();
                hal_rtc_get_time(&time);
                wf_app_update_time(&time);
            }
    	   }
      
    }

}

static void wf_app_set_defalut_time(void)
{
	hal_rtc_time_t time;

	time.rtc_year = 17;
    time.rtc_mon = 10;
    time.rtc_day = 18;
	time.rtc_week = 3;
    time.rtc_hour = 10;
    time.rtc_min = 0;
    time.rtc_sec = 0;

	hal_rtc_set_time(&time);

}

static hal_display_lcd_roi_output_t lcd_para_wf;
static hal_display_lcd_layer_input_t lcm_para_wf;

static void wf_app_update_time(hal_rtc_time_t *curr_time)
{
    uint8_t *img_ptr;
    uint32_t lcd_height = wf_app_get_lcd_size(WF_APP_LCD_TYPE_HEIGHT);
    uint32_t lcd_width = wf_app_get_lcd_size(WF_APP_LCD_TYPE_WIDTH);
	static uint8_t layer_time_buffer[LCD_WIDTH * LCD_HEIGHT * 2];
	uint16_t temp_img;
    uint16_t temp_num;
	int16_t bat_num1,bat_num2,bat_img;
	int32_t capacity;
	static int32_t is_set_time;
	static uint8_t layer_buffer[LCD_WIDTH * LCD_HEIGHT * 2];
    //LOG_I(common, "app task to draw screen %d", g_wf_is_show_screen);
/* iot_demo watch face
    if (g_wf_is_show_screen) {

    	  lcd_para_wf.target_start_x = 0;
    	  lcd_para_wf.target_start_y = (lcd_height - IMG_UPDATE_HEIGHT)/2;
    	  lcd_para_wf.target_end_x = lcd_width - 1;
    	  lcd_para_wf.target_end_y = (lcd_height - IMG_UPDATE_HEIGHT)/2+IMG_UPDATE_HEIGHT-1;
    	  lcd_para_wf.roi_offset_x = 0;
    	  lcd_para_wf.roi_offset_y = 0;
          lcd_para_wf.main_lcd_output = LCM_16BIT_16_BPP_RGB565_1;

    	  bsp_lcd_config_roi(&lcd_para_wf);
          bsp_lcd_set_index_color_table(g_wf_index_color_table);
    	  lcm_para_wf.source_key_flag= 0;
    	  lcm_para_wf.alpha_flag= 0;
    	  lcm_para_wf.color_format= HAL_DISPLAY_LCD_LAYER_COLOR_1BIT_INDEX;
    	  lcm_para_wf.alpha = 0;
    	  lcm_para_wf.rotate = HAL_DISPLAY_LCD_LAYER_ROTATE_0;
    	  lcm_para_wf.layer_enable= 0;
    	  lcm_para_wf.pitch = lcd_width/8;
    	  lcm_para_wf.row_size = IMG_UPDATE_HEIGHT;
    	  lcm_para_wf.column_size = lcd_width;
    	  lcm_para_wf.window_x_offset = 0;
    	  //lcm_para.window_y_offset = (240 - IMG_UPDATE_HEIGHT)/2;
          lcm_para_wf.window_y_offset = 0;

          memset(g_wf_time_update_area_img, 0x00, IMG_UPDATE_HEIGHT * lcd_width/8);
          img_ptr = wf_app_get_time_img_buffer(curr_time);
    	  lcm_para_wf.buffer_address = (uint32_t)img_ptr;

    	  bsp_lcd_config_layer(&lcm_para_wf);
    	  bsp_lcd_update_screen(lcd_para_wf.target_start_x, lcd_para_wf.target_start_y, lcd_para_wf.target_end_x, lcd_para_wf.target_end_y);
    }
*/
/*
	if (!is_set_time) {
		is_set_time = 1;
		wf_app_set_defalut_time();
		vTaskDelay(100);
	}
*/	
	if (g_wf_is_show_screen) {

		gdi_init(LCD_WIDTH, LCD_HEIGHT, GDI_COLOR_FORMAT_16, layer_buffer);
		gdi_draw_filled_rectangle(0, 0, LCD_WIDTH, LCD_HEIGHT, gdi_get_color_from_argb(0, 0, 0, 0)); // Clear the screen to black.

		temp_num = curr_time->rtc_year/10;
		temp_img = wf_get_year_time_img_number(temp_num);
		gdi_image_draw_by_id(45, 170, IMAGE_ID_IDLE_DATE_NUMBER_2_BMP);
		gdi_image_draw_by_id(55, 170, IMAGE_ID_IDLE_DATE_NUMBER_0_BMP);
		gdi_image_draw_by_id(65, 170, temp_img);
//		LOG_I(common, "chenchen wf_app_time year %d mon %d day %d\n",curr_time->rtc_year,curr_time->rtc_mon,curr_time->rtc_day);

		temp_num = curr_time->rtc_year%10;
		temp_img = wf_get_year_time_img_number(temp_num);
		gdi_image_draw_by_id(75, 170, temp_img);

		gdi_image_draw_by_id(85, 170, IMAGE_ID_IDLE_DATE_NUMBER_LINE_BMP);

		temp_num = curr_time->rtc_mon/10;
		temp_img = wf_get_mon_time_img_number(temp_num);
		gdi_image_draw_by_id(95, 170, temp_img);

		temp_num = curr_time->rtc_mon%10;
		temp_img = wf_get_mon_time_img_number(temp_num);
		gdi_image_draw_by_id(105, 170, temp_img);

		gdi_image_draw_by_id(115, 170, IMAGE_ID_IDLE_DATE_NUMBER_LINE_BMP);

		temp_num = curr_time->rtc_day/10;
		temp_img = wf_get_day_time_img_number(temp_num);
		gdi_image_draw_by_id(125, 170, temp_img);

		temp_num = curr_time->rtc_day%10;
		temp_img = wf_get_day_time_img_number(temp_num);
		gdi_image_draw_by_id(135, 170, temp_img);

		temp_num = curr_time->rtc_week;
		temp_img = wf_get_week_time_img_number(temp_num);
		gdi_image_draw_by_id(155, 170, temp_img);

/*------------------------------------------------------*/
		temp_num = curr_time->rtc_hour/10;
		temp_img = wf_get_hour_time_img_number(temp_num);
		gdi_image_draw_by_id(15, 75, temp_img);

		temp_num = curr_time->rtc_hour%10;
		temp_img = wf_get_hour_time_img_number(temp_num);
		gdi_image_draw_by_id(65, 75, temp_img);
		
		gdi_image_draw_by_id(120, 75, IMAGE_ID_IDLE_TIME_NUMBER_COLON_BMP);		

		temp_num = curr_time->rtc_min/10;
		temp_img = wf_get_minute_time_img_number(temp_num);
		gdi_image_draw_by_id(134, 75, temp_img);

		temp_num = curr_time->rtc_min%10;
		temp_img = wf_get_minute_time_img_number(temp_num);
		gdi_image_draw_by_id(184, 75, temp_img);


		capacity = battery_management_get_battery_property(BATTERY_PROPERTY_CAPACITY);
		if (capacity == 100) {
			gdi_image_draw_by_id(90, 20, IMAGE_ID_BATTERY_FULL_BMP);
			gdi_image_draw_by_id(130, 21, IMAGE_ID_BATTERY_NUMBER_1_BMP);
			gdi_image_draw_by_id(140, 21, IMAGE_ID_BATTERY_NUMBER_0_BMP);
			gdi_image_draw_by_id(150, 21, IMAGE_ID_BATTERY_NUMBER_0_BMP);
			gdi_image_draw_by_id(160, 21, IMAGE_ID_BATTERY_NUMBER_PERCENT_BMP);
		
		} else if (capacity == 0) {
			gdi_image_draw_by_id(90, 20, IMAGE_ID_BATTERY_EMPTY_BMP);
		} else {
			bat_num1 = capacity / 10;
			bat_num2 = capacity % 10;
			bat_num1 = main_get_battery_img_number(bat_num1);
			bat_num2 = main_get_battery_img_number(bat_num2);
			bat_img = main_get_battery_show_img(capacity);
		
			gdi_image_draw_by_id(90, 20, bat_img);
			gdi_image_draw_by_id(130, 21, bat_num1);
			gdi_image_draw_by_id(140, 21, bat_num2);
			gdi_image_draw_by_id(150, 21, IMAGE_ID_BATTERY_NUMBER_PERCENT_BMP);
		}



		gdi_image_draw_by_id(90, 200, IMAGE_ID_IDLE_ALARM_BMP);
		gdi_image_draw_by_id(140, 200, IMAGE_ID_IDLE_GPS_BMP);

		gdi_lcd_update_screen(0, 0, LCD_WIDTH, LCD_HEIGHT);


	}

}


