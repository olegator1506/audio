/*
 * File:           E:\projects\test1_IC_1_PARAM.h
 *
 * Created:        Friday, October 02, 2020 9:45:34 PM
 * Description:    test1:IC 1 parameter RAM definitions.
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
#ifndef __TEST1_IC_1_PARAM_H__
#define __TEST1_IC_1_PARAM_H__


/* Module Modulo Size - Modulo Size*/
#define MOD_MODULOSIZE_COUNT                           1
#define MOD_MODULOSIZE_DEVICE                          "IC1"
#define MOD_MODULOSIZE_MODULO_SIZE_ADDR                0
#define MOD_MODULOSIZE_MODULO_SIZE_FIXPT               0x00001000
#define MOD_MODULOSIZE_MODULO_SIZE_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(4096)
#define MOD_MODULOSIZE_MODULO_SIZE_TYPE                SIGMASTUDIOTYPE_INTEGER

/* Module Nx2-1 - Stereo Switch Nx2*/
#define MOD_NX2_1_COUNT                                2
#define MOD_NX2_1_DEVICE                               "IC1"
#define MOD_NX2_1_ALG0_STAGE0_STEREOSWITCHNOSLEW_ADDR  8
#define MOD_NX2_1_ALG0_STAGE0_STEREOSWITCHNOSLEW_FIXPT 0x00000000
#define MOD_NX2_1_ALG0_STAGE0_STEREOSWITCHNOSLEW_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_NX2_1_ALG0_STAGE0_STEREOSWITCHNOSLEW_TYPE  SIGMASTUDIOTYPE_FIXPOINT
#define MOD_NX2_1_ALG0_STAGE1_STEREOSWITCHNOSLEW_ADDR  9
#define MOD_NX2_1_ALG0_STAGE1_STEREOSWITCHNOSLEW_FIXPT 0x00800000
#define MOD_NX2_1_ALG0_STAGE1_STEREOSWITCHNOSLEW_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_NX2_1_ALG0_STAGE1_STEREOSWITCHNOSLEW_TYPE  SIGMASTUDIOTYPE_FIXPOINT

#endif
