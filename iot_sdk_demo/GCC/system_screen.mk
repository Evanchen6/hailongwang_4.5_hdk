LIBSYSTEMSREEN   = project/mt2523_hdk/apps/iot_sdk_demo/src/system_screen

C_FILES  += $(LIBSYSTEMSREEN)/system_screen.c \
			$(LIBSYSTEMSREEN)/system_person.c \
			$(LIBSYSTEMSREEN)/system_record.c

CFLAGS  += -I$(SOURCE_DIR)/project/mt2523_hdk/apps/iot_sdk_demo/inc/system_screen