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
{show_setting_bt_screen, NULL, "BT enable"},
{show_setting_lora_screen, NULL, "LORA enable"},
{show_setting_gps_screen, NULL, "GPS enable"},
{show_setting_fota_screen, NULL, "FOTA"},
{show_setting_vibrator_screen, NULL, "VIBRATOR"},

#endif

#ifdef CONFIG_MESSAGE_ID_ENUM
// define your own message bellowing here
//GNSS message
MESSAGE_ID_TRAING_RUNNING,
MESSAGE_ID_TRAING_SWIM,
MESSAGE_ID_BT_AUDIO,
MESSAGE_ID_WATCH_FACE,

#endif

