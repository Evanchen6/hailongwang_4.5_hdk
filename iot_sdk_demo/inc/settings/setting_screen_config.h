#ifdef CONFIG_INCLUDE_HEADER
#include "setting_bt.h"
#include "setting_lora.h"
#include "setting_gps.h"
#include "setting_fota.h"
#include "setting_vibrator.h"
//#include "bt_audio.h"
#endif


#ifdef CONFIG_INCLUD_BODY
// add your screen here
{show_setting_bt_screen, NULL, {0xDD,0x84,0x59,0x72,0x00}},
{show_setting_lora_screen, NULL, {0xE0,0x65,0xBF,0x7E,0x7F,0x5E,0xAD,0x64,0x00}},
{show_setting_gps_screen, NULL, {0x9A,0x5B,0x4D,0x4F,0x00}},
{show_setting_fota_screen, NULL, {0x47,0x53,0xA7,0x7E,0x00}},
{show_setting_vibrator_screen, NULL, {0x07,0x97,0xA8,0x52,0x00}},

#endif

#ifdef CONFIG_MESSAGE_ID_ENUM
// define your own message bellowing here
//GNSS message
MESSAGE_ID_TRAING_RUNNING,
MESSAGE_ID_TRAING_SWIM,
MESSAGE_ID_BT_AUDIO,
MESSAGE_ID_WATCH_FACE,

#endif

