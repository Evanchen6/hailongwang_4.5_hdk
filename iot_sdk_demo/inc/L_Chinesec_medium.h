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

const uint16_t AChinese32_RangeOffset[24]= {
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
16,17,18,19,20,21,22,23,};

const uint8_t  AChinese32_Data[3264]= {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xC0,0xFF,0xFF,0xFF,0x3,0xFF,0xFF,0xFF,
0xF,0xFC,0xFF,0xFF,0x3F,0xF0,0xFF,0xFF,0xFF,0x0,0x0,0x7E,0x0,0x0,0x0,0xF0,
0x1,0x0,0x0,0xC0,0x7,0x0,0x0,0x0,0x1F,0x0,0x0,0x0,0x7C,0x0,0x0,0x0,
0xF0,0x1,0x0,0x0,0xC0,0x7,0x0,0xF8,0xFF,0xFF,0xFF,0xE1,0xFF,0xFF,0xFF,0x87,
0xFF,0xFF,0xFF,0x1F,0xFE,0xFF,0xFF,0x7F,0x0,0x80,0x1F,0x0,0x0,0x0,0x7C,0x0,
0x0,0x0,0xF0,0x1,0x0,0x0,0xC0,0x7,0x0,0x0,0x0,0x1F,0x0,0x0,0x0,0x7C,
0x0,0x0,0x0,0xF0,0x1,0x0,0x0,0xC0,0x7,0x0,0x0,0x0,0x1F,0x0,0x0,0x0,
0x7C,0x0,0x0,0x0,0xFF,0x1,0x0,0x0,0xFC,0x7,0x0,0x0,0xF0,0x1F,0x0,0x0,
0xC0,0x3F,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x3E,0x80,0xF,0x0,0xF8,0x7C,0x3E,0x0,0xE0,0xF1,0xF8,0x0,0xC0,0xE7,0xE3,
0x3,0x0,0x9F,0x8F,0xF,0x0,0x3E,0xFE,0xFF,0xF,0xF8,0xFC,0xFF,0x3F,0xF0,0xF3,
0xFF,0xFF,0xE0,0xC7,0xFF,0xFF,0x83,0xF,0xF,0x3E,0x0,0x3E,0x1C,0xF8,0x0,0xF8,
0x33,0xE0,0x3,0xE0,0xF,0x80,0xF,0x80,0x3E,0x0,0x3E,0x0,0xF8,0x0,0xF8,0x0,
0xE0,0x3,0xE0,0x3,0x80,0xF,0x80,0xF,0x0,0x3E,0x0,0x3E,0x0,0xF8,0xF8,0xFF,
0x7F,0xE0,0xE3,0xFF,0xFF,0x81,0x8F,0xFF,0xFF,0x7,0x3E,0xFE,0xFF,0x1F,0xF8,0x0,
0xFC,0x0,0xE0,0x3,0xE0,0x3,0x80,0xF,0x80,0xF,0x0,0x3E,0x0,0x3E,0x0,0xF8,
0x0,0xF8,0x0,0xE0,0x3,0xE0,0x3,0x80,0x7,0x80,0xF,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3F,0x0,0x7E,0x0,0xF8,0x1,0xF8,
0x1,0xC0,0xF,0xF0,0x3,0x0,0x7F,0xE0,0x7,0xC0,0xFF,0xFF,0xFF,0x7,0xFF,0xFF,
0xFF,0x1F,0xFC,0xFF,0xFF,0x7F,0xF0,0xFF,0xFF,0xFF,0x1,0x80,0x7F,0x0,0x0,0x0,
0xF8,0x1,0x0,0x0,0xE0,0x7,0x0,0x0,0x80,0x1F,0x0,0x0,0x0,0x7E,0x0,0x80,
0xFF,0xFF,0xFF,0x1F,0xFE,0xFF,0xFF,0x7F,0xF8,0xFF,0xFF,0xFF,0xE1,0xFF,0xFF,0xFF,
0x7,0x0,0xFC,0x3,0x0,0x0,0xF8,0x1F,0x0,0x0,0xF0,0xFF,0x0,0x0,0xE0,0xFF,
0x7,0x0,0xC0,0x9F,0x3F,0x0,0xC0,0x7F,0xFC,0x1,0xC0,0x7F,0xE0,0xF,0xC0,0xFF,
0x0,0x7F,0x0,0xFF,0x1,0xF8,0x3,0xFC,0x1,0xC0,0xF,0xF0,0x3,0x0,0x7F,0xC0,
0x1,0x0,0xF8,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0xFF,0xFF,0xFF,0x1,0xFE,0xFF,0xFF,0x7,0xF8,0xFF,0xFF,0x1F,0xE0,0xFF,0xFF,
0x7F,0x80,0xF,0x0,0xF0,0x1,0x3E,0x0,0xC0,0x7,0xF8,0x0,0x0,0x1F,0xE0,0xFF,
0xFF,0x7F,0x80,0xFF,0xFF,0xFF,0x1,0xFE,0xFF,0xFF,0x7,0xF8,0xFF,0xFF,0x1F,0x0,
0x0,0x0,0x0,0xE0,0xFF,0xFF,0xFF,0x87,0xFF,0xFF,0xFF,0x1F,0xFE,0xFF,0xFF,0x7F,
0xF8,0xFF,0xFF,0xFF,0x1,0x7E,0x0,0x0,0x0,0xFC,0x0,0x0,0x0,0xF0,0x3,0x0,
0x0,0xE0,0xFF,0xFF,0x7F,0x80,0xFF,0xFF,0xFF,0x1,0xFC,0xFF,0xFF,0x7,0x0,0x0,
0x80,0x1F,0x0,0x0,0x0,0x7C,0x0,0x0,0x0,0xF0,0x1,0xF0,0xFF,0xFF,0x7,0xC0,
0xFF,0xFF,0x1F,0x0,0xFF,0xFF,0x7F,0x0,0xFC,0xFF,0xFF,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xC0,0xFF,0x9F,0xE7,0x3,0xFF,0x7F,0x9E,
0xF,0xFC,0xFF,0x79,0x3E,0xF0,0xFF,0xE7,0xF9,0x80,0xCF,0x87,0xE7,0x3,0x3E,0x1F,
0x9E,0xF,0xF8,0x7C,0x78,0x3E,0xF8,0xFF,0xE7,0xF9,0xE0,0xFF,0x9F,0xE7,0x83,0xFF,
0x7F,0x9E,0xF,0xF8,0x7E,0x78,0x3E,0xE0,0xF3,0xE1,0xF9,0x80,0xCF,0x87,0xE7,0x3,
0x1E,0x1F,0x9E,0xF,0x7C,0x7C,0x78,0x1E,0xF0,0xF1,0xE1,0x79,0x0,0x0,0x0,0x0,
0x0,0x0,0xF8,0x1,0x0,0x0,0xE0,0x7,0x0,0xE0,0xFF,0xFF,0x7F,0x80,0xFF,0xFF,
0xFF,0x1,0xFE,0xFF,0xFF,0x7,0x0,0xF8,0x7,0x0,0x0,0x80,0x1F,0x0,0x0,0x0,
0x7E,0x0,0x80,0xFF,0xFF,0xFF,0x1F,0xFE,0xFF,0xFF,0x7F,0xF8,0xFF,0xFF,0xFF,0xE1,
0xFF,0xFF,0xFF,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x7C,0x0,0x0,0xFC,0xFF,0xFF,0x1F,0xFC,0xFF,0xFF,0x7F,0xF0,0xFF,0xFF,
0xFF,0xE1,0xFF,0xFF,0xFF,0x87,0xF,0x0,0x0,0x0,0x3E,0xFF,0xFF,0x3,0xF8,0xFC,
0xFF,0x3F,0xE0,0xF3,0xFF,0xFF,0x81,0xCF,0xFF,0xFF,0x7,0x3E,0x0,0xC0,0x1F,0xF8,
0x0,0x80,0x3F,0xE0,0xC3,0xF,0x7E,0x80,0xF,0x7F,0xFE,0x0,0x3E,0xFF,0xFF,0xF,
0xF8,0xFC,0xFF,0x7F,0xE0,0xF3,0xFF,0xFF,0x83,0xCF,0xFF,0xFF,0xF,0x3E,0x80,0x1F,
0x3F,0xF8,0x0,0x7C,0xF8,0xE0,0x3,0xF0,0xE1,0x83,0xF,0xC0,0x87,0xF,0x3E,0x0,
0x1F,0x3E,0xF8,0x0,0x7C,0xF8,0xE0,0x3,0xF0,0xE1,0x83,0xF,0xFE,0x7,0x0,0x3E,
0xF8,0x1F,0x0,0xF8,0xE0,0x7F,0x0,0xE0,0x81,0xFF,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x7F,0x0,0xF8,0x0,0xFF,0x3,0xE0,
0x3,0xFE,0xCF,0xFF,0x7F,0xF8,0x7F,0xFF,0xFF,0xE1,0xF3,0xFD,0xFF,0x87,0xCF,0xF7,
0xFF,0x1F,0x3E,0x1F,0xC0,0xF,0xF8,0x7C,0x0,0x3E,0xE0,0xF3,0x1,0xF8,0x80,0xCF,
0x77,0xE0,0x3,0x3E,0x9F,0x87,0xF,0xF8,0x7C,0x3E,0x3E,0xE0,0xFF,0xF9,0xF8,0x80,
0xFF,0xE7,0xE3,0x3,0xFE,0x9F,0x8F,0xF,0xF8,0x7F,0x3C,0x3E,0xE0,0xFB,0xF1,0xF9,
0x80,0xCF,0xC7,0xE7,0x3,0x3E,0x1F,0x9F,0xF,0xF8,0x7C,0x7C,0x3E,0xE0,0xF3,0xE1,
0xF9,0x80,0xCF,0x7,0xE0,0x3,0x3E,0x1F,0x80,0xF,0xF8,0x7C,0x0,0x3E,0xE0,0xF3,
0x1,0xF8,0x80,0xFF,0x7,0xFC,0x3,0xFE,0x1F,0xF0,0xF,0xF8,0x7F,0xC0,0x3F,0xE0,
0xFF,0x1,0x7F,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0xFF,0xFF,0x7F,0x0,0xFE,0xFF,0xFF,0x3,0xF8,0xFF,0xFF,0x1F,0xE0,0xFF,0xFF,
0x7F,0x80,0xF,0x0,0xF0,0x1,0xFE,0xFF,0xFF,0x7,0xF8,0xFF,0xFF,0x1F,0xE0,0xFF,
0xFF,0x7F,0x80,0xFF,0xFF,0xFF,0x1,0x3E,0x0,0xC0,0x7,0xF8,0x0,0x0,0x1F,0xE0,
0xFF,0xFF,0x7F,0x80,0xFF,0xFF,0xFF,0x1,0xFE,0xFF,0xFF,0x7,0xF8,0xFF,0xFF,0x1F,
0x0,0x0,0x0,0x0,0x0,0xE0,0xE3,0x7,0x0,0x9F,0x8F,0x9F,0xF,0x7C,0x3E,0x7E,
0x3E,0xF0,0xFB,0xF8,0x7D,0x80,0xFF,0xE3,0xFF,0x1,0xFE,0x8F,0xFF,0x3,0xF8,0x3F,
0xFE,0xF,0x80,0xFF,0xF8,0xF,0x0,0xE0,0xE3,0x7,0x80,0xFF,0xFF,0xFF,0x1F,0xFE,
0xFF,0xFF,0x7F,0xF8,0xFF,0xFF,0xFF,0xE1,0xFF,0xFF,0xFF,0x3,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7C,0x0,0x0,0x0,0xF0,0x1,
0x0,0xFE,0xFF,0x7,0x0,0xF8,0xFF,0xFF,0xFF,0xE1,0xFF,0xFF,0xFF,0x87,0xFF,0xFF,
0xFF,0x1F,0xFE,0xFF,0xFF,0x7F,0x80,0x8F,0x1F,0x1F,0x0,0x3E,0x7E,0x7C,0x0,0xF8,
0xF0,0xF1,0x1,0xF0,0xC3,0xC7,0x7,0xC0,0x7,0x1F,0x3F,0x0,0x1F,0x7C,0xF8,0x0,
0x7C,0xF0,0xE1,0x3,0xF0,0xC1,0x87,0xF,0xC0,0x7,0x1F,0x3E,0x80,0xF,0x7C,0xF8,
0x1,0x3E,0xF0,0xE1,0x7,0xF8,0xC0,0x7,0x1F,0xE0,0x3,0x1F,0x7C,0x80,0xF,0x7C,
0xF0,0x1,0x3F,0xF0,0xC1,0x7,0x7C,0xC0,0x7,0x3F,0xF0,0xF9,0xFF,0xF9,0xC0,0xE7,
0xFF,0xE7,0x3,0x9F,0xFF,0x9F,0xF,0x7C,0xFE,0x7F,0x3E,0xF8,0x81,0x1F,0xF8,0x1,
0x0,0x7E,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x7C,0x0,0x0,0x7C,0xF0,0x1,0x0,0xF0,0xC1,0xFF,0x3F,0xC0,0x7,0xFF,
0xFF,0x0,0x1F,0xFC,0xFF,0x3,0x7C,0xF0,0xFF,0xF,0xF0,0xC1,0x7,0x0,0xC0,0x7,
0x1F,0x0,0xE0,0xFF,0xFF,0xFF,0x87,0xFF,0xFF,0xFF,0x1F,0xFE,0xFF,0xFF,0x7F,0xF8,
0xFF,0xFF,0xFF,0xE1,0xFF,0xFF,0xFF,0x7,0x0,0xF8,0x1,0x0,0x0,0xE0,0x7,0x3E,
0x80,0x87,0x1F,0xF8,0x0,0x3F,0x7C,0xF0,0x3,0xFC,0xF0,0xC1,0x7,0xF0,0xC3,0x87,
0x1F,0xC0,0xF,0x1F,0x7E,0x0,0x1E,0x7C,0xFC,0x0,0x0,0xF0,0xF9,0x3,0x0,0xC0,
0xF7,0x7,0x0,0x0,0xF0,0xF,0x0,0x0,0xFC,0x1F,0x0,0xFF,0xFF,0x3F,0x0,0xFC,
0xFF,0x7F,0x0,0xF0,0xFF,0x7F,0x0,0xC0,0xFF,0x3F,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x83,0xFF,0xFF,0x1,0x1F,0xFE,0xFF,
0x7,0x7E,0xF8,0xFF,0x1F,0xF0,0xE1,0xFF,0x7F,0xC0,0x7,0x0,0x0,0x0,0x6,0x0,
0x0,0x0,0x0,0xF8,0xF,0x0,0x8,0xE0,0xFF,0x0,0xE0,0x80,0xFF,0xE7,0x83,0xF,
0xFE,0x9F,0xF,0x3E,0x0,0x7E,0x3F,0xF8,0x1,0xF0,0xFD,0xE0,0xC7,0xC7,0xE7,0x3,
0x3E,0x3F,0x9F,0x7,0xF8,0xFC,0x7D,0x1E,0xE0,0xF3,0xF7,0x79,0x80,0xF,0xCF,0xE7,
0x1,0x3E,0x3C,0x9F,0xF,0xF8,0xF8,0x7C,0x3E,0xE0,0xE3,0xF3,0xF9,0x80,0x8F,0xCF,
0xE7,0x3,0x3E,0x3E,0x9F,0xF,0xF8,0x78,0x7C,0x3E,0xF0,0xF1,0xF1,0xF1,0xC0,0xC7,
0xC7,0xC7,0x3,0x1F,0xDF,0x1F,0xF,0x7C,0x7C,0x7F,0x3C,0xF0,0xF1,0xFC,0xF1,0xE1,
0xE3,0xF3,0xC3,0x7,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0xC0,0x83,0xF,0x1F,0x0,0x1F,0x3E,0x7C,0x0,0x7E,0xFF,0xF7,0x3F,0xF0,0xFD,0xDF,
0xFF,0xC0,0xF3,0x7F,0xFF,0x3,0xC0,0xFF,0xF9,0xF,0x0,0x3E,0x0,0x0,0x8,0xF8,
0x0,0x0,0xE0,0xE0,0x3,0xFF,0x83,0x87,0x7F,0xFC,0xF,0x3E,0xFE,0xF3,0x3F,0xF8,
0xF9,0xDF,0xFF,0xE0,0xE7,0x7F,0xF0,0x3,0x9F,0xE7,0xC1,0x7,0xF8,0x9E,0x87,0x1F,
0xE0,0x7B,0x1E,0x3E,0x80,0xEF,0x79,0xF8,0x0,0xBE,0xE7,0xFD,0x1F,0xF8,0x9E,0xF7,
0x7F,0xE0,0x7B,0xDE,0xFF,0x81,0xE7,0x79,0xFF,0x7,0x9E,0xE7,0xE1,0x3,0x78,0x9E,
0x87,0xF,0xF0,0x79,0x1E,0x3E,0xC0,0xE7,0x79,0xF8,0x0,0x9F,0xE7,0xF9,0x3,0x3C,
0x9E,0xE7,0xF,0xF0,0x78,0x9E,0x3F,0xE0,0xE3,0x79,0x7E,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xE0,0xF3,0xF0,0xFF,0x83,0xCF,0xE3,0xFF,
0xF,0xBE,0x9F,0xFF,0x3F,0xF8,0x3C,0xFE,0x7F,0xE0,0xF3,0x78,0x0,0x80,0xF,0xE0,
0x1,0x0,0x3E,0x80,0x7,0x0,0xF8,0xFF,0xFE,0x7F,0xE0,0xFF,0xFB,0xFF,0x83,0xFF,
0xEF,0xFF,0xF,0xFE,0xBF,0xFF,0x3F,0xF8,0x0,0x1E,0xF8,0xE0,0x3,0xF8,0xE7,0x83,
0xF,0xE0,0xBF,0x7,0xFE,0x8F,0xFF,0x1F,0xF8,0x7F,0xDE,0x7F,0xE0,0xFF,0x79,0xFF,
0x80,0xFF,0xE7,0xF9,0x3,0x3E,0x9F,0xE7,0xF,0xF8,0x7C,0x1E,0x1F,0xE0,0xF3,0x79,
0x7C,0x80,0xCF,0xE7,0xF1,0x3,0x3E,0x9F,0xE7,0xF,0xF8,0x7C,0x9E,0x3F,0xE0,0xF3,
0x79,0xFF,0x81,0xCF,0xE7,0xFD,0x7,0x3E,0x9F,0xF7,0x3E,0xF8,0x7C,0xFE,0xFB,0xE0,
0xF1,0xB9,0xCF,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0xC0,0xFF,0xFF,0xFF,0x3,0xFF,0xFF,0xFF,0xF,0xFC,0xFF,0xFF,0x3F,0xF0,0xFF,0xFF,
0xFF,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xF8,0xFF,
0xFF,0xFF,0xE1,0xFF,0xFF,0xFF,0x87,0xFF,0xFF,0xFF,0x1F,0xFE,0xFF,0xFF,0x7F,0x0,
0xE0,0x1F,0x0,0x0,0x0,0x7E,0x0,0x0,0x7C,0xF8,0xE1,0x1,0xF0,0xE1,0x87,0xF,
0xC0,0x87,0x1F,0x7E,0x80,0x1F,0x7E,0xF8,0x1,0x3E,0xF8,0xC1,0x7,0xF8,0xE0,0x7,
0x1F,0xE0,0x83,0x1F,0x7C,0x80,0xF,0x7E,0xF0,0x1,0x3E,0xF8,0xC1,0xF,0xF8,0xE0,
0x7,0x3F,0xE0,0x83,0x1F,0xF8,0xC0,0xF,0x7E,0xE0,0x3,0x1F,0xF8,0x81,0xF,0x7C,
0xE0,0x7,0x3E,0xF0,0x81,0x1F,0xF8,0x1,0x0,0x7E,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1F,0x3E,0xF8,0x0,0xFC,0xF8,0xF0,
0x3,0xF0,0xE3,0xC3,0xF,0x80,0xBF,0xCF,0x1F,0xE0,0xFF,0xFF,0xFF,0x83,0xFF,0xFF,
0xFF,0xF,0xFE,0xFF,0xFF,0x3F,0xF8,0xFF,0xFF,0xFF,0x0,0x0,0x3F,0x0,0x0,0xFC,
0xF8,0xF8,0x1,0xF0,0xE1,0xC3,0xF,0xE0,0x87,0xF,0x3F,0x80,0xF,0x3E,0xF8,0x1,
0x3E,0xF8,0xC0,0x7,0xFC,0xE0,0x3,0x3F,0x0,0x0,0x0,0x0,0x0,0x0,0x7E,0x0,
0x80,0xFF,0xFF,0xFF,0xF,0xFE,0xFF,0xFF,0x3F,0xF8,0xFF,0xFF,0xFF,0xE0,0xFF,0xFF,
0xFF,0x3,0x0,0xFE,0x0,0x0,0x0,0xFC,0x1,0x0,0x0,0xFC,0xFF,0x3,0x0,0xFF,
0xC7,0x1F,0x0,0xFF,0xF,0xFE,0x0,0xFC,0xF,0xF0,0x7,0xF0,0xF,0x80,0x7F,0xC0,
0x3,0x0,0xF8,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0xE0,0xFF,0xFF,0xFF,0x83,0xFF,0xFF,0xFF,0xF,0xFE,0xFF,0xFF,0x3F,0xF8,0xFF,0xFF,
0xFF,0x0,0xE0,0x3F,0x0,0x0,0xE0,0x3F,0x0,0x0,0xE0,0x3F,0x0,0x0,0xC0,0x3F,
0xF0,0x7F,0x80,0xFF,0xFF,0x3F,0x0,0xFE,0xFF,0x3F,0x0,0xF8,0xFF,0x3F,0x0,0x80,
0xFF,0x3F,0x0,0x0,0xE0,0x3F,0x7C,0x0,0xE0,0x3F,0xF0,0x1,0xE0,0x7F,0x80,0xF,
0xE0,0x7F,0x0,0x3E,0x80,0xFF,0xFF,0xFF,0x1,0xFE,0xFF,0xFF,0x7,0xF8,0xFF,0xFF,
0x1F,0x80,0xFF,0xFF,0x3F,0x0,0x0,0x3E,0x0,0x0,0x3E,0xF8,0xE0,0x3,0xF8,0xE0,
0x83,0xF,0xE0,0x83,0xF,0x3E,0x80,0xF,0x3E,0xF8,0x1,0x3F,0xF8,0xC0,0x7,0x7C,
0xE0,0x3,0x1F,0xF0,0x81,0xF,0xFC,0xC0,0x7,0x3E,0xE0,0x3,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0xF8,0x0,0x0,0x7E,0xF0,0x1,0x0,0xF8,0xFC,0xFF,
0xF,0xF0,0xF3,0xFF,0x3F,0xC0,0xC7,0xFF,0xFF,0x80,0x1F,0xFF,0xFF,0x3,0x3F,0xFC,
0xFF,0xF,0xFC,0x80,0xF,0x0,0xF8,0xFF,0xFF,0x1,0xE0,0xFF,0xFF,0xF,0x80,0xFF,
0xFF,0x3F,0x0,0xFC,0xFF,0xFF,0x1,0x0,0x9F,0xEF,0x7,0x0,0x7E,0xBE,0x1F,0x0,
0xF8,0xF8,0xFF,0xF,0xF0,0xE3,0xFF,0x3F,0xC0,0x87,0xFF,0xFF,0x80,0x1F,0xFC,0xFF,
0x3,0x3F,0x0,0x7E,0x0,0x7C,0xC0,0xFB,0x1D,0xF8,0x1F,0xEF,0xF7,0xE0,0x7F,0xBE,
0xDF,0x3,0xFF,0xF9,0x7E,0xF,0xF8,0xE7,0xFB,0x3D,0x0,0x80,0xEF,0xF7,0x0,0x0,
0x9E,0xDF,0x3,0xFF,0x7B,0x7E,0xF,0xFC,0xEF,0xF9,0x3D,0xF0,0xBF,0xE7,0xF7,0xC0,
0x7F,0x9E,0x1F,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x3E,0xC0,0x7,0x0,0xFC,0xFC,0xFF,0xF,0xF0,0xF1,0xFF,0x3F,0xE0,0xC7,0xFF,
0xFF,0x80,0xF,0xFF,0xFF,0x3,0x3F,0xC0,0xF,0x0,0x7C,0x80,0x1F,0x0,0xF8,0x1F,
0x3E,0x3E,0xE0,0x7F,0xFC,0xF0,0x81,0xFF,0xF9,0xC1,0x7,0xFC,0xE7,0x7,0x1F,0x80,
0xCF,0xFF,0xFF,0x0,0x3E,0xFF,0xFF,0x3,0x7C,0xF8,0xFF,0xF,0xF0,0xC1,0xFF,0x7C,
0xE0,0x3,0x0,0x0,0x80,0xF,0xFC,0x7C,0x0,0x1F,0xF0,0xF1,0x1,0x7C,0xC0,0xC7,
0x7,0xF8,0x1F,0x1F,0x1F,0xE0,0x7F,0x7C,0x7C,0x0,0xFF,0xF9,0xF0,0x1,0xF8,0xE7,
0xC3,0x7,0x0,0x80,0xF,0x1F,0x0,0x0,0x3E,0x7C,0x80,0xFF,0x7F,0xF0,0xF,0xFE,
0xFF,0xC1,0x3F,0xF8,0xFF,0x7,0xFF,0xE0,0xFF,0xF,0xF8,0x3,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0xFF,0xFF,0xFF,0x1,0xFF,0xFF,0xFF,
0xF,0x7C,0x7F,0x3F,0x3F,0xF0,0xF1,0xF9,0xF8,0xC0,0xFF,0xFF,0xFF,0x3,0xFF,0xFF,
0xFF,0xF,0xFC,0xFF,0xFF,0x3F,0x0,0x80,0x1F,0x0,0xE0,0xFF,0xFF,0xFF,0x87,0xFF,
0xFF,0xFF,0x1F,0x0,0xF0,0xFF,0x7F,0x0,0xE0,0x7,0x0,0x0,0xFF,0xFF,0xFF,0x0,
0xFC,0xFF,0xFF,0x7,0xF8,0x0,0xC0,0x1F,0xE0,0x3,0x0,0x7C,0x80,0xFF,0xFF,0xFF,
0x1,0xFE,0xFF,0xFF,0x7,0xF8,0x0,0x0,0x1F,0xE0,0xFF,0xFF,0x7F,0x80,0xFF,0xFF,
0xFF,0x1,0x3E,0x0,0xE0,0x7,0xF8,0x0,0x0,0x1F,0xE0,0xFF,0xFF,0x7F,0x80,0xFF,
0xFF,0xFF,0x1,0x3E,0x0,0xC0,0x7,0xFE,0xFF,0xFF,0x7F,0xF8,0xFF,0xFF,0xFF,0xE1,
0xFF,0xFF,0xFF,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x7,0x9F,0xCF,0x7,0x3E,0x7C,0x3E,0x1F,0xFC,0xF0,0xF9,0x7C,0xF0,0xC3,0xE7,
0xF3,0x81,0x7,0x9F,0xCF,0x7,0x0,0x7C,0x3E,0x1F,0x0,0xF0,0xF9,0x7C,0x0,0xC0,
0xE7,0xF3,0xE1,0xF,0x9F,0xCF,0x87,0x7F,0x7C,0x3E,0x1F,0xFE,0xF3,0xF9,0x7C,0xF8,
0xCF,0xE7,0xF3,0x1,0x3F,0x9F,0xCF,0x7,0xF8,0x7C,0x3E,0x1F,0xE0,0xF3,0xF9,0x7C,
0x80,0xCF,0xE7,0xF3,0x1,0x3E,0x9F,0xCF,0x7,0xF8,0x7C,0x3E,0x1F,0xE0,0xF3,0xF9,
0x7C,0x80,0xCF,0xE7,0xF3,0x1,0x3E,0x9F,0xCF,0x7,0xF8,0x7C,0x3E,0x1F,0xE0,0xF3,
0xF9,0x7C,0x80,0xCF,0xE7,0xF3,0x1,0x3E,0x9F,0xCF,0x7,0xF8,0x7F,0x3E,0x1F,0xE0,
0xFF,0xF9,0x7C,0x80,0xFF,0xE3,0xF3,0x1,0xFC,0x87,0xCF,0x3,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0xF,0xFC,0xFF,0x0,0x3E,0xF8,0xFF,
0x7,0xF8,0xE1,0xFF,0x1F,0xE0,0x83,0xFF,0x7F,0x80,0xF,0x3E,0xF0,0x1,0x0,0xF8,
0xC0,0x7,0x0,0xE0,0x3,0x1F,0xF8,0x83,0x7,0xFC,0xE1,0x1F,0x1F,0xF0,0x87,0x7F,
0x7C,0xC0,0x1F,0xFE,0xF1,0x1,0x7E,0xC0,0x7,0x0,0x0,0x0,0x1F,0x0,0x0,0x0,
0x7C,0xFC,0xFF,0xF,0xF0,0xF1,0xFF,0x3F,0xC0,0xC7,0xFF,0xFF,0x0,0x1F,0xFF,0xFF,
0x3,0x7C,0x0,0xC0,0xF,0xF0,0x81,0x8F,0x1F,0xC0,0x7,0xFF,0x3E,0x0,0x1F,0xFE,
0x7F,0x0,0x7C,0xFC,0xFF,0x1,0xF0,0xF1,0xF8,0x3,0xC0,0xC7,0xC3,0xF,0x0,0x1F,
0x8F,0xFF,0x3,0xFC,0xFD,0xFF,0x1F,0xF0,0xE7,0xFF,0x7F,0xC0,0x9F,0xFF,0xFC,0x1,
0x7E,0xF8,0xC1,0x7,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x80,0x7F,0x3E,0x0,0x0,0xFF,0xFB,0xFF,0x1,0xFE,0xFF,0xFF,0x1F,0x78,0xFE,0xFF,
0xFF,0xE0,0xE1,0xFD,0xFF,0x83,0x87,0xE7,0xFF,0xF,0x1E,0x1E,0x0,0x3C,0x78,0x78,
0x0,0xF0,0xE0,0xFF,0xF9,0xCF,0x83,0xFF,0xF7,0x7F,0xF,0xFE,0xFF,0xFF,0x3D,0xF8,
0xFF,0xFF,0xF7,0x0,0x3E,0xFE,0xDF,0x83,0xF1,0x78,0x78,0xF,0xDE,0xE3,0xE1,0x3D,
0x78,0x8F,0x87,0xF7,0xE0,0xFD,0x1E,0xDE,0x83,0xF7,0xFB,0x7F,0xF,0xDE,0xEF,0xFF,
0x3D,0x78,0xBF,0xFF,0xF7,0xE0,0x3D,0xFE,0xDF,0x83,0xF7,0xF8,0x7F,0xF,0xDE,0xE3,
0x1,0x1C,0x78,0x8F,0x7,0x0,0xE0,0x3D,0x1E,0x0,0x80,0xFF,0xFF,0xFF,0x1F,0xFE,
0xFF,0xFF,0x7F,0xF0,0x7F,0xFF,0xFF,0x81,0xFF,0xFD,0xFF,0x3,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1E,0xF8,0x0,0x0,0x7C,0xE0,0x3,
0x0,0xFC,0xBF,0xF,0x0,0xF0,0xFF,0xFE,0x7F,0xC0,0xFF,0xFB,0xFF,0x3,0xFF,0xEF,
0xFF,0xF,0xF8,0x0,0xFE,0x3F,0xE0,0x1,0x0,0xF0,0x80,0xFF,0xC0,0xC7,0x3,0xFF,
0x3,0x1F,0xF,0xFC,0xF,0x7C,0x3C,0xF0,0x3E,0xF0,0xF1,0xC0,0xFB,0xC0,0x7,0x80,
0xFF,0xF,0x1F,0x0,0xFE,0x3F,0x7C,0x0,0xF8,0xFF,0xF0,0x1F,0xC0,0xFF,0xC3,0xFF,
0x0,0xF0,0x83,0xFF,0x3,0x80,0xF,0xBE,0xF,0x0,0x3E,0xF8,0x7C,0xE0,0xFF,0xE3,
0xF3,0x81,0xFF,0xCF,0xC7,0x7,0xFE,0x3F,0x1F,0x1F,0xF8,0xFF,0x7C,0x78,0x0,0xFC,
0xF0,0xE1,0x3,0xE0,0xE3,0x83,0xF,0x80,0x8F,0xF,0x3E,0x0,0x3E,0x3E,0xF8,0x0,
0xF8,0xF8,0xC0,0x7,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x80,0xC7,0xFF,0xFF,0x0,0x1F,0xFF,0xFF,0xF,0xFC,0xFC,0xFF,0x3F,0xF0,0xF1,0xFF,
0xFF,0x80,0x7,0x0,0xF0,0x3,0x0,0x0,0x80,0xF,0x3E,0x0,0x0,0x3E,0xF8,0xF0,
0xFF,0xF8,0xE0,0xE3,0xFF,0xE7,0x83,0x8F,0xFF,0x9F,0xF,0x3E,0xFE,0x7F,0x3E,0xF8,
0x78,0xF8,0xF9,0xE0,0xE3,0xC1,0xE7,0x83,0x8F,0x7,0x9E,0xF,0x3E,0x1E,0x78,0x3E,
0xF8,0xF8,0xFF,0xF9,0xE0,0xE3,0xFF,0xE7,0x83,0x8F,0xFF,0x9F,0xF,0x3E,0xFE,0x7F,
0x3E,0xF8,0x78,0xF0,0xF9,0xE0,0xE3,0x81,0xE7,0x83,0x8F,0x7,0x9E,0xF,0x3E,0xFE,
0x7F,0x3E,0xF8,0xF8,0xFF,0xF9,0xE0,0xE3,0xFF,0xE7,0x83,0x8F,0xFF,0x9F,0xF,0x3E,
0xFE,0x7F,0x3E,0xF8,0x0,0x0,0xF8,0xE0,0x3,0x0,0xE0,0x1,0x0,0x0,0x0,0x0,};

const RangeData AChinese32_RangeData[24]={
{20110,20110},{20214,20214},{20851,20851},{21495,21495},{22411,22411},{24207,24207},{26102,26102},{26174,26174},{26412,26412},{27493,27493},
{27891,27891},{28216,28216},{29256,29256},{31034,31034},{31867,31867},{31995,31995},{32451,32451},{32479,32479},{32622,32622},{35757,35757},
{35774,35774},{36305,36305},{36719,36719},{38388,38388},};

const RangeDetails AChinese32_RangeInfo={
24,
AChinese32_RangeData
};

const sCustFontData Chinesec_medium = {
32, 34,
25, 6,
1, 136, 500,
(uint8_t*)NULL, (uint8_t*)NULL, (uint32_t*)NULL, (uint8_t*)AChinese32_Data, (uint16_t*)AChinese32_RangeOffset,
&AChinese32_RangeInfo,
0X00000000,
};
