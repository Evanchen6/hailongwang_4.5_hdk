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
#include "gdi_resource_internal.h"

extern const uint8_t ____________DEFAULT_RESOURCE__EMPTYIMAGE_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_EMPTY_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_FULL_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_0_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_1_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_2_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_3_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_4_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_5_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_6_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_7_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_8_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_9_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_PERCENT_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_ALARM_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_GPS_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_HEART_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_0_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_1_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_2_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_3_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_4_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_5_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_6_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_7_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_8_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_9_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_0_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_1_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_2_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_3_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_4_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_5_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_6_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_7_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_8_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_9_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__LINE_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__LIST_HISTORY_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__LIST_PERSON_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__LIST_SETTING_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__LIST_TYPE_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__MENU_BG_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__MENU_DOWN_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__MENU_TITLE_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__MENU_UP_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__POP_UP_BMP[] ;
extern const uint8_t ________________CUSTOM_RESOURCE__IMAGES__POP_UP_BG_BMP[] ;
