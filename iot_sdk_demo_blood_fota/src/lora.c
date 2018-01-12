#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "task_def.h"

/* Queue include */
#include "queue.h"

#include "hal_log.h"
#include "hal_uart.h"

#include "lora.h"

static char lora_rx_vfifo_buffer[512] __attribute__ ((section(".noncached_zidata")));
static char lora_tx_vfifo_buffer[512] __attribute__ ((section(".noncached_zidata")));

QueueHandle_t lora_rx_queue;
#define START_BIT   0x55AA

static void lora_uart_irq(hal_uart_callback_event_t status, void *user_data)
{
	lora_general_msg_t msg_queue_item;
	
	if(HAL_UART_EVENT_READY_TO_READ == status){
		msg_queue_item.msg_id = MSG_ID_LORA_READY_TO_READ;
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
	
	lora_rx_queue = xQueueCreate(10, sizeof(lora_general_msg_t));
	if(lora_rx_queue == NULL ) {
      return;
  }
	
	while(1){
		log_hal_info("[hailong]xQueueReceive\n");
		xQueueReceive(lora_rx_queue, (void *)&msg_queue_item, portMAX_DELAY);
		if(msg_queue_item.msg_id == MSG_ID_LORA_READY_TO_READ){
			memset((void*) &message, 0, sizeof(lora_message_t));
			hal_uart_receive_dma(HAL_UART_1, &message, sizeof(lora_message_t));
			log_hal_info("[hailong]%s", message.spp_message.data);
			lora_event_handler(message.start, message.addr, message.keycode, message.spp_message, message.crccode);
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
