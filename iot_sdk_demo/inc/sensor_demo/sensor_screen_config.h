#ifdef CONFIG_INCLUDE_HEADER
#include "gnss_demo.h"
#include "bt_audio.h"
#endif

#ifdef CONFIG_INCLUD_BODY
// add your screen here
{show_gnss_screen, gnss_event_handler, "GNSS demo"},
{show_bt_audio_screen, bt_audio_event_handler, "BT Audio"},

#endif

#ifdef CONFIG_MESSAGE_ID_ENUM
// define your own message bellowing here
//GNSS message
MESSAGE_ID_GNSS_POSITION,
MESSAGE_ID_GNSS_NMEA,
MESSAGE_ID_BT_AUDIO,
MESSAGE_ID_WATCH_FACE,

#endif
