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

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "task_def.h"

/* device.h includes */
#include "mt2523.h"

/* hal includes */
#include "hal.h"


//#include "bt_error_solution.h"

/*bt spp include */
#include "bt_spp.h"
#include "bt_init.h"
#include "bt_spp_main.h"

#include "nvdm.h"
#include "hal_flash.h"

#include "sensor_demo.h" /* Turn ON/OFF SENSOR_DEMO inside */
#ifdef SENSOR_DEMO
#include "sensor_alg_interface.h"
#endif

#ifdef MTK_SMART_BATTERY_ENABLE
#include "cust_battery_meter.h"
#include "hal.h"
#include "memory_attribute.h"

/* battery management includes */
#include "battery_management.h"
#include "battery_message.h"

log_create_module(bmt_demo, PRINT_LEVEL_WARNING);
#endif

#include "audio_middleware_api.h"

#if defined(MTK_PORT_SERVICE_ENABLE)
#include "serial_port.h"
#endif

#include "hal_uart.h"

#include "sys_init.h"
#include "bsp_gpio_ept_config.h"
#include "memory_map.h"


#ifdef MTK_USB_DEMO_ENABLED
#include "usb.h"
#endif

#ifdef MTK_KEYPAD_ENABLE
#include "keypad_custom.h"
#endif

#include "gnss_demo.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


extern uint8_t sleep_manager_handle;

/* Private functions ---------------------------------------------------------*/


#if !defined (MTK_DEBUG_LEVEL_NONE)

LOG_CONTROL_BLOCK_DECLARE(atci);
#ifdef MTK_BT_AT_COMMAND_ENABLE
LOG_CONTROL_BLOCK_DECLARE(atci_bt);
#endif
LOG_CONTROL_BLOCK_DECLARE(atci_charger);
#ifdef MTK_CTP_ENABLE
LOG_CONTROL_BLOCK_DECLARE(atci_ctp);
#endif
LOG_CONTROL_BLOCK_DECLARE(atci_keypad);
LOG_CONTROL_BLOCK_DECLARE(atci_reg);
LOG_CONTROL_BLOCK_DECLARE(atcmd);
LOG_CONTROL_BLOCK_DECLARE(BT);
LOG_CONTROL_BLOCK_DECLARE(BTMM);
LOG_CONTROL_BLOCK_DECLARE(BTHCI);
LOG_CONTROL_BLOCK_DECLARE(BTIF);
LOG_CONTROL_BLOCK_DECLARE(BTRFCOMM);
LOG_CONTROL_BLOCK_DECLARE(BTL2CAP);
LOG_CONTROL_BLOCK_DECLARE(BTSPP);
LOG_CONTROL_BLOCK_DECLARE(sink_srv);
LOG_CONTROL_BLOCK_DECLARE(sink_app);
LOG_CONTROL_BLOCK_DECLARE(bt_audio);
LOG_CONTROL_BLOCK_DECLARE(common);
LOG_CONTROL_BLOCK_DECLARE(GNSS_TAG);
LOG_CONTROL_BLOCK_DECLARE(GRAPHIC_TAG);
LOG_CONTROL_BLOCK_DECLARE(hal);
//LOG_CONTROL_BLOCK_DECLARE(PXP_MAIN);
LOG_CONTROL_BLOCK_DECLARE(RTC_ATCI);
LOG_CONTROL_BLOCK_DECLARE(sensor);
#ifdef MTK_SMART_BATTERY_ENABLE
LOG_CONTROL_BLOCK_DECLARE(bmt);
#endif

log_control_block_t *syslog_control_blocks[] = {
    &LOG_CONTROL_BLOCK_SYMBOL(atci),
#ifdef MTK_BT_AT_COMMAND_ENABLE
    &LOG_CONTROL_BLOCK_SYMBOL(atci_bt),
#endif
    &LOG_CONTROL_BLOCK_SYMBOL(atci_charger),
#ifdef MTK_CTP_ENABLE
    &LOG_CONTROL_BLOCK_SYMBOL(atci_ctp),
#endif
    &LOG_CONTROL_BLOCK_SYMBOL(atci_keypad),
    &LOG_CONTROL_BLOCK_SYMBOL(atci_reg),
    &LOG_CONTROL_BLOCK_SYMBOL(atcmd),
    &LOG_CONTROL_BLOCK_SYMBOL(BT),
    &LOG_CONTROL_BLOCK_SYMBOL(BT),
    &LOG_CONTROL_BLOCK_SYMBOL(BTMM),
    &LOG_CONTROL_BLOCK_SYMBOL(BTHCI),    
    &LOG_CONTROL_BLOCK_SYMBOL(BTIF),
    &LOG_CONTROL_BLOCK_SYMBOL(BTL2CAP),
    &LOG_CONTROL_BLOCK_SYMBOL(BTRFCOMM),
    &LOG_CONTROL_BLOCK_SYMBOL(BTSPP),
    &LOG_CONTROL_BLOCK_SYMBOL(sink_srv),
    &LOG_CONTROL_BLOCK_SYMBOL(sink_app),
    &LOG_CONTROL_BLOCK_SYMBOL(bt_audio),
    &LOG_CONTROL_BLOCK_SYMBOL(common),
    &LOG_CONTROL_BLOCK_SYMBOL(GNSS_TAG),
    &LOG_CONTROL_BLOCK_SYMBOL(GRAPHIC_TAG),
    &LOG_CONTROL_BLOCK_SYMBOL(hal),
    &LOG_CONTROL_BLOCK_SYMBOL(RTC_ATCI),
    &LOG_CONTROL_BLOCK_SYMBOL(sensor),
#ifdef MTK_SMART_BATTERY_ENABLE
    &LOG_CONTROL_BLOCK_SYMBOL(bmt),
#endif
    NULL
};

int BT_XFile_EncryptionCommand()
{
    return 0;
}


static void syslog_config_save(const syslog_config_t *config)
{
    nvdm_status_t status;
    char *syslog_filter_buf;

    syslog_filter_buf = (char*)pvPortMalloc(SYSLOG_FILTER_LEN);
    configASSERT(syslog_filter_buf != NULL);
    syslog_convert_filter_val2str((const log_control_block_t **)config->filters, syslog_filter_buf);
    status = nvdm_write_data_item("common",
                                  "syslog_filters",
                                  NVDM_DATA_ITEM_TYPE_STRING,
                                  (const uint8_t *)syslog_filter_buf,
                                  strlen(syslog_filter_buf));
    vPortFree(syslog_filter_buf);
    LOG_I(common, "syslog config save, status=%d", status);
}

static uint32_t syslog_config_load(syslog_config_t *config)
{
    uint32_t sz = SYSLOG_FILTER_LEN;
    char *syslog_filter_buf;

    syslog_filter_buf = (char*)pvPortMalloc(SYSLOG_FILTER_LEN);
    configASSERT(syslog_filter_buf != NULL);
    if (nvdm_read_data_item("common", "syslog_filters", (uint8_t*)syslog_filter_buf, &sz) == NVDM_STATUS_OK) {
        syslog_convert_filter_str2val(config->filters, syslog_filter_buf);
    } else {
        /* popuplate the syslog nvdm with the image setting */
        syslog_config_save(config);
    }
    vPortFree(syslog_filter_buf);
    return 0;
}

#endif /* MTK_DEBUG_LEVEL_NONE */

#ifdef MTK_SMART_BATTERY_ENABLE
/**
* @brief       This function is use to get the battery information.
* @return      None.
*/
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

    if (charger_status) {
        LOG_I(bmt_demo, "Battery capacity = %d(%%)", capacity);
        LOG_I(bmt_demo, "Battery capacity level = %d", capacity_level);
        LOG_I(bmt_demo, "Charger current = %d(mA)", charger_current);
        LOG_I(bmt_demo, "Charger status = %d(0:charge not exist; 1:charger exist)", charger_status);
        LOG_I(bmt_demo, "Charger type = %d(0:unknown; 1:standard host; 2:non-standard AC charger; 3:standard AC charger 4:charging host)", charger_type);
        LOG_I(bmt_demo, "Battery temperature = %d(Celsius degrees)", battery_temperature);
        LOG_I(bmt_demo, "Battery voltage = %d(mV)\n", battery_volt);
    } else {
        LOG_I(bmt_demo, "Battery capacity = %d(%%)", capacity);
        LOG_I(bmt_demo, "Battery capacity level = %d", capacity_level);
        LOG_I(bmt_demo, "Battery temperature = %d(Celsius degrees)", battery_temperature);
        LOG_I(bmt_demo, "Battery voltage = %d(mV)\n", battery_volt);
    }

}

/**
* @brief       This function is use to check battery status.
* @return      None.
*/
static void check_battery_status(void)
{
    int32_t capacity, battery_temperature,charger_exist;

    capacity = battery_management_get_battery_property(BATTERY_PROPERTY_CAPACITY);
    battery_temperature = battery_management_get_battery_property(BATTERY_PROPERTY_TEMPERATURE);
    charger_exist = battery_management_get_battery_property(BATTERY_PROPERTY_CHARGER_EXIST);

    if((capacity == 0 ) && (capacity != BATTERY_INVALID_VALUE)) {
        /* Low battery shutdown */
        LOG_W(bmt_demo, "Low battery shutdown");
        vTaskDelay(3 * 1000 / portTICK_RATE_MS);
        hal_sleep_manager_enter_power_off_mode();
    }

    /* High temperature protection. It depends on your application and the battery specifications */
    if((battery_temperature >= 60 ) && (battery_temperature != BATTERY_INVALID_VALUE)) {
        /* High temperature  shutdown */
        LOG_W(bmt_demo, "High temperature shutdown");
        vTaskDelay(3 * 1000 / portTICK_RATE_MS);
        hal_sleep_manager_enter_power_off_mode();
    }

    if((charger_exist == 1 ) && (charger_exist != BATTERY_INVALID_VALUE)
       && (capacity == 100 ) && (capacity != BATTERY_INVALID_VALUE)) {
        /* Battery full */
        LOG_I(bmt_demo, "Battery full");
    }

}

/**
* @brief       This function is battery management message handler.
* @param[in]   message: The message should be process.
* @return      None.
*/
static void battery_management_message_handler(battery_message_context_t *message)
{
    LOG_I(bmt_demo, "battery_management_message_handler event  = 0x%X", (int) message->event);

    switch (message->event) {
        case BATTERY_MANAGEMENT_EVENT_BATTERY_UPDATE: {

            get_battery_information();

        }
        break;
        default: {

        }
        break;
    }

    check_battery_status();
}

/**
* @brief       Task main function
* @param[in]   pvParameters: Pointer that will be used as the parameter for the task being created.
* @return      None.
*/
static void battery_message_task(void *pvParameters)
{
    uint32_t handle;
    battery_message_context_t message;

    battery_message_allocate(&handle);

    while (1) {
        if (battery_message_receive(handle, &message)) {

            battery_management_message_handler(&message);
        }

    }
}

/**
 * @brief     This function is to create task for battery message.
 * @return    None.
 */
void battery_message_create_task(void)
{
    /* Create task */
    xTaskCreate(battery_message_task, BMT_APP_TASK_NAME, BMT_APP_TASK_STACKSIZE / sizeof(portSTACK_TYPE), NULL, BMT_APP_TASK_PRIO, NULL);
}
#endif //MTK_SMART_BATTERY_ENABLE



#if defined(MTK_PORT_SERVICE_ENABLE)
static void syslog_port_service_init(void)
{
    serial_port_dev_t syslog_port;
    serial_port_setting_uart_t uart_setting;

    if (serial_port_config_read_dev_number("syslog", &syslog_port) != SERIAL_PORT_STATUS_OK) {
        syslog_port = SERIAL_PORT_DEV_UART_2;
        serial_port_config_write_dev_number("syslog", syslog_port);
        uart_setting.baudrate = HAL_UART_BAUDRATE_115200;
        serial_port_config_write_dev_setting(syslog_port, (serial_port_dev_setting_t *)&uart_setting);
    }
}
#endif

void bt_io_uart_irq_ex(hal_uart_callback_event_t event, void *parameter)
{
    // BaseType_t  x_higher_priority_task_woken = pdFALSE;
    // if (HAL_UART_EVENT_READY_TO_READ == event)
    {
        // xSemaphoreGiveFromISR(g_bt_io_semaphore, &x_higher_priority_task_woken);
        // portYIELD_FROM_ISR( x_higher_priority_task_woken );
    }
}


#define VFIFO_SIZE_RX_BT (1024)
#define VFIFO_SIZE_TX_BT (1024)
#define VFIFO_ALERT_LENGTH_BT (20)

ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN static uint8_t g_bt_cmd_tx_vfifo[VFIFO_SIZE_TX_BT];
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN static uint8_t g_bt_cmd_rx_vfifo[VFIFO_SIZE_RX_BT];

hal_uart_status_t bt_io_uart_init_ex(hal_uart_port_t port)
{
    hal_uart_status_t ret;
    /* Configure UART PORT */
    hal_uart_config_t uart_config = {
        .baudrate = HAL_UART_BAUDRATE_115200,
        .word_length = HAL_UART_WORD_LENGTH_8,
        .stop_bit = HAL_UART_STOP_BIT_1,
        .parity = HAL_UART_PARITY_NONE
    };

    ret = hal_uart_init(port, &uart_config);

    if (HAL_UART_STATUS_OK == ret) {

        hal_uart_dma_config_t   dma_config = {
            .send_vfifo_buffer              = g_bt_cmd_tx_vfifo,
            .send_vfifo_buffer_size         = VFIFO_SIZE_TX_BT,
            .send_vfifo_threshold_size      = 128,
            .receive_vfifo_buffer           = g_bt_cmd_rx_vfifo,
            .receive_vfifo_buffer_size      = VFIFO_SIZE_RX_BT,
            .receive_vfifo_threshold_size   = 128,
            .receive_vfifo_alert_size       = VFIFO_ALERT_LENGTH_BT
        };

        // g_bt_io_semaphore = xSemaphoreCreateBinary();

        ret = hal_uart_set_dma(port, &dma_config);

        ret = hal_uart_register_callback(port, bt_io_uart_irq_ex, NULL);

    }
    return ret;
}

static volatile uint32_t lora_receive_notice = 0;
static volatile uint32_t lora_send_notice = 0;
static char lora_rx_vfifo_buffer[512] __attribute__ ((section(".noncached_zidata")));
static char lora_tx_vfifo_buffer[512] __attribute__ ((section(".noncached_zidata")));

QueueHandle_t lora_rx_queue;
#define START_BIT   0x55AA

typedef struct{
	uint16_t length;
	uint8_t type;
	uint8_t data[17];
} spp_message_ex_t;

typedef struct{
	uint16_t start;
	uint16_t addr;
	uint32_t keycode;
	spp_message_ex_t spp_message;
	uint16_t crccode;
} lora_message_t;

typedef enum {
    MSG_ID_LORA_RX_QUEUE = 0,

    MSG_ID_LORA_END
} lora_msg_id_t;


typedef struct {
    lora_msg_id_t msg_id;
    uint8_t* msg_data;
} lora_general_msg_t;

typedef enum{
	SINGLE_READ = 0x01,
	SINGLE_WRITE,
	MULTIPLY_READ,
	MULTIPLY_WRITE,
	CHANNEL_CHANGE
} command_type_t;

typedef enum{
	BT_ID = 0,    //蓝牙ID，唯一
	MEMBER_ID,    //佩戴人ID
	MEMBER_NAME,    //佩戴人姓名
	MEMBER_GENDER,    //佩戴人性别
	MEMBER_AGE,    //佩戴人年龄
	MEMBER_WEIGHT,    //佩戴人体重
	RANGE_NORMAL_PPG,    //正常心率范围
	RANGE_NORMAL_BLOOD_OXYGEN,    //正常血氧范围
	RANGE_NORMAL_EKG,     //正常血压范围
	EKG_PARAMETER,    //血压特征参数
	STANDARD_TIME,    //时间
	RUNNNING_STATUS,    //运行状态
	CALORIES_BURNED,    //当日累计消耗卡路里
	LAST_ERROR_INFO,    //末次故障信息
	LAST_WARNNING_INFO,    //末次告警信息
	LAST_POSITION_TIME,    //末次位置及时间
	LAST_VITAL_SIGNS_INFO,    //末次生命体征信息
	GPS_SWITCH,    //GPS开关控制
	GPS_FREQ,    //GPS采样频率
	GYRO_MODE,    //GYRO工作模式
	VITAL_SIGNS_SWITCH,    //生命体征芯片开关控制
	VITAL_SIGNS_FREQ,    //生命体征芯片采样频率
	VITAL_SIGNS_COUNTER,     //生命体征芯片单次采样原始值数目
	COMMUNICATION_AUTHENTICATION_CODE,    //单播认证码（明文）
	COMMUNICATION_SECRET_KEY,    //通信密钥
	BT_SWTICH,    //蓝牙开关控制
	BT_AUTHENTICATION_CODE,    //蓝牙认证码
	LORA_SWTICH,    //LORA开关控制
	LORA_MODE,    //LORA工作模式
	LORA_WORK_FREQ,    //LORA工作频率
	LORA_FREQ_PARAMETER,    //LORA扩频参数
	LORA_ADDR,    //LORA短地址
	LORA_OVERTIME,    //LORA单播超时
	WIFI_SWTICH,    //WIFI开关控制
	WIFI_NET_ID,    //WIFI网络ID
	WIFI_NET_PASSWORD,    //WIFI网络口令
	MAGNETOMETER_SWITCH,    //磁力计开关控制
	CHEAT_PROOF_SWITCH,    //防作弊开关控制
	CLASS_ID,     //科目代码
	TIME_WARM_UP,    //热身时间
	TIME_TRAIN_START,    //训练开始时间
	TIME_TRAIN_END,    //训练完成时间
	TIME_RESTORE,    //体征恢复时间
	LEVEL_ACHIEVEMENT,    //成绩等级
	CLASS_ACHIEVEMENT,    //课目成绩
	DISTANCE_TOTAL,    //课目累计位移米数
	CLASS_CALORIES_BURNED_TOTAL,    //课目累计消耗卡路里
	HISTORY_ERROR_COUNTER,    //历史故障数组缓存元素个数
	HISTORY_NON_RETURN_ERROR_COUNTER,     //历史故障数组缓存未回传元素个数
	HISTORY_CLASS_COUNTER,    //历史组训课目数组元素个数
	HISTORY_NON_RETURN_CLASS_COUNTER,     //历史组训课目数组未回传元素个数
	HISTORY_WARNNING_COUNTER,    //历史告警数组元素个数
	HISTORY_NON_RETURN_WARNNING_COUNTER,    //历史告警数组未回传元素个数
	HISTORY_TRAJECTORY_COUNTRER,    //历史轨迹点数组元素个数
	HISTORY_NON_RETURN_TRAJECTORY_COUNTRER,     //历史轨迹点数组未回传元素个数
	HISTORY_VITAL_SIGNS_COUNTRER,    //历史生命体征数组元素个数
	HISTORY_NON_RETURN_VITAL_SIGNS_COUNTRER,    //历史生命体征数组未回传元素个数
	HISTORY_PPG_COUNTRER,    //历史生命体征原始PPG数组元素个数
	HISTORY_NON_RETURN_PPG_COUNTRER    //历史生命体征原始PPG数组未回传元素个数
}device_param_t;

static void lora_uart_irq(hal_uart_callback_event_t status, void *user_data)
{
	lora_general_msg_t msg_queue_item;
	
	if(HAL_UART_EVENT_READY_TO_READ == status){
		msg_queue_item.msg_id = MSG_ID_LORA_RX_QUEUE;
		msg_queue_item.msg_data = NULL;		
		xQueueSendFromISR(lora_rx_queue, (void*)&msg_queue_item, 0);
		log_hal_info("[hailong]xQueueSendFromISR\n");
	}
}

bool LORA_ADDR_CHECK(uint16_t addr){
	return true;
}

bool LORA_KEYCODE_CHECK(uint32_t keycode){
	return true;
}

bool LORA_CRC_CHECK(spp_message_ex_t spp_message){
	return true;
}

void single_param_read(uint8_t data)
{

}

void single_param_write()
{

}

void multiply_param_read()
{

}


void multiply_param_write()
{

}

void channel_change()
{

}

void spp_event_handler(spp_message_ex_t spp_message)
{
	switch(spp_message.type){
		case SINGLE_READ:
		{
			int i;
			for(i = 0; i < spp_message.length-1; i++){
				single_param_read(spp_message.data[i]);
			}
		}
		break;
		case SINGLE_WRITE:
		{
			single_param_write();
		}
		break;
		case MULTIPLY_READ:
		{
			multiply_param_read();
		}
		break;
		case MULTIPLY_WRITE:
		{
			multiply_param_write();
		}
		break;
		case CHANNEL_CHANGE:
		{
			channel_change();
		}
	}
}

void lora_event_handler(uint16_t start, uint16_t addr, uint32_t keycode, spp_message_ex_t spp_message, uint16_t crccode)
{
	if(start != START_BIT){
		return;
	}

	if(!LORA_ADDR_CHECK(addr)){
		return;
	}
	
	if(!LORA_KEYCODE_CHECK(keycode)){
		return;
	}
	
	if(!LORA_CRC_CHECK(spp_message)){
		return;
	}
	
	spp_event_handler(spp_message);
}

void lora_task(void *arg)
{
	lora_message_t message;
	lora_general_msg_t msg_queue_item;
	int left = sizeof(lora_message_t);
	
	lora_rx_queue = xQueueCreate(10, sizeof(lora_general_msg_t));
	if(lora_rx_queue == NULL ) {
        return;
    }
	
	while(1){
		log_hal_info("[hailong]xQueueReceive\n");
		xQueueReceive(lora_rx_queue, (void *)&msg_queue_item, portMAX_DELAY);
		if(msg_queue_item.msg_id == MSG_ID_LORA_RX_QUEUE){
			memset((void*) &message, 0, sizeof(lora_message_t));
			hal_uart_receive_dma(HAL_UART_1, &message, left);
			log_hal_info("[hailong]%s", message.spp_message.data);
			lora_event_handler(message.start, message.addr, message.keycode, message.spp_message, message.crccode);
            memset((void*) &message, 0, sizeof(lora_message_t));
		}
	}
}

void lora_creat_task()
{
	TaskHandle_t xCreatedLoraTask;
	xTaskCreate(lora_task, LORA_TASK_NAME, LORA_TASK_STACK_SIZE /((uint32_t)sizeof(StackType_t)), NULL, LORA_TASK_PRIO, &xCreatedLoraTask);
}

void lora_uart_init()
{
	hal_uart_config_t lora_uart_config;
	lora_uart_config.baudrate = HAL_UART_BAUDRATE_9600;
    lora_uart_config.parity = HAL_UART_PARITY_NONE;
    lora_uart_config.stop_bit = HAL_UART_STOP_BIT_1;
    lora_uart_config.word_length = HAL_UART_WORD_LENGTH_8;
	hal_uart_init(HAL_UART_1, &lora_uart_config);
	
	hal_uart_dma_config_t lora_dma_config;
	lora_dma_config.receive_vfifo_alert_size = 50;
	lora_dma_config.receive_vfifo_buffer = lora_rx_vfifo_buffer;
	lora_dma_config.receive_vfifo_buffer_size = 512;
	lora_dma_config.receive_vfifo_threshold_size = 128;
	lora_dma_config.send_vfifo_buffer = lora_tx_vfifo_buffer;
	lora_dma_config.send_vfifo_buffer_size = 512;
	lora_dma_config.send_vfifo_threshold_size = 51;
	hal_uart_set_dma(HAL_UART_1, &lora_dma_config);
	hal_uart_register_callback(HAL_UART_1, lora_uart_irq, NULL);
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
//    int user_data[10];
	/* Do system initialization, eg: hardware, nvdm. */
    system_init();


    hal_sleep_manager_lock_sleep(sleep_manager_handle);

#if defined(MTK_PORT_SERVICE_ENABLE)
    syslog_port_service_init();
#endif

    /* system log initialization. */
    log_init(syslog_config_save, syslog_config_load, syslog_control_blocks);

#if defined (MTK_PORT_SERVICE_ENABLE)
    /* Reduce bt-spp log to make syslog over bt-spp work. */
    //log_config_print_level(bt_spp, PRINT_LEVEL_WARNING);
   // log_config_print_level(SPP_PORT, PRINT_LEVEL_WARNING);
#endif


#ifdef MTK_SENSOR_BIO_USE_MT2511
    /*turn on VA28 for mt2511*/
    PMIC_VR_CONTROL(PMIC_VA28   , PMIC_VR_CTL_ENABLE);
#endif

#ifdef MTK_USB_DEMO_ENABLED
    usb_boot_init();
#endif

#ifdef MTK_SMART_BATTERY_ENABLE
    battery_message_create_task();
#endif
		/* disable sleep defaultly */
    audio_middleware_init();

    bt_demo_init();
	
	//++ by yanhui add for SPP
	bt_io_uart_init_ex(HAL_UART_2);
	log_config_print_switch(BTMM, DEBUG_LOG_OFF);
    log_config_print_switch(BTHCI, DEBUG_LOG_ON);
	bt_create_task();
	bt_spp_main();
	//-- by yanhui add for SPP

	//add lora task start
	PMIC_VR_CONTROL(PMIC_VMC, PMIC_VR_CTL_ENABLE);//LORA power supply enable
	lora_uart_init();
	lora_creat_task();
	//add lora task end

#ifdef SENSOR_DEMO
    sensor_manager_init();
#endif

    /* user may create own tasks here.
     * EX:
     *    xTaskCreate(UserTask, USER_TASK_NAME, USER_TASK_STACKSIZE/sizeof(StackType_t), NULL, USER_TASK_PRIO, NULL);
     *
     *    UserTask is user's task entry function, which may be defined in another C file to do application job.
     *    USER_TASK_NAME, USER_TASK_STACKSIZE and USER_TASK_PRIO should be defined in task_def.h. User needs to
     *    refer to example in task_def.h, then makes own task MACROs defined.
     */

    task_def_init();
    task_def_create();


    /* Call this function to indicate the system initialize done. */
    SysInitStatus_Set();

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details. */
    for ( ;; );
}



