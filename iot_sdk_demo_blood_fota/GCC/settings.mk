
LIBSETTINGSREEN   = project/mt2523_hdk/apps/iot_sdk_demo/src/settings

C_FILES  += $(LIBSETTINGSREEN)/setting_screen.c \
		    $(LIBSETTINGSREEN)/setting_bt.c \
		    $(LIBSETTINGSREEN)/setting_gps.c \
		    $(LIBSETTINGSREEN)/setting_fota.c \
		    $(LIBSETTINGSREEN)/setting_vibrator.c \
		    $(LIBSETTINGSREEN)/setting_lora.c
		    
CFLAGS  += -I$(SOURCE_DIR)/project/mt2523_hdk/apps/iot_sdk_demo/inc/settings