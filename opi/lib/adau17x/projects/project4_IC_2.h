/*
 * File:           E:\projects\project4_IC_2.h
 *
 * Created:        Monday, December 28, 2020 9:00:39 PM
 * Description:    project4:IC 2 program data.
 *
 * This software is distributed in the hope that it will be useful,
 * but is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * This software may only be used to program products purchased from
 * Analog Devices for incorporation by you into audio products that
 * are intended for resale to audio product end users. This software
 * may not be distributed whole or in any part to third parties.
 *
 * Copyright ©2020 Analog Devices, Inc. All rights reserved.
 */
#ifndef __PROJECT4_IC_2_H__
#define __PROJECT4_IC_2_H__

#include "SigmaStudioFW.h"
#include "project4_IC_2_REG.h"

#define DEVICE_ARCHITECTURE_IC_2                  "ADAU176x"
#define DEVICE_ADDR_IC_2                          0x1

/* DSP Program Data */
#define PROGRAM_SIZE_IC_2 2780
#define PROGRAM_ADDR_IC_2 2048
ADI_REG_TYPE Program_Data_IC_2[PROGRAM_SIZE_IC_2] = {
0x00, 0x00, 0x00, 0x00, 0x00, 
0xFE, 0xE0, 0x00, 0x00, 0x00, 
0xFF, 0x34, 0x00, 0x00, 0x00, 
0xFF, 0x2C, 0x00, 0x00, 0x00, 
0xFF, 0x54, 0x00, 0x00, 0x00, 
0xFF, 0x5C, 0x00, 0x00, 0x00, 
0xFF, 0xF5, 0x08, 0x20, 0x00, 
0xFF, 0x38, 0x00, 0x00, 0x00, 
0xFF, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0xFE, 0xE8, 0x0C, 0x00, 0x00, 
0xFE, 0x30, 0x00, 0xE2, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0xFF, 0xE8, 0x07, 0x20, 0x08, 
0x00, 0x00, 0x06, 0xA0, 0x00, 
0xFF, 0xE0, 0x00, 0xC0, 0x00, 
0xFF, 0x80, 0x07, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0xFF, 0x00, 0x00, 0x00, 0x00, 
0xFE, 0xC0, 0x22, 0x00, 0x27, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0xFE, 0xE8, 0x1E, 0x00, 0x00, 
0xFF, 0xE8, 0x01, 0x20, 0x00, 
0xFF, 0xD8, 0x01, 0x03, 0x00, 
0x00, 0x07, 0xC6, 0x00, 0x00, 
0xFF, 0x08, 0x00, 0x00, 0x00, 
0xFF, 0xF4, 0x00, 0x20, 0x00, 
0xFF, 0xD8, 0x07, 0x02, 0x00, 
0xFD, 0xA5, 0x08, 0x20, 0x00, 
0x00, 0xB0, 0x00, 0xE2, 0x00, 
0xFD, 0xAD, 0x08, 0x20, 0x00, 
0x00, 0x78, 0x00, 0xE2, 0x00, 
0xFD, 0x25, 0x08, 0x20, 0x00, 
0x00, 0x40, 0x00, 0xE2, 0x00, 
0xFD, 0x2D, 0x08, 0x20, 0x00, 
0x00, 0x08, 0x00, 0xE2, 0x00, 
0x00, 0x20, 0x08, 0x20, 0x00, 
0x00, 0x10, 0x08, 0x34, 0x00, 
0x00, 0x05, 0x08, 0x22, 0x40, 
0x00, 0x0D, 0x08, 0x22, 0x00, 
0x00, 0x18, 0x00, 0xE2, 0x00, 
0x00, 0x28, 0x00, 0xF2, 0x00, 
0x00, 0x58, 0x09, 0x20, 0x00, 
0x00, 0x48, 0x09, 0x34, 0x00, 
0x00, 0x3D, 0x08, 0x22, 0x40, 
0x00, 0x45, 0x08, 0x22, 0x00, 
0x00, 0x50, 0x00, 0xE2, 0x00, 
0x00, 0x60, 0x00, 0xF2, 0x00, 
0x00, 0x90, 0x0A, 0x20, 0x00, 
0x00, 0x80, 0x0A, 0x34, 0x00, 
0x00, 0x75, 0x08, 0x22, 0x40, 
0x00, 0x7D, 0x08, 0x22, 0x00, 
0x00, 0x88, 0x00, 0xE2, 0x00, 
0x00, 0x98, 0x00, 0xF2, 0x00, 
0x00, 0xC8, 0x0B, 0x20, 0x00, 
0x00, 0xB8, 0x0B, 0x34, 0x00, 
0x00, 0xAD, 0x08, 0x22, 0x40, 
0x00, 0xB5, 0x08, 0x22, 0x00, 
0x00, 0xC0, 0x00, 0xE2, 0x00, 
0x00, 0xD0, 0x00, 0xF2, 0x00, 
0x00, 0xC0, 0x0C, 0x20, 0x00, 
0x00, 0x50, 0x0D, 0x22, 0x00, 
0x00, 0xE0, 0x00, 0xE2, 0x00, 
0x00, 0x88, 0x0C, 0x20, 0x00, 
0x00, 0x18, 0x0D, 0x22, 0x00, 
0x00, 0xE8, 0x00, 0xE2, 0x00, 
0x00, 0xE0, 0x0E, 0x20, 0x00, 
0x01, 0x00, 0x00, 0xE2, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xE8, 0x0F, 0x20, 0x00, 
0x01, 0x68, 0x00, 0xE2, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0x28, 0x3F, 0x20, 0x00, 
0x01, 0x20, 0x40, 0x22, 0x00, 
0x01, 0x10, 0x3F, 0x34, 0x00, 
0x01, 0x08, 0x40, 0x22, 0x00, 
0x01, 0x00, 0x3D, 0x22, 0x00, 
0x00, 0xF8, 0x3E, 0x22, 0x00, 
0x00, 0xF0, 0x3D, 0x22, 0x00, 
0x01, 0x18, 0x00, 0xE2, 0x00, 
0x01, 0x30, 0x00, 0xF2, 0x00, 
0x01, 0x48, 0x42, 0x20, 0x00, 
0x01, 0x38, 0x42, 0x34, 0x00, 
0x01, 0x18, 0x41, 0x22, 0x00, 
0x01, 0x10, 0x41, 0x22, 0x40, 
0x01, 0x40, 0x00, 0xE2, 0x00, 
0x01, 0x90, 0x3F, 0x40, 0x00, 
0x01, 0x50, 0x00, 0xF2, 0x00, 
0x01, 0x88, 0x40, 0x24, 0x00, 
0x01, 0x78, 0x3F, 0x34, 0x00, 
0x01, 0x70, 0x40, 0x22, 0x00, 
0x01, 0x68, 0x3D, 0x22, 0x00, 
0x01, 0x60, 0x3E, 0x22, 0x00, 
0x01, 0x58, 0x3D, 0x22, 0x00, 
0x01, 0x80, 0x00, 0xE2, 0x00, 
0x01, 0x98, 0x00, 0xF2, 0x00, 
0x01, 0xB0, 0x42, 0x20, 0x00, 
0x01, 0xA0, 0x42, 0x34, 0x00, 
0x01, 0x80, 0x41, 0x22, 0x00, 
0x01, 0x78, 0x41, 0x22, 0x40, 
0x01, 0xA8, 0x00, 0xE2, 0x00, 
0x01, 0x05, 0x08, 0x40, 0x00, 
0x01, 0xB8, 0x00, 0xF2, 0x00, 
0x01, 0x6D, 0x08, 0x24, 0x00, 
0x01, 0xD0, 0x00, 0xE2, 0x00, 
0x01, 0xF8, 0x3F, 0x20, 0x00, 
0x01, 0xF0, 0x40, 0x22, 0x00, 
0x01, 0xE0, 0x3F, 0x34, 0x00, 
0x01, 0xD8, 0x40, 0x22, 0x00, 
0x01, 0xD0, 0x43, 0x22, 0x00, 
0x01, 0xC8, 0x44, 0x22, 0x00, 
0x01, 0xC0, 0x43, 0x22, 0x00, 
0x01, 0xE8, 0x00, 0xE2, 0x00, 
0x02, 0x00, 0x00, 0xF2, 0x00, 
0x02, 0x18, 0x42, 0x20, 0x00, 
0x02, 0x08, 0x42, 0x34, 0x00, 
0x01, 0xE8, 0x45, 0x22, 0x00, 
0x01, 0xE0, 0x45, 0x22, 0x00, 
0x02, 0x20, 0x00, 0xF2, 0x00, 
0x02, 0x10, 0x00, 0xE2, 0x00, 
0xFF, 0xE8, 0x3A, 0x20, 0x00, 
0x02, 0xAD, 0x08, 0x22, 0x40, 
0x02, 0xA0, 0x00, 0xE2, 0x00, 
0x02, 0xAD, 0x08, 0x20, 0x00, 
0x02, 0xA0, 0x46, 0x22, 0x00, 
0x02, 0xB0, 0x00, 0xE2, 0x00, 
0x02, 0xB0, 0x00, 0xC0, 0x00, 
0x02, 0x17, 0xFF, 0x20, 0x00, 
0x02, 0x48, 0x00, 0xE2, 0x00, 
0x02, 0x48, 0x35, 0x60, 0x00, 
0x02, 0x48, 0x3C, 0x20, 0x00, 
0xFF, 0xE8, 0x39, 0x22, 0x00, 
0xFF, 0xF5, 0x08, 0x50, 0x00, 
0xFF, 0xE8, 0x36, 0x24, 0x48, 
0x02, 0x48, 0x00, 0xE4, 0x00, 
0x02, 0x30, 0x00, 0xE4, 0x00, 
0x02, 0x48, 0x00, 0xC0, 0x00, 
0x02, 0x4F, 0xFF, 0x20, 0x00, 
0x02, 0x28, 0x00, 0xE2, 0x00, 
0x02, 0x28, 0x00, 0xC0, 0x00, 
0x02, 0x4F, 0xFF, 0x20, 0x00, 
0x02, 0x28, 0x00, 0xE2, 0x00, 
0x02, 0x28, 0x00, 0xC0, 0x00, 
0x02, 0x2F, 0xFF, 0x20, 0x00, 
0x02, 0x48, 0x00, 0xE2, 0x00, 
0xFF, 0xE8, 0x37, 0x20, 0x40, 
0x02, 0x35, 0x08, 0x22, 0x00, 
0x02, 0x30, 0x00, 0xE2, 0x00, 
0x02, 0x30, 0x00, 0xC0, 0x00, 
0x02, 0x37, 0xFF, 0x20, 0x00, 
0x02, 0x28, 0x00, 0xE2, 0x00, 
0x02, 0x28, 0x00, 0xC0, 0x00, 
0x02, 0x37, 0xFF, 0x20, 0x00, 
0x02, 0x28, 0x00, 0xE2, 0x00, 
0x02, 0x28, 0x00, 0xC0, 0x00, 
0x02, 0x2F, 0xFF, 0x20, 0x40, 
0xFF, 0xE8, 0x34, 0x22, 0x00, 
0x02, 0x48, 0x00, 0xE2, 0x25, 
0xFF, 0xE8, 0x37, 0x24, 0x48, 
0xFF, 0xE8, 0x34, 0x20, 0x00, 
0x02, 0x48, 0x00, 0xE2, 0x25, 
0x02, 0x4D, 0x08, 0x26, 0x00, 
0x02, 0x48, 0x00, 0xE2, 0x00, 
0x02, 0x48, 0x33, 0x20, 0x00, 
0x02, 0x48, 0x00, 0xE2, 0x00, 
0x02, 0x70, 0x3F, 0x20, 0x00, 
0x02, 0x68, 0x40, 0x22, 0x00, 
0x02, 0x58, 0x3F, 0x34, 0x00, 
0x02, 0x50, 0x40, 0x22, 0x00, 
0x02, 0x48, 0x3D, 0x22, 0x00, 
0x02, 0x40, 0x3E, 0x22, 0x00, 
0x02, 0x38, 0x3D, 0x22, 0x00, 
0x02, 0x60, 0x00, 0xE2, 0x00, 
0x02, 0x78, 0x00, 0xF2, 0x00, 
0x02, 0x90, 0x42, 0x20, 0x00, 
0x02, 0x80, 0x42, 0x34, 0x00, 
0x02, 0x60, 0x41, 0x22, 0x00, 
0x02, 0x58, 0x41, 0x22, 0x40, 
0x02, 0x98, 0x00, 0xF2, 0x00, 
0x02, 0x88, 0x00, 0xE2, 0x00, 
0x02, 0x88, 0x00, 0xC0, 0x00, 
0x02, 0x8F, 0xFF, 0x20, 0x00, 
0x03, 0x00, 0x00, 0xE2, 0x00, 
0x03, 0x08, 0x00, 0xF2, 0x00, 
0x02, 0xD5, 0x08, 0x20, 0x00, 
0x02, 0xD0, 0x31, 0x22, 0x40, 
0x03, 0x08, 0x31, 0x22, 0x00, 
0x02, 0xC5, 0x08, 0x34, 0x00, 
0x02, 0xC0, 0x31, 0x22, 0x40, 
0x03, 0x00, 0x31, 0x82, 0x00, 
0x03, 0x00, 0x31, 0x22, 0x00, 
0x02, 0xC8, 0x00, 0xE2, 0x00, 
0x02, 0xD8, 0x00, 0xF2, 0x00, 
0x03, 0x10, 0x00, 0xF6, 0x00, 
0x02, 0xE5, 0x08, 0x20, 0x00, 
0xFF, 0xE8, 0x32, 0x22, 0x40, 
0x02, 0xE8, 0x00, 0xE2, 0x00, 
0x03, 0x15, 0x08, 0x22, 0x48, 
0x03, 0x15, 0x08, 0x20, 0x00, 
0x02, 0xE8, 0x00, 0xE2, 0x27, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x02, 0xED, 0x1A, 0x20, 0x00, 
0x03, 0x18, 0x00, 0xE2, 0x00, 
0x03, 0x20, 0x00, 0xF2, 0x00, 
0x03, 0x18, 0x00, 0xC0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x11, 0xA1, 0x00, 
0xFF, 0xE5, 0x08, 0x20, 0x00, 
0x00, 0x00, 0x10, 0xA1, 0x00, 
0xFF, 0xE5, 0x08, 0x22, 0x40, 
0x02, 0xF0, 0x00, 0xE2, 0x00, 
0x03, 0x20, 0x00, 0xC0, 0x00, 
0x02, 0xF7, 0xFF, 0x20, 0x00, 
0xFF, 0xE5, 0x08, 0x22, 0x00, 
0x02, 0xF8, 0x00, 0xE2, 0x00, 
0xFF, 0xE8, 0x3B, 0x20, 0x00, 
0x03, 0x2D, 0x08, 0x22, 0x40, 
0x02, 0xA0, 0x00, 0xE2, 0x00, 
0x03, 0x2D, 0x08, 0x20, 0x00, 
0x02, 0xA0, 0x46, 0x22, 0x00, 
0x03, 0x30, 0x00, 0xE2, 0x00, 
0x03, 0x30, 0x00, 0xC0, 0x00, 
0x02, 0xFF, 0xFF, 0x20, 0x00, 
0x02, 0xF8, 0x00, 0xE2, 0x00, 
0x02, 0xF8, 0x00, 0xC0, 0x00, 
0x02, 0x8F, 0xFF, 0x20, 0x40, 
0x01, 0x45, 0x08, 0x42, 0x00, 
0x01, 0xAD, 0x08, 0x62, 0x00, 
0xFF, 0xE8, 0x38, 0x20, 0x00, 
0x03, 0x3D, 0x08, 0x22, 0x40, 
0x02, 0xA0, 0x00, 0xE2, 0x00, 
0x03, 0x3D, 0x08, 0x20, 0x00, 
0x02, 0xA0, 0x46, 0x22, 0x00, 
0x03, 0x40, 0x00, 0xE2, 0x00, 
0x03, 0x40, 0x00, 0xC0, 0x00, 
0x02, 0x28, 0x00, 0xE4, 0x00, 
0x01, 0x07, 0xFF, 0x20, 0x00, 
0x02, 0x2D, 0x08, 0x22, 0x00, 
0x02, 0x2F, 0xFF, 0x22, 0x40, 
0x03, 0x58, 0x00, 0xE2, 0x00, 
0x01, 0x6F, 0xFF, 0x20, 0x00, 
0x02, 0x28, 0x00, 0xE6, 0x00, 
0x02, 0x2D, 0x08, 0x22, 0x00, 
0x02, 0x2F, 0xFF, 0x22, 0x40, 
0x03, 0x70, 0x00, 0xE2, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x03, 0x98, 0x4A, 0x20, 0x00, 
0x03, 0x90, 0x4B, 0x22, 0x00, 
0x03, 0x80, 0x4A, 0x34, 0x00, 
0x03, 0x78, 0x4B, 0x22, 0x00, 
0x03, 0x58, 0x47, 0x22, 0x00, 
0x03, 0x50, 0x48, 0x22, 0x00, 
0x03, 0x48, 0x49, 0x22, 0x00, 
0x03, 0x88, 0x00, 0xE2, 0x00, 
0x03, 0xA0, 0x00, 0xF2, 0x00, 
0x03, 0xC8, 0x4A, 0x20, 0x00, 
0x03, 0xC0, 0x4B, 0x22, 0x00, 
0x03, 0xB0, 0x4A, 0x34, 0x00, 
0x03, 0xA8, 0x4B, 0x22, 0x00, 
0x03, 0x70, 0x47, 0x22, 0x00, 
0x03, 0x68, 0x48, 0x22, 0x00, 
0x03, 0x60, 0x49, 0x22, 0x00, 
0x03, 0xB8, 0x00, 0xE2, 0x00, 
0x03, 0xD0, 0x00, 0xF2, 0x00, 
0x03, 0xF8, 0x4F, 0x20, 0x00, 
0x03, 0xF0, 0x50, 0x22, 0x00, 
0x03, 0xE0, 0x4F, 0x34, 0x00, 
0x03, 0xD8, 0x50, 0x22, 0x00, 
0x03, 0x88, 0x4C, 0x22, 0x00, 
0x03, 0x80, 0x4D, 0x22, 0x00, 
0x03, 0x78, 0x4E, 0x22, 0x00, 
0x03, 0xE8, 0x00, 0xE2, 0x00, 
0x04, 0x00, 0x00, 0xF2, 0x00, 
0x04, 0x28, 0x4F, 0x20, 0x00, 
0x04, 0x20, 0x50, 0x22, 0x00, 
0x04, 0x10, 0x4F, 0x34, 0x00, 
0x04, 0x08, 0x50, 0x22, 0x00, 
0x03, 0xB8, 0x4C, 0x22, 0x00, 
0x03, 0xB0, 0x4D, 0x22, 0x00, 
0x03, 0xA8, 0x4E, 0x22, 0x00, 
0x04, 0x18, 0x00, 0xE2, 0x00, 
0x04, 0x30, 0x00, 0xF2, 0x00, 
0x04, 0x58, 0x54, 0x20, 0x00, 
0x04, 0x50, 0x55, 0x22, 0x00, 
0x04, 0x40, 0x54, 0x34, 0x00, 
0x04, 0x38, 0x55, 0x22, 0x00, 
0x03, 0xE8, 0x51, 0x22, 0x00, 
0x03, 0xE0, 0x52, 0x22, 0x00, 
0x03, 0xD8, 0x53, 0x22, 0x00, 
0x04, 0x48, 0x00, 0xE2, 0x00, 
0x04, 0x60, 0x00, 0xF2, 0x00, 
0x04, 0x88, 0x54, 0x20, 0x00, 
0x04, 0x80, 0x55, 0x22, 0x00, 
0x04, 0x70, 0x54, 0x34, 0x00, 
0x04, 0x68, 0x55, 0x22, 0x00, 
0x04, 0x18, 0x51, 0x22, 0x00, 
0x04, 0x10, 0x52, 0x22, 0x00, 
0x04, 0x08, 0x53, 0x22, 0x00, 
0x04, 0x78, 0x00, 0xE2, 0x00, 
0x04, 0x90, 0x00, 0xF2, 0x00, 
0x04, 0xB8, 0x59, 0x20, 0x00, 
0x04, 0xB0, 0x5A, 0x22, 0x00, 
0x04, 0xA0, 0x59, 0x34, 0x00, 
0x04, 0x98, 0x5A, 0x22, 0x00, 
0x04, 0x48, 0x56, 0x22, 0x00, 
0x04, 0x40, 0x57, 0x22, 0x00, 
0x04, 0x38, 0x58, 0x22, 0x00, 
0x04, 0xA8, 0x00, 0xE2, 0x00, 
0x04, 0xC0, 0x00, 0xF2, 0x00, 
0x04, 0xE8, 0x59, 0x20, 0x00, 
0x04, 0xE0, 0x5A, 0x22, 0x00, 
0x04, 0xD0, 0x59, 0x34, 0x00, 
0x04, 0xC8, 0x5A, 0x22, 0x00, 
0x04, 0x78, 0x56, 0x22, 0x00, 
0x04, 0x70, 0x57, 0x22, 0x00, 
0x04, 0x68, 0x58, 0x22, 0x00, 
0x04, 0xD8, 0x00, 0xE2, 0x00, 
0x04, 0xF0, 0x00, 0xF2, 0x00, 
0x05, 0x18, 0x5E, 0x20, 0x00, 
0x05, 0x10, 0x5F, 0x22, 0x00, 
0x05, 0x00, 0x5E, 0x34, 0x00, 
0x04, 0xF8, 0x5F, 0x22, 0x00, 
0x04, 0xA8, 0x5B, 0x22, 0x00, 
0x04, 0xA0, 0x5C, 0x22, 0x00, 
0x04, 0x98, 0x5D, 0x22, 0x00, 
0x05, 0x08, 0x00, 0xE2, 0x00, 
0x05, 0x20, 0x00, 0xF2, 0x00, 
0x05, 0x48, 0x5E, 0x20, 0x00, 
0x05, 0x40, 0x5F, 0x22, 0x00, 
0x05, 0x30, 0x5E, 0x34, 0x00, 
0x05, 0x28, 0x5F, 0x22, 0x00, 
0x04, 0xD8, 0x5B, 0x22, 0x00, 
0x04, 0xD0, 0x5C, 0x22, 0x00, 
0x04, 0xC8, 0x5D, 0x22, 0x00, 
0x05, 0x38, 0x00, 0xE2, 0x00, 
0x05, 0x50, 0x00, 0xF2, 0x00, 
0x05, 0x78, 0x63, 0x20, 0x00, 
0x05, 0x70, 0x64, 0x22, 0x00, 
0x05, 0x60, 0x63, 0x34, 0x00, 
0x05, 0x58, 0x64, 0x22, 0x00, 
0x05, 0x08, 0x60, 0x22, 0x00, 
0x05, 0x00, 0x61, 0x22, 0x00, 
0x04, 0xF8, 0x62, 0x22, 0x00, 
0x05, 0x68, 0x00, 0xE2, 0x00, 
0x05, 0x80, 0x00, 0xF2, 0x00, 
0x05, 0xA8, 0x63, 0x20, 0x00, 
0x05, 0xA0, 0x64, 0x22, 0x00, 
0x05, 0x90, 0x63, 0x34, 0x00, 
0x05, 0x88, 0x64, 0x22, 0x00, 
0x05, 0x38, 0x60, 0x22, 0x00, 
0x05, 0x30, 0x61, 0x22, 0x00, 
0x05, 0x28, 0x62, 0x22, 0x00, 
0x05, 0x98, 0x00, 0xE2, 0x00, 
0x05, 0xB0, 0x00, 0xF2, 0x00, 
0x05, 0x68, 0x65, 0x20, 0x00, 
0x01, 0x00, 0x66, 0x22, 0x00, 
0x05, 0xB8, 0x00, 0xE2, 0x00, 
0x05, 0x98, 0x65, 0x20, 0x00, 
0x01, 0x68, 0x66, 0x22, 0x00, 
0x05, 0xC0, 0x00, 0xE2, 0x00, 
0x05, 0xBD, 0x09, 0x20, 0x00, 
0x05, 0xC5, 0x09, 0x22, 0x00, 
0x06, 0x18, 0x00, 0xE2, 0x00, 
0x06, 0x18, 0x00, 0xC0, 0x00, 
0x06, 0x1F, 0xFF, 0x20, 0x00, 
0x06, 0x38, 0x00, 0xE2, 0x00, 
0x06, 0x40, 0x00, 0xF2, 0x00, 
0x05, 0xED, 0x08, 0x20, 0x00, 
0x05, 0xE8, 0x89, 0x22, 0x40, 
0x06, 0x40, 0x89, 0x22, 0x00, 
0x05, 0xDD, 0x08, 0x34, 0x00, 
0x05, 0xD8, 0x89, 0x22, 0x40, 
0x06, 0x38, 0x89, 0x82, 0x00, 
0x06, 0x38, 0x89, 0x22, 0x00, 
0x05, 0xE0, 0x00, 0xE2, 0x00, 
0x05, 0xF0, 0x00, 0xF2, 0x00, 
0x06, 0x48, 0x00, 0xF6, 0x00, 
0x06, 0x0D, 0x08, 0x20, 0x08, 
0x06, 0x10, 0x00, 0xE2, 0x00, 
0x05, 0xFD, 0x08, 0x20, 0x00, 
0xFF, 0xE8, 0x8C, 0x22, 0x67, 
0x06, 0x00, 0x00, 0xE2, 0x00, 
0x06, 0x4D, 0x08, 0x22, 0x48, 
0x06, 0x4D, 0x08, 0x20, 0x00, 
0x06, 0x00, 0x00, 0xE2, 0x27, 
0xFF, 0xE8, 0x8B, 0x20, 0x00, 
0x06, 0x10, 0x00, 0xE2, 0x27, 
0x06, 0x15, 0x08, 0x20, 0x08, 
0xFF, 0xFD, 0x08, 0x22, 0x40, 
0x06, 0x10, 0x00, 0xE2, 0x26, 
0x06, 0x05, 0x1A, 0x20, 0x00, 
0x06, 0x50, 0x00, 0xE2, 0x00, 
0x06, 0x58, 0x00, 0xF2, 0x00, 
0x06, 0x50, 0x00, 0xC0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x68, 0xA1, 0x00, 
0xFF, 0xE5, 0x08, 0x20, 0x00, 
0x00, 0x00, 0x67, 0xA1, 0x00, 
0xFF, 0xE5, 0x08, 0x22, 0x40, 
0x06, 0x20, 0x00, 0xE2, 0x00, 
0x06, 0x58, 0x00, 0xC0, 0x00, 
0x06, 0x27, 0xFF, 0x20, 0x00, 
0xFF, 0xE5, 0x08, 0x22, 0x00, 
0x06, 0x30, 0x00, 0xE2, 0x00, 
0x06, 0x30, 0x00, 0xC0, 0x00, 
0x05, 0xBF, 0xFF, 0x20, 0x00, 
0x06, 0x28, 0x00, 0xE2, 0x00, 
0x06, 0x28, 0x8A, 0x20, 0x00, 
0x06, 0x28, 0x00, 0xE2, 0x00, 
0x06, 0x28, 0x8A, 0x20, 0x00, 
0x05, 0xC8, 0x00, 0xE2, 0x00, 
0x05, 0xC7, 0xFF, 0x20, 0x00, 
0x06, 0x28, 0x00, 0xE2, 0x00, 
0x06, 0x28, 0x8A, 0x20, 0x00, 
0x06, 0x28, 0x00, 0xE2, 0x00, 
0x06, 0x28, 0x8A, 0x20, 0x00, 
0x05, 0xD0, 0x00, 0xE2, 0x00, 
0x05, 0xC8, 0x8D, 0x20, 0x00, 
0x05, 0xB8, 0x8E, 0x22, 0x00, 
0x06, 0x60, 0x00, 0xE2, 0x00, 
0x05, 0xD0, 0x8D, 0x20, 0x00, 
0x05, 0xC0, 0x8E, 0x22, 0x00, 
0x06, 0x68, 0x00, 0xE2, 0x00, 
0xFF, 0xE8, 0xB4, 0x20, 0x00, 
0x06, 0xC0, 0x00, 0xE2, 0x00, 
0x06, 0xC5, 0x09, 0x20, 0x00, 
0x06, 0xC0, 0x00, 0xE2, 0x00, 
0x06, 0xC0, 0x00, 0xC0, 0x00, 
0x06, 0x67, 0xFF, 0x20, 0x00, 
0x06, 0x6F, 0xFF, 0x22, 0x00, 
0x06, 0xC8, 0x00, 0xE2, 0x00, 
0x06, 0xC8, 0x00, 0xC0, 0x00, 
0x06, 0xCF, 0xFF, 0x20, 0x00, 
0x06, 0xE8, 0x00, 0xE2, 0x00, 
0x06, 0xF0, 0x00, 0xF2, 0x00, 
0x06, 0x95, 0x08, 0x20, 0x00, 
0x06, 0x90, 0xB1, 0x22, 0x40, 
0x06, 0xF0, 0xB1, 0x22, 0x00, 
0xFF, 0xD8, 0xB7, 0x02, 0x00, 
0x06, 0x85, 0x08, 0x34, 0x00, 
0x06, 0x80, 0xB1, 0x22, 0x40, 
0x06, 0xE8, 0xB1, 0x82, 0x00, 
0xFF, 0xD8, 0xB6, 0x02, 0x00, 
0x06, 0xE8, 0xB1, 0x22, 0x00, 
0x06, 0x88, 0x00, 0xE2, 0x00, 
0x06, 0x98, 0x00, 0xF2, 0x00, 
0x06, 0xF8, 0x00, 0xF6, 0x00, 
0x06, 0xB5, 0x08, 0x20, 0x08, 
0x06, 0xB8, 0x00, 0xE2, 0x00, 
0x06, 0xA5, 0x08, 0x20, 0x00, 
0xFF, 0xE8, 0xB3, 0x22, 0x67, 
0x06, 0xA8, 0x00, 0xE2, 0x00, 
0x06, 0xFD, 0x08, 0x22, 0x48, 
0x06, 0xFD, 0x08, 0x20, 0x00, 
0x06, 0xA8, 0x00, 0xE2, 0x27, 
0xFF, 0xE8, 0xB2, 0x20, 0x00, 
0x06, 0xB8, 0x00, 0xE2, 0x27, 
0x06, 0xBD, 0x08, 0x20, 0x08, 
0xFF, 0xFD, 0x08, 0x22, 0x40, 
0x06, 0xB8, 0x00, 0xE2, 0x26, 
0x06, 0xAD, 0x1A, 0x20, 0x00, 
0x07, 0x00, 0x00, 0xE2, 0x00, 
0x07, 0x08, 0x00, 0xF2, 0x00, 
0x07, 0x00, 0x00, 0xC0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x90, 0xA1, 0x00, 
0xFF, 0xE5, 0x08, 0x20, 0x00, 
0x00, 0x00, 0x8F, 0xA1, 0x00, 
0xFF, 0xE5, 0x08, 0x22, 0x40, 
0x06, 0xD0, 0x00, 0xE2, 0x00, 
0x07, 0x08, 0x00, 0xC0, 0x00, 
0x06, 0xD7, 0xFF, 0x20, 0x00, 
0xFF, 0xE5, 0x08, 0x22, 0x00, 
0x06, 0xE0, 0x00, 0xE2, 0x00, 
0x06, 0xE0, 0x00, 0xC0, 0x00, 
0xFF, 0xD8, 0xB9, 0x02, 0x00, 
0x06, 0xC5, 0x07, 0x20, 0x00, 
0x06, 0xC0, 0x00, 0xE2, 0x00, 
0x06, 0xC7, 0xFF, 0x20, 0x00, 
0x06, 0xE0, 0x00, 0xE2, 0x00, 
0x06, 0xE0, 0x00, 0xC0, 0x00, 
0xFF, 0xD8, 0xB8, 0x02, 0x00, 
0x06, 0x67, 0xFF, 0x20, 0x00, 
0x06, 0x70, 0x00, 0xE2, 0x00, 
0x06, 0x6F, 0xFF, 0x20, 0x00, 
0x06, 0x78, 0x00, 0xE2, 0x00, 
0x06, 0x70, 0xBC, 0x20, 0x00, 
0x07, 0x10, 0x00, 0xE2, 0x00, 
0x06, 0x78, 0xBD, 0x20, 0x00, 
0x07, 0x18, 0x00, 0xE2, 0x00, 
0x07, 0x15, 0x08, 0x20, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x07, 0x48, 0x00, 0xF0, 0x00, 
0x07, 0x3D, 0x08, 0x20, 0x08, 
0x07, 0x40, 0x00, 0xE2, 0x00, 
0x07, 0x2D, 0x08, 0x20, 0x00, 
0xFF, 0xE8, 0xBF, 0x22, 0x67, 
0x07, 0x30, 0x00, 0xE2, 0x00, 
0x07, 0x4D, 0x08, 0x22, 0x48, 
0x07, 0x4D, 0x08, 0x20, 0x00, 
0x07, 0x30, 0x00, 0xE2, 0x27, 
0xFF, 0xE8, 0xBE, 0x20, 0x00, 
0x07, 0x40, 0x00, 0xE2, 0x27, 
0x07, 0x45, 0x08, 0x20, 0x08, 
0xFF, 0xFD, 0x08, 0x22, 0x40, 
0x07, 0x40, 0x00, 0xE2, 0x26, 
0x07, 0x35, 0x08, 0x20, 0x00, 
0x07, 0x20, 0x00, 0xE2, 0x00, 
0x07, 0x10, 0xC0, 0x20, 0x00, 
0x07, 0x50, 0x00, 0xE2, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x07, 0x18, 0xC1, 0x20, 0x00, 
0x07, 0x58, 0x00, 0xE2, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x07, 0x1D, 0x08, 0x20, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0x07, 0x88, 0x00, 0xF0, 0x00, 
0x07, 0x7D, 0x08, 0x20, 0x08, 
0x07, 0x80, 0x00, 0xE2, 0x00, 
0x07, 0x6D, 0x08, 0x20, 0x00, 
0xFF, 0xE8, 0xC3, 0x22, 0x67, 
0x07, 0x70, 0x00, 0xE2, 0x00, 
0x07, 0x8D, 0x08, 0x22, 0x48, 
0x07, 0x8D, 0x08, 0x20, 0x00, 
0x07, 0x70, 0x00, 0xE2, 0x27, 
0xFF, 0xE8, 0xC2, 0x20, 0x00, 
0x07, 0x80, 0x00, 0xE2, 0x27, 
0x07, 0x85, 0x08, 0x20, 0x08, 
0xFF, 0xFD, 0x08, 0x22, 0x40, 
0x07, 0x80, 0x00, 0xE2, 0x26, 
0x07, 0x75, 0x08, 0x20, 0x00, 
0x07, 0x60, 0x00, 0xE2, 0x00, 
0x07, 0x25, 0x08, 0x20, 0x00, 
0xFF, 0xD8, 0xC4, 0x02, 0x00, 
0x07, 0x90, 0x00, 0xE2, 0x00, 
0x07, 0x65, 0x08, 0x20, 0x00, 
0xFF, 0xD8, 0xC5, 0x02, 0x00, 
0x07, 0x98, 0x00, 0xE2, 0x00, 
0x07, 0x55, 0x08, 0x20, 0x00, 
0xFD, 0xB0, 0x00, 0xE2, 0x00, 
0x07, 0x5D, 0x08, 0x20, 0x00, 
0xFD, 0xB8, 0x00, 0xE2, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0xFE, 0x30, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
0xFE, 0xC0, 0x0F, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 
};

/* DSP Parameter (Coefficient) Data */
#define PARAM_SIZE_IC_2 792
#define PARAM_ADDR_IC_2 0
ADI_REG_TYPE Param_Data_IC_2[PARAM_SIZE_IC_2] = {
0x00, 0x00, 0x10, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x7F, 0xFC, 0xB9, 
0x00, 0x7F, 0xFC, 0xB9, 
0x00, 0x7F, 0xFC, 0xB9, 
0x00, 0x7F, 0xFC, 0xB9, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x17, 0x62, 0x31, 
0x00, 0x10, 0x30, 0x4F, 
0x00, 0x0B, 0x5F, 0x9E, 
0x00, 0x08, 0x0D, 0x44, 
0x00, 0x05, 0xB3, 0x44, 
0x00, 0x04, 0x09, 0x15, 
0x00, 0x04, 0x59, 0x5D, 
0x00, 0x19, 0x59, 0x8E, 
0x00, 0x59, 0x2D, 0xAC, 
0x00, 0xAF, 0x08, 0x62, 
0x01, 0x1C, 0x6B, 0x3D, 
0x01, 0x7E, 0x1C, 0x0D, 
0x01, 0xC3, 0x08, 0xCA, 
0x01, 0xF2, 0x76, 0x28, 
0x02, 0x09, 0xDF, 0x42, 
0x02, 0x0B, 0xBD, 0xC6, 
0x01, 0xFD, 0xCC, 0xCD, 
0x01, 0xE6, 0xFE, 0x4F, 
0x01, 0xCB, 0x6B, 0x7D, 
0x01, 0xA1, 0xE2, 0x3D, 
0x01, 0x76, 0xD3, 0x01, 
0x01, 0x55, 0xB0, 0xC6, 
0x01, 0x31, 0xE6, 0x13, 
0x00, 0xFD, 0x99, 0x50, 
0x00, 0xC9, 0x35, 0x3A, 
0x00, 0xA7, 0xA8, 0x21, 
0x00, 0x8B, 0xEC, 0x5E, 
0x00, 0x6B, 0x3A, 0xC6, 
0x00, 0x51, 0x15, 0x27, 
0x00, 0x3F, 0xE2, 0xCD, 
0x00, 0x30, 0x3C, 0xA7, 
0x00, 0x22, 0x26, 0x2D, 
0x00, 0x18, 0x2C, 0xFC, 
0x00, 0x00, 0x31, 0x81, 
0x00, 0x00, 0x00, 0x45, 
0x00, 0x40, 0x00, 0x00, 
0x06, 0x00, 0x00, 0x00, 
0x00, 0x40, 0x00, 0x00, 
0x00, 0xAC, 0x8B, 0x77, 
0x01, 0x59, 0x16, 0xEE, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x59, 0x99, 0x9A, 
0x00, 0xA6, 0x66, 0x66, 
0x00, 0x99, 0x99, 0x9A, 
0x00, 0x59, 0x99, 0x9A, 
0x00, 0x7F, 0x2D, 0xEB, 
0xFF, 0x01, 0xA4, 0x2B, 
0x00, 0xFE, 0x59, 0x28, 
0xFF, 0x81, 0xA1, 0x7E, 
0x00, 0x7F, 0x2F, 0x3F, 
0x00, 0x7E, 0x5E, 0x7E, 
0x00, 0x00, 0x01, 0x57, 
0x00, 0x00, 0x02, 0xAD, 
0x00, 0x00, 0xD0, 0xC1, 
0x00, 0x01, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x56, 0x1B, 
0x00, 0x80, 0xD2, 0x5F, 
0x00, 0x81, 0x9B, 0xE4, 
0x00, 0x82, 0xBF, 0xB2, 
0x00, 0x84, 0x47, 0xCC, 
0x00, 0x86, 0x3B, 0x39, 
0x00, 0x88, 0x9D, 0x10, 
0x00, 0x8B, 0x6C, 0x66, 
0x00, 0x8E, 0xA3, 0x3C, 
0x00, 0x92, 0x35, 0x6D, 
0x00, 0x96, 0x0F, 0x7D, 
0x00, 0x9A, 0x16, 0x43, 
0x00, 0x9E, 0x39, 0x7C, 
0x00, 0xA2, 0x79, 0x26, 
0x00, 0xA6, 0xCA, 0xF1, 
0x00, 0xA5, 0xE3, 0x1C, 
0x00, 0x97, 0x46, 0x15, 
0x00, 0x7D, 0xC9, 0xDF, 
0x00, 0x61, 0xB2, 0x82, 
0x00, 0x48, 0xA0, 0xB1, 
0x00, 0x34, 0xE9, 0x4F, 
0x00, 0x26, 0x75, 0xC2, 
0x00, 0x00, 0x14, 0x8A, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x14, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x7F, 0xDD, 0x36, 
0x00, 0x5A, 0xEE, 0x3B, 
0x00, 0x40, 0x98, 0xBE, 
0x00, 0x00, 0x14, 0xA5, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x14, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 
0x00, 0x00, 0x08, 0x9D, 
0x00, 0x00, 0x00, 0xC6, 
0x00, 0x28, 0x7A, 0x27, 
0x00, 0x28, 0x7A, 0x27, 
0x00, 0x00, 0x08, 0x9D, 
0x00, 0x00, 0x00, 0xC6, 
0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 
};


/* Register Default - IC 2.Sample Rate Setting */
ADI_REG_TYPE R0_SAMPLE_RATE_SETTING_IC_2_Default[REG_SAMPLE_RATE_SETTING_IC_2_BYTE] = {
0x7F
};

/* Register Default - IC 2.DSP Run Register */
ADI_REG_TYPE R1_DSP_RUN_REGISTER_IC_2_Default[REG_DSP_RUN_REGISTER_IC_2_BYTE] = {
0x00
};

/* Register Default - IC 2.Clock Control Register */
ADI_REG_TYPE R2_CLKCTRLREGISTER_IC_2_Default[REG_CLKCTRLREGISTER_IC_2_BYTE] = {
0x0F
};

/* Register Default - IC 2.PLL Control Register */
ADI_REG_TYPE R3_PLLCRLREGISTER_IC_2_Default[REG_PLLCRLREGISTER_IC_2_BYTE] = {
0x00, 0xFD, 0x00, 0x0C, 0x20, 0x03
};

/* Register Default - IC 2.Delay */
#define R4_DELAY_IC_2_ADDR 0x0
#define R4_DELAY_IC_2_SIZE 2
ADI_REG_TYPE R4_DELAY_IC_2_Default[R4_DELAY_IC_2_SIZE] = {
0x00, 0x64
};

/* Register Default - IC 2.Serial Port Control Registers */
#define R5_SERIAL_PORT_CONTROL_REGISTERS_IC_2_SIZE 2
ADI_REG_TYPE R5_SERIAL_PORT_CONTROL_REGISTERS_IC_2_Default[R5_SERIAL_PORT_CONTROL_REGISTERS_IC_2_SIZE] = {
0x00, 0x00
};

/* Register Default - IC 2.ALC Control Registers */
#define R6_ALC_CONTROL_REGISTERS_IC_2_SIZE 4
ADI_REG_TYPE R6_ALC_CONTROL_REGISTERS_IC_2_Default[R6_ALC_CONTROL_REGISTERS_IC_2_SIZE] = {
0xF8, 0x3B, 0x68, 0x31
};

/* Register Default - IC 2.Microphone Control Register */
ADI_REG_TYPE R7_MICCTRLREGISTER_IC_2_Default[REG_MICCTRLREGISTER_IC_2_BYTE] = {
0x00
};

/* Register Default - IC 2.Record Input Signal Path Registers */
#define R8_RECORD_INPUT_SIGNAL_PATH_REGISTERS_IC_2_SIZE 8
ADI_REG_TYPE R8_RECORD_INPUT_SIGNAL_PATH_REGISTERS_IC_2_Default[R8_RECORD_INPUT_SIGNAL_PATH_REGISTERS_IC_2_SIZE] = {
0x00, 0x01, 0x00, 0x01, 0x00, 0xFC, 0xFC, 0x00
};

/* Register Default - IC 2.ADC Control Registers */
#define R9_ADC_CONTROL_REGISTERS_IC_2_SIZE 3
ADI_REG_TYPE R9_ADC_CONTROL_REGISTERS_IC_2_Default[R9_ADC_CONTROL_REGISTERS_IC_2_SIZE] = {
0x13, 0x00, 0x00
};

/* Register Default - IC 2.Playback Output Signal Path Registers */
#define R10_PLAYBACK_OUTPUT_SIGNAL_PATH_REGISTERS_IC_2_SIZE 14
ADI_REG_TYPE R10_PLAYBACK_OUTPUT_SIGNAL_PATH_REGISTERS_IC_2_Default[R10_PLAYBACK_OUTPUT_SIGNAL_PATH_REGISTERS_IC_2_SIZE] = {
0x21, 0x00, 0x41, 0x00, 0x05, 0x11, 0x00, 0xFF, 0xFE, 0xFE, 0xFE, 0xFD, 0x04, 0x03
};

/* Register Default - IC 2.Converter Control Registers */
#define R11_CONVERTER_CONTROL_REGISTERS_IC_2_SIZE 2
ADI_REG_TYPE R11_CONVERTER_CONTROL_REGISTERS_IC_2_Default[R11_CONVERTER_CONTROL_REGISTERS_IC_2_SIZE] = {
0x00, 0x00
};

/* Register Default - IC 2.DAC Control Registers */
#define R12_DAC_CONTROL_REGISTERS_IC_2_SIZE 3
ADI_REG_TYPE R12_DAC_CONTROL_REGISTERS_IC_2_Default[R12_DAC_CONTROL_REGISTERS_IC_2_SIZE] = {
0x07, 0x00, 0x00
};

/* Register Default - IC 2.Serial Port Pad Control Registers */
#define R13_SERIAL_PORT_PAD_CONTROL_REGISTERS_IC_2_SIZE 1
ADI_REG_TYPE R13_SERIAL_PORT_PAD_CONTROL_REGISTERS_IC_2_Default[R13_SERIAL_PORT_PAD_CONTROL_REGISTERS_IC_2_SIZE] = {
0xAA
};

/* Register Default - IC 2.Communication Port Pad Control Registers */
#define R14_COMMUNICATION_PORT_PAD_CONTROL_REGISTERS_IC_2_SIZE 2
ADI_REG_TYPE R14_COMMUNICATION_PORT_PAD_CONTROL_REGISTERS_IC_2_Default[R14_COMMUNICATION_PORT_PAD_CONTROL_REGISTERS_IC_2_SIZE] = {
0xAA, 0x00
};

/* Register Default - IC 2.Jack Detect Pad Control Register */
ADI_REG_TYPE R15_JACKREGISTER_IC_2_Default[REG_JACKREGISTER_IC_2_BYTE] = {
0x08
};

/* Register Default - IC 2.DSP ON Register */
ADI_REG_TYPE R21_DSP_ENABLE_REGISTER_IC_2_Default[REG_DSP_ENABLE_REGISTER_IC_2_BYTE] = {
0x01
};

/* Register Default - IC 2.CRC Registers */
#define R22_CRC_REGISTERS_IC_2_SIZE 5
ADI_REG_TYPE R22_CRC_REGISTERS_IC_2_Default[R22_CRC_REGISTERS_IC_2_SIZE] = {
0x04, 0x5B, 0x06, 0x7F, 0x01
};

/* Register Default - IC 2.GPIO Registers */
#define R23_GPIO_REGISTERS_IC_2_SIZE 4
ADI_REG_TYPE R23_GPIO_REGISTERS_IC_2_Default[R23_GPIO_REGISTERS_IC_2_SIZE] = {
0x00, 0x00, 0x00, 0x00
};

/* Register Default - IC 2.Non Modulo Registers */
#define R24_NON_MODULO_REGISTERS_IC_2_SIZE 2
ADI_REG_TYPE R24_NON_MODULO_REGISTERS_IC_2_Default[R24_NON_MODULO_REGISTERS_IC_2_SIZE] = {
0x10, 0x00
};

/* Register Default - IC 2.Watchdog Registers */
#define R25_WATCHDOG_REGISTERS_IC_2_SIZE 5
ADI_REG_TYPE R25_WATCHDOG_REGISTERS_IC_2_Default[R25_WATCHDOG_REGISTERS_IC_2_SIZE] = {
0x00, 0x04, 0x00, 0x00, 0x00
};

/* Register Default - IC 2.Sampling Rate Setting Register */
ADI_REG_TYPE R26_SAMPLE_RATE_SETTING_IC_2_Default[REG_SAMPLE_RATE_SETTING_IC_2_BYTE] = {
0x7F
};

/* Register Default - IC 2.Routing Matrix Inputs Register */
ADI_REG_TYPE R27_ROUTING_MATRIX_INPUTS_IC_2_Default[REG_ROUTING_MATRIX_INPUTS_IC_2_BYTE] = {
0x00
};

/* Register Default - IC 2.Routing Matrix Outputs Register */
ADI_REG_TYPE R28_ROUTING_MATRIX_OUTPUTS_IC_2_Default[REG_ROUTING_MATRIX_OUTPUTS_IC_2_BYTE] = {
0x00
};

/* Register Default - IC 2.Serial Data Configuration Register */
ADI_REG_TYPE R29_SERIAL_DATAGPIO_PIN_CONFIG_IC_2_Default[REG_SERIAL_DATAGPIO_PIN_CONFIG_IC_2_BYTE] = {
0x00
};

/* Register Default - IC 2.DSP Slew Mode Register */
ADI_REG_TYPE R30_DSP_SLEW_MODES_IC_2_Default[REG_DSP_SLEW_MODES_IC_2_BYTE] = {
0x00
};

/* Register Default - IC 2.Serial Port Sample Rate Register */
ADI_REG_TYPE R31_SERIAL_PORT_SAMPLE_RATE_SETTING_IC_2_Default[REG_SERIAL_PORT_SAMPLE_RATE_SETTING_IC_2_BYTE] = {
0x00
};

/* Register Default - IC 2.Clock Enable Registers */
#define R32_CLOCK_ENABLE_REGISTERS_IC_2_SIZE 2
ADI_REG_TYPE R32_CLOCK_ENABLE_REGISTERS_IC_2_Default[R32_CLOCK_ENABLE_REGISTERS_IC_2_SIZE] = {
0x7F, 0x03
};

/* Register Default - IC 2.Sample Rate Setting */
ADI_REG_TYPE R35_SAMPLE_RATE_SETTING_IC_2_Default[REG_SAMPLE_RATE_SETTING_IC_2_BYTE] = {
0x01
};

/* Register Default - IC 2.DSP Run Register */
ADI_REG_TYPE R36_DSP_RUN_REGISTER_IC_2_Default[REG_DSP_RUN_REGISTER_IC_2_BYTE] = {
0x01
};

/* Register Default - IC 2.Dejitter Register Control */
ADI_REG_TYPE R37_DEJITTER_REGISTER_CONTROL_IC_2_Default[REG_DEJITTER_REGISTER_CONTROL_IC_2_BYTE] = {
0x00
};

/* Register Default - IC 2.Dejitter Register Control */
ADI_REG_TYPE R38_DEJITTER_REGISTER_CONTROL_IC_2_Default[REG_DEJITTER_REGISTER_CONTROL_IC_2_BYTE] = {
0x03
};


/*
 * Default Download
 */
#define DEFAULT_DOWNLOAD_SIZE_IC_2 39

void default_download_IC_2() {
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_SAMPLE_RATE_SETTING_IC_2_ADDR, REG_SAMPLE_RATE_SETTING_IC_2_BYTE, R0_SAMPLE_RATE_SETTING_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_DSP_RUN_REGISTER_IC_2_ADDR, REG_DSP_RUN_REGISTER_IC_2_BYTE, R1_DSP_RUN_REGISTER_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_CLKCTRLREGISTER_IC_2_ADDR, REG_CLKCTRLREGISTER_IC_2_BYTE, R2_CLKCTRLREGISTER_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_PLLCRLREGISTER_IC_2_ADDR, REG_PLLCRLREGISTER_IC_2_BYTE, R3_PLLCRLREGISTER_IC_2_Default );
	SIGMA_WRITE_DELAY( DEVICE_ADDR_IC_2, R4_DELAY_IC_2_SIZE, R4_DELAY_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_SERIAL_PORT_CONTROL_0_IC_2_ADDR , R5_SERIAL_PORT_CONTROL_REGISTERS_IC_2_SIZE, R5_SERIAL_PORT_CONTROL_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_ALC_CONTROL_0_IC_2_ADDR , R6_ALC_CONTROL_REGISTERS_IC_2_SIZE, R6_ALC_CONTROL_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_MICCTRLREGISTER_IC_2_ADDR, REG_MICCTRLREGISTER_IC_2_BYTE, R7_MICCTRLREGISTER_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_RECORD_PWR_MANAGEMENT_IC_2_ADDR , R8_RECORD_INPUT_SIGNAL_PATH_REGISTERS_IC_2_SIZE, R8_RECORD_INPUT_SIGNAL_PATH_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_ADC_CONTROL_0_IC_2_ADDR , R9_ADC_CONTROL_REGISTERS_IC_2_SIZE, R9_ADC_CONTROL_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_PLAYBACK_MIXER_LEFT_CONTROL_0_IC_2_ADDR , R10_PLAYBACK_OUTPUT_SIGNAL_PATH_REGISTERS_IC_2_SIZE, R10_PLAYBACK_OUTPUT_SIGNAL_PATH_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_CONVERTER_CTRL_0_IC_2_ADDR , R11_CONVERTER_CONTROL_REGISTERS_IC_2_SIZE, R11_CONVERTER_CONTROL_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_DAC_CONTROL_0_IC_2_ADDR , R12_DAC_CONTROL_REGISTERS_IC_2_SIZE, R12_DAC_CONTROL_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_SERIAL_PORT_PAD_CONTROL_0_IC_2_ADDR , R13_SERIAL_PORT_PAD_CONTROL_REGISTERS_IC_2_SIZE, R13_SERIAL_PORT_PAD_CONTROL_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_COMM_PORT_PAD_CTRL_0_IC_2_ADDR , R14_COMMUNICATION_PORT_PAD_CONTROL_REGISTERS_IC_2_SIZE, R14_COMMUNICATION_PORT_PAD_CONTROL_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_JACKREGISTER_IC_2_ADDR, REG_JACKREGISTER_IC_2_BYTE, R15_JACKREGISTER_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, PROGRAM_ADDR_IC_2, PROGRAM_SIZE_IC_2, Program_Data_IC_2 );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, PROGRAM_ADDR_IC_2, PROGRAM_SIZE_IC_2, Program_Data_IC_2 );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, PROGRAM_ADDR_IC_2, PROGRAM_SIZE_IC_2, Program_Data_IC_2 );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, PROGRAM_ADDR_IC_2, PROGRAM_SIZE_IC_2, Program_Data_IC_2 );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, PROGRAM_ADDR_IC_2, PROGRAM_SIZE_IC_2, Program_Data_IC_2 );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_DSP_ENABLE_REGISTER_IC_2_ADDR, REG_DSP_ENABLE_REGISTER_IC_2_BYTE, R21_DSP_ENABLE_REGISTER_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_CRC_IDEAL_1_IC_2_ADDR , R22_CRC_REGISTERS_IC_2_SIZE, R22_CRC_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_GPIO_0_CONTROL_IC_2_ADDR , R23_GPIO_REGISTERS_IC_2_SIZE, R23_GPIO_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_NON_MODULO_RAM_1_IC_2_ADDR , R24_NON_MODULO_REGISTERS_IC_2_SIZE, R24_NON_MODULO_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_WATCHDOG_ENABLE_IC_2_ADDR , R25_WATCHDOG_REGISTERS_IC_2_SIZE, R25_WATCHDOG_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_SAMPLE_RATE_SETTING_IC_2_ADDR, REG_SAMPLE_RATE_SETTING_IC_2_BYTE, R26_SAMPLE_RATE_SETTING_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_ROUTING_MATRIX_INPUTS_IC_2_ADDR, REG_ROUTING_MATRIX_INPUTS_IC_2_BYTE, R27_ROUTING_MATRIX_INPUTS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_ROUTING_MATRIX_OUTPUTS_IC_2_ADDR, REG_ROUTING_MATRIX_OUTPUTS_IC_2_BYTE, R28_ROUTING_MATRIX_OUTPUTS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_SERIAL_DATAGPIO_PIN_CONFIG_IC_2_ADDR, REG_SERIAL_DATAGPIO_PIN_CONFIG_IC_2_BYTE, R29_SERIAL_DATAGPIO_PIN_CONFIG_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_DSP_SLEW_MODES_IC_2_ADDR, REG_DSP_SLEW_MODES_IC_2_BYTE, R30_DSP_SLEW_MODES_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_SERIAL_PORT_SAMPLE_RATE_SETTING_IC_2_ADDR, REG_SERIAL_PORT_SAMPLE_RATE_SETTING_IC_2_BYTE, R31_SERIAL_PORT_SAMPLE_RATE_SETTING_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_CLOCK_ENABLE_REG_0_IC_2_ADDR , R32_CLOCK_ENABLE_REGISTERS_IC_2_SIZE, R32_CLOCK_ENABLE_REGISTERS_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, PROGRAM_ADDR_IC_2, PROGRAM_SIZE_IC_2, Program_Data_IC_2 );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, PARAM_ADDR_IC_2, PARAM_SIZE_IC_2, Param_Data_IC_2 );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_SAMPLE_RATE_SETTING_IC_2_ADDR, REG_SAMPLE_RATE_SETTING_IC_2_BYTE, R35_SAMPLE_RATE_SETTING_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_DSP_RUN_REGISTER_IC_2_ADDR, REG_DSP_RUN_REGISTER_IC_2_BYTE, R36_DSP_RUN_REGISTER_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_DEJITTER_REGISTER_CONTROL_IC_2_ADDR, REG_DEJITTER_REGISTER_CONTROL_IC_2_BYTE, R37_DEJITTER_REGISTER_CONTROL_IC_2_Default );
	SIGMA_WRITE_REGISTER_BLOCK( DEVICE_ADDR_IC_2, REG_DEJITTER_REGISTER_CONTROL_IC_2_ADDR, REG_DEJITTER_REGISTER_CONTROL_IC_2_BYTE, R38_DEJITTER_REGISTER_CONTROL_IC_2_Default );
}

#endif
