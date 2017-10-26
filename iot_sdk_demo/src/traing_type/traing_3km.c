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
#include "gnss_app.h"
#include "task.h"
#include "gnss_log.h"

#include "syslog.h"
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include "traing_3km.h"

#include "FreeRTOS.h"
#include "task.h"
#include "task_def.h"
#include <math.h>
#include "hal.h"

#define LEFT_GAP 5
#define ITEM_HEIGHT 25

#define RESIZE_RATE LCD_CURR_HEIGHT/240
#define DEMO_ITEM_NAME_MAX_LEN 50
static bool g_tt_is_3km_start;

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

void running_3km_event_handler(message_id_enum event_id, int32_t param1, void* param2);
static TaskHandle_t gnss_task_handle;

int8_t lat_temp[15] = "\0";
int8_t lng_temp[15] = "\0";
double distance_3km = 0.0;
#define MAX_PRECISION   (13)

static char * my_3km_ftoa(double f, char * buf, int precision)
{
    char * ptr = buf;
    char * p = ptr;
    char * p1;
    char c;
    long intPart;
    char* temp_str;

    // check precision bounds
    if (precision > MAX_PRECISION)
        precision = MAX_PRECISION;

    // sign stuff
    if (f < 0)
    {
        f = -f;
        *ptr++ = '-';
    }

    if (precision < 0)  // negative precision == automatic precision guess
    {
        if (f < (double)1.0) precision = 6;
        else if (f < (double)10.0) precision = 5;
        else if (f < (double)100.0) precision = 4;
        else if (f < (double)1000.0) precision = 3;
        else if (f < (double)10000.0) precision = 2;
        else if (f < (double)100000.0) precision = 1;
        else precision = 0;
    }

    // round value according the precision
    //if (precision)
    //    f += rounders[precision];

    // integer part...
    intPart = f;
    f -= intPart;

    if (!intPart)
        *ptr++ = '0';
    else
    {
        // save start pointer
        p = ptr;

        // convert (reverse order)
        while (intPart)
        {
            *p++ = '0' + intPart % 10;
            intPart /= 10;
        }

        // save end pos
        p1 = p;

        // reverse result
        while (p > ptr)
        {
            c = *--p;
            *p = *ptr;
            *ptr++ = c;
        }

        // restore end pos
        ptr = p1;
    }

    // decimal part
    if (precision)
    {
        // place decimal point
        *ptr++ = '.';

        // convert
        while (precision--)
        {
            f *= (double)10.0;
            c = f;
            *ptr++ = '0' + c;
            f -= c;
        }
    }

    // terminating zero
    *ptr = 0;

    temp_str = --ptr;
    while(*temp_str != '.')
    { 
        if(*temp_str == '0')
        {
            *temp_str = '\0';
        }
        else
        {
            break;
        }
        temp_str--;
    }   

    if((*(temp_str+1) == '\0') && (*temp_str == '.'))
    {
        *(temp_str+1) = '0';
    }

    return buf;
}

void running_3km_event_handler(message_id_enum event_id, int32_t param1, void* param2)
{
	GRAPHICLOG("[chenchen---------  message_id_enum=%d, param1=%d\r\n", event_id, param1);
}

static double getdistance(int lat1, int lng1, int lat2, int lng2)
{
	double a = abs(lat1-lat2)*10.0;
	double b = abs(lng1-lng2)*11.0;
	double s = sqrt((a*a)+(b*b));	
	return s;
}

void training_3km()
{
	int lat1,lng1,lat2,lng2;
	double s1;

	while(1){
		if(lat_temp[0] == 0 && lng_temp[0] == 0){
			vTaskDelay(2000);
		}else{
			lat1 = atof(lat_temp)*100;
			lng1 = atof(lng_temp)*100;
			while(1){
				lat2 = lat1;
				lng2 = lng1;
				vTaskDelay(2000);
				if(lat_temp[0] == 0 && lng_temp[0] == 0){
					continue;
				}
				lat1 = atof(lat_temp)*100;
				lng1 = atof(lng_temp)*100;
				s1 = getdistance(lat1,lng1,lat2,lng2);
				distance_3km += s1;
				if(distance_3km >= 3000){
					PMIC_VR_CONTROL(PMIC_VIBR   , PMIC_VR_CTL_ENABLE);
					vTaskDelay(1000);
					PMIC_VR_CONTROL(PMIC_VIBR   , PMIC_VR_CTL_DISABLE);
					return;
				}
			}
		}
	}
}

static void running_3km_screen_cntx_init()
{
	g_tt_is_3km_start = false;

    if ((running_3km_screen_cntx.height == 0) && (running_3km_screen_cntx.width==0)) {

        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_HEIGHT, &(running_3km_screen_cntx.height));
        bsp_lcd_get_parameter(LCM_IOCTRL_QUERY__LCM_WIDTH, &(running_3km_screen_cntx.width));
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
			temp_index = 3;
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
				break;
			case -3:
				break;
			case 0:
				break;
			case 2:
				gnss_demo_app_stop();
                gnss_demo_app_destroy(gnss_task_handle);
				show_traing_type_screen();
				return;
			case 3:
				g_tt_is_3km_start = !g_tt_is_3km_start;
				return;
			default:
				break;
	
		}


}

static uint8_t* running_3km_convert_string_to_wstring(char* string)
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

static void gnss_3km_app_location_handle(gnss_location_handle_type_t type, void* param)
{
    int32_t x,y;
	char buf1[32];
	char buf2[32];
	char buf3[32];
	uint8_t trainning3kmname[10] = {0x09,0x4E,0x6C,0x51,0xCC,0x91,0x00};

	x = 40 * RESIZE_RATE;
	y = 50 * RESIZE_RATE;

	ui_send_event(MESSAGE_ID_TRAING_3KM, 35, 0);

    if (type == GNSS_LOCATION_HANDLE_TYPE_ERROR) {
        GNSSLOGD("[chenchen] location handle error! type: %d\n", (int)param);
    } else {
        gnss_location_struct_t *location = (gnss_location_struct_t *)param;
        GNSSLOGD("[chenchen] App Get Location, latitude:%s, longitude:%s, accuracy:%d\n", location->latitude, location->longitude, (int)location->accuracy);
        //gnss_update_data(&location->nmea_sentence);		
        ui_send_event(MESSAGE_ID_GNSS_NMEA, 0, 0); 

		memcpy(lat_temp, location->latitude, sizeof(location->latitude));
		memcpy(lng_temp, location->longitude, sizeof(location->longitude));

		my_3km_ftoa(atof(location->latitude)/100, buf1, 4);
		my_3km_ftoa(atof(location->longitude)/100, buf2, 4);

		gdi_font_engine_display_string_info_t running_3km_string_info = {0};
	    gdi_draw_filled_rectangle(0,0,running_3km_screen_cntx.width-1,running_3km_screen_cntx.height-1, running_3km_screen_cntx.bg_color);

//		gdi_image_draw_by_id(0, 0, IMAGE_ID_ZBG_03_BMP);

	    gdi_font_engine_size_t font = GDI_FONT_ENGINE_FONT_SMALL;
	    gdi_font_engine_color_t text_color = {0, 255, 255, 255};

	    gdi_font_engine_set_font_size(font);
	    gdi_font_engine_set_text_color(text_color);

		if (g_tt_is_3km_start) {
			gdi_image_draw_by_id(190, running_3km_screen_cntx.fota_title_y, IMAGE_ID_IDLE_GPS_BMP);

			running_3km_string_info.baseline_height = -1;
	    	running_3km_string_info.x = 100;
	    	running_3km_string_info.y = running_3km_screen_cntx.fota_title_y;
	    	running_3km_string_info.string = running_3km_convert_string_to_wstring("STOP");
	    	running_3km_string_info.length = strlen("STOP");
	    	gdi_font_engine_display_string(&running_3km_string_info);			
		} else {
			running_3km_string_info.baseline_height = -1;
			running_3km_string_info.x = 100;
			running_3km_string_info.y = running_3km_screen_cntx.fota_title_y;
			running_3km_string_info.string = running_3km_convert_string_to_wstring("START");
			running_3km_string_info.length = strlen("START");
			gdi_font_engine_display_string(&running_3km_string_info);
		}
		
	    running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = running_3km_screen_cntx.fota_title_x;
	    running_3km_string_info.y = running_3km_screen_cntx.fota_title_y;
	    running_3km_string_info.string = trainning3kmname;
	    running_3km_string_info.length = 4;
	    gdi_font_engine_display_string(&running_3km_string_info);	
/*
	    running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 25;
	    running_3km_string_info.y = 50;
	    running_3km_string_info.string = running_3km_convert_string_to_wstring("latitude:");
	    running_3km_string_info.length = strlen("latitude:");
	    gdi_font_engine_display_string(&running_3km_string_info);
*/
		uint8_t lat_cn[10] = {0xAC,0x7E,0xA6,0x5E,0x00};
		running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 25;
	    running_3km_string_info.y = 50;
	    running_3km_string_info.string = lat_cn;
	    running_3km_string_info.length = 2;
	    gdi_font_engine_display_string(&running_3km_string_info);

	    running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 120;
	    running_3km_string_info.y = 50;
	    running_3km_string_info.string = running_3km_convert_string_to_wstring(buf1);
	    running_3km_string_info.length = strlen(buf1);
	    gdi_font_engine_display_string(&running_3km_string_info);
/*
	    running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 25;
	    running_3km_string_info.y = 85;
	    running_3km_string_info.string = running_3km_convert_string_to_wstring("longitude:");
	    running_3km_string_info.length = strlen("longitude:");
	    gdi_font_engine_display_string(&running_3km_string_info);
*/
		uint8_t lon_cn[10] = {0xCF,0x7E,0xAC,0x7E,0x00};
	    running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 25;
	    running_3km_string_info.y = 85;
	    running_3km_string_info.string = lon_cn;
	    running_3km_string_info.length = 2;
	    gdi_font_engine_display_string(&running_3km_string_info);


	    running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 120;
	    running_3km_string_info.y = 85;
	    running_3km_string_info.string = running_3km_convert_string_to_wstring(buf2);
	    running_3km_string_info.length = strlen(buf2);
	    gdi_font_engine_display_string(&running_3km_string_info);
/*
		running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 25;
	    running_3km_string_info.y = 120;
	    running_3km_string_info.string = running_3km_convert_string_to_wstring("heartrate:");
	    running_3km_string_info.length = strlen("heartrate:");
	    gdi_font_engine_display_string(&running_3km_string_info);
*/
		uint8_t hr_cn[10] = {0xC3,0x5F,0x87,0x73,0x00};
		running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 25;
	    running_3km_string_info.y = 120;
	    running_3km_string_info.string = hr_cn;
	    running_3km_string_info.length = 2;
	    gdi_font_engine_display_string(&running_3km_string_info);

/*
		running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 25;
	    running_3km_string_info.y = 155;
	    running_3km_string_info.string = running_3km_convert_string_to_wstring("distance:");
	    running_3km_string_info.length = strlen("distance:");
	    gdi_font_engine_display_string(&running_3km_string_info);
*/
		uint8_t dis_cn[10] = {0xDD,0x8D,0xBB,0x79,0x00};
		running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 25;
	    running_3km_string_info.y = 155;
	    running_3km_string_info.string = dis_cn;
	    running_3km_string_info.length = 2;
	    gdi_font_engine_display_string(&running_3km_string_info);


		my_3km_ftoa(distance_3km,buf3,1);
		running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 120;
	    running_3km_string_info.y = 155;
	    running_3km_string_info.string = running_3km_convert_string_to_wstring(buf3);
	    running_3km_string_info.length = strlen(buf3);
	    gdi_font_engine_display_string(&running_3km_string_info);

		running_3km_string_info.baseline_height = -1;
	    running_3km_string_info.x = 180;
	    running_3km_string_info.y = 155;
	    running_3km_string_info.string = running_3km_convert_string_to_wstring("m");
	    running_3km_string_info.length = strlen("m");
	    gdi_font_engine_display_string(&running_3km_string_info);

		gdi_lcd_update_screen(0,0,running_3km_screen_cntx.width-1,running_3km_screen_cntx.height-1);	
    }
}

static void gnss_3km_main()
{
    int32_t periodic = 1;
    
    gnss_task_handle = gnss_demo_app_create();
    gnss_demo_app_config(periodic, gnss_3km_app_location_handle);
    gnss_demo_app_start();
}


void show_running_3km_screen(void)
{
	TaskHandle_t xCreatedTraining3KMTask;
	
	running_3km_screen_cntx_init();
	demo_ui_register_keypad_event_callback(running_3km_screen_keypad_event_handler, NULL);
	gnss_3km_main();

	if(pdPASS !=xTaskCreate(training_3km, TRAINING_3KM_TASK_NAME, TRAINING_3KM_TASK_STACK_SIZE /((uint32_t)sizeof(StackType_t)), NULL, TRAINING_3KM_TASK_PRIO, &xCreatedTraining3KMTask)){
		log_hal_info("[hailong]creat training 3km task fail\n");
	}else{
		log_hal_info("[hailong]creat training 3km task pass\n");
	}
}

