#ifdef CONFIG_INCLUDE_HEADER
#include "traing_running.h"
#include "traing_swim.h"
#include "traing_3km.h"
#include "sensor_demo.h"
#include "gnss_demo.h"
#endif


#ifdef CONFIG_INCLUD_BODY
// add your screen here
{show_running_screen, running_event_handler, {0xD1,0x8D,0x65,0x6B,0x00}},
{show_swim_screen, NULL, {0x38,0x6E,0xF3,0x6C,0x00}},
{show_running_3km_screen, running_3km_event_handler, {0x09,0x4E,0x6C,0x51,0xCC,0x91,0x00}},
{show_sensor_ready_to_connect_screen, sensor_event_handler, {0xE1,0x4F,0x6F,0x60,0x00}},
{show_gnss_screen, gnss_event_handler, {0x4D,0x4F,0x6E,0x7F,0xF6,0x65,0xF4,0x95,0x00}},

#endif

#ifdef CONFIG_MESSAGE_ID_ENUM
// define your own message bellowing here
//GNSS message
MESSAGE_ID_TRAING_3KM,
MESSAGE_ID_TRAING_RUNNING,

#endif

