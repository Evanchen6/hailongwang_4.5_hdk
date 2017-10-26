/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

#ifdef CONFIG_INCLUDE_HEADER
//#include "gnss_demo.h"
#include "traing_type.h"
//#include "bt_audio.h"
#include "sensor_demo.h"
#include "ble_pxp_app.h"
#include "wf_image.h"
#include "about_screen.h"
#include "setting_screen.h"
#include "system_screen.h"
#endif

#ifdef CONFIG_INCLUD_BODY
// add your screen here
{show_traing_type_screen, traing_type_event_handler, {0xAD,0x8B,0xC3,0x7E,0x7B,0x7C,0x8B,0x57,0x00}},
{show_system_screen, system_screen_event_handler, {0xFB,0x7C,0xDF,0x7E,0x00}},
//{show_gnss_screen, gnss_event_handler, {0xFB,0x7C,0xDF,0x7E,0x00}},
//{show_bt_audio_screen, bt_audio_event_handler, "APP2 Audio"},
//{ble_pxp_show_unconnected_screen, ble_pxp_screen_event_handler, "BLE PXP"},
{show_settings_screen, settings_screen_event_handler, {0xBE,0x8B,0x6E,0x7F,0x00}},
{wf_app_task_enable_show, wf_event_handler, {0xF6,0x65,0xF4,0x95,0x3E,0x66,0x3A,0x79,0x00}},
{show_about_screen, about_screen_event_handler, {0x73,0x51,0x8E,0x4E,0x00}},
//{show_sensor_ready_to_connect_screen, sensor_event_handler, {0x73,0x51,0x8E,0x4E,0x00}},


#endif

#ifdef CONFIG_MESSAGE_ID_ENUM
// define your own message bellowing here
//GNSS message
MESSAGE_ID_GNSS_POSITION,
MESSAGE_ID_GNSS_NMEA,
MESSAGE_ID_BT_AUDIO,
MESSAGE_ID_WATCH_FACE,
MESSAGE_ID_TRAING_3KM,
MESSAGE_ID_TRAING_RUNNING,

#endif

