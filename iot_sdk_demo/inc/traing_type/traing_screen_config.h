#ifdef CONFIG_INCLUDE_HEADER
#include "traing_running.h"
#include "traing_swim.h"
#include "traing_3km.h"
//#include "bt_audio.h"
#endif


#ifdef CONFIG_INCLUD_BODY
// add your screen here
{show_running_screen, NULL, {0xD1,0x8D,0x65,0x6B,0x00}},
{show_swim_screen, NULL, {0x38,0x6E,0xF3,0x6C,0x00}},
{show_running_3km_screen, NULL, {0x09,0x4E,0x6C,0x51,0xCC,0x91,0x00}},

#endif

#ifdef CONFIG_MESSAGE_ID_ENUM
// define your own message bellowing here
//GNSS message
MESSAGE_ID_TRAING_RUNNING,
MESSAGE_ID_TRAING_SWIM,
MESSAGE_ID_BT_AUDIO,
MESSAGE_ID_WATCH_FACE,

#endif

