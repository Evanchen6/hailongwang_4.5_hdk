MAINSCREEN   = project/mt2523_hdk/apps/longyue/src/main_screen

C_FILES  += $(MAINSCREEN)/main_screen.c    \
            $(MAINSCREEN)/ui_demo_task.c    \



CFLAGS  += -I$(SOURCE_DIR)/project/mt2523_hdk/apps/longyue/inc/main_screen
CFLAGS  += -I$(SOURCE_DIR)/driver/chip/inc
CFLAGS  += -I$(SOURCE_DIR)/driver/chip/mt2523/inc
CFLAGS  += -I$(SOURCE_DIR)/driver/board/component/lcm/ST7789H2
CFLAGS  += -I$(SOURCE_DIR)/driver/board/component/common
