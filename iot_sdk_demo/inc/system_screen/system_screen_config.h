#ifdef CONFIG_INCLUDE_HEADER
#include "system_person.h"
#include "system_record.h"
//#include "bt_audio.h"
#endif


#ifdef CONFIG_INCLUD_BODY
// add your screen here
{show_system_person_screen, NULL, {0x28,0x75,0x37,0x62,0x00}},
{show_system_record_screen, NULL, {0xAD,0x8B,0xC3,0x7E,0xE1,0x4F,0x6F,0x60,0x00}},
#endif

#ifdef CONFIG_MESSAGE_ID_ENUM
// define your own message bellowing here
//GNSS message
MESSAGE_ID_TRAING_RUNNING,
MESSAGE_ID_TRAING_SWIM,
MESSAGE_ID_BT_AUDIO,
MESSAGE_ID_WATCH_FACE,

#endif

