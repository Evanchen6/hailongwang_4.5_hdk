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
const uint16_t  gdi_resource_current_max_image_number=105;
#include "custom_image_data_resource.h"

const gdi_resource_custom_image_t	gdi_resource_custom_image_names[]={
{(uint8_t*)&____________DEFAULT_RESOURCE__EMPTYIMAGE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_25_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_50_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_75_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_EMPTY_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_FULL_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_0_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_1_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_2_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_3_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_4_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_5_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_6_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_7_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_8_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_9_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__BATTERY_NUMBER_PERCENT_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_ALARM_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_DATE_NUMBER_0_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_DATE_NUMBER_1_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_DATE_NUMBER_2_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_DATE_NUMBER_3_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_DATE_NUMBER_4_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_DATE_NUMBER_5_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_DATE_NUMBER_6_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_DATE_NUMBER_7_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_DATE_NUMBER_8_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_DATE_NUMBER_9_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_DATE_NUMBER_LINE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_GPS_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_HEART_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_COLON_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_COLON_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_0_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_0_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_1_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_1_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_2_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_2_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_3_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_3_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_4_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_4_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_5_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_5_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_6_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_6_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_7_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_7_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_8_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_8_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_9_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_HOUR_9_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_0_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_0_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_1_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_1_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_2_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_2_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_3_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_3_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_4_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_4_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_5_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_5_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_6_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_6_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_7_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_7_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_8_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_8_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_9_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_TIME_NUMBER_MINUTE_9_BLUE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_FRI_CN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_FRI_EN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_MON_CN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_MON_EN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_SAT_CN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_SAT_EN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_SUN_CN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_SUN_EN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_THUR_CN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_THUR_EN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_TUES_CN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_TUES_EN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_WED_CN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__IDLE_WEEK_WED_EN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__LINE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__LIST_1TYPE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__LIST_2PERSON_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__LIST_3SETTING_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__LIST_4HISTORY_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__LIST_5HISTORY_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__MENU_BG_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__MENU_DOWN_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__MENU_TITLE_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__MENU_UP_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__POP_UP_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__POP_UP_BG_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__ZBG_01_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__ZBG_02_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__ZBG_03_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__ZBG_04_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__ZBG_05_BMP},
{(uint8_t*)&________________CUSTOM_RESOURCE__IMAGES__ZBG_06_BMP},
};



