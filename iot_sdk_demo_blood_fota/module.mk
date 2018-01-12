# source files

APP_PATH = project/mt2523_hdk/apps/iot_sdk_demo
GNSS_DL_SRC = $(APP_PATH)/src/fota/gnss_src
APP_FILES += $(APP_PATH)/src/fota/fota_main.c
APP_FILES += $(APP_PATH)/src/fota/fota_trigger.c
APP_FILES += $(GNSS_DL_SRC)/brom_base.c
APP_FILES += $(GNSS_DL_SRC)/brom_mt3301.c
APP_FILES += $(GNSS_DL_SRC)/da_cmd.c
APP_FILES += $(GNSS_DL_SRC)/flashtool.c
APP_FILES += $(GNSS_DL_SRC)/gnss_uart.c

# include files
CFLAGS += -I$(SOURCE_DIR)/$(APP_PATH)/inc/fota/fota_inc
CFLAGS += -I$(SOURCE_DIR)/$(APP_PATH)/inc/fota/gnss_inc
CFLAGS += -I$(SOURCE_DIR)/driver/chip/mt2523/inc
CFLAGS += -I$(SOURCE_DIR)/driver/chip/mt$(PRODUCT_VERSION)/inc
CFLAGS += -I$(SOURCE_DIR)/driver/chip/inc

