/*
 * File:           E:\projects\my-project1_IC_1_PARAM.h
 *
 * Created:        Wednesday, May 06, 2020 10:48:01 PM
 * Description:    my-project1:IC 1 parameter RAM definitions.
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
#ifndef __MY_PROJECT1_IC_1_PARAM_H__
#define __MY_PROJECT1_IC_1_PARAM_H__


/* Module Modulo Size - Modulo Size*/
#define MOD_MODULOSIZE_COUNT                           1
#define MOD_MODULOSIZE_DEVICE                          "IC1"
#define MOD_MODULOSIZE_MODULO_SIZE_ADDR                0
#define MOD_MODULOSIZE_MODULO_SIZE_FIXPT               0x00001000
#define MOD_MODULOSIZE_MODULO_SIZE_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(4096)
#define MOD_MODULOSIZE_MODULO_SIZE_TYPE                SIGMASTUDIOTYPE_INTEGER

/* Module DCB2 - DC Blocking*/
#define MOD_DCB2_COUNT                                 1
#define MOD_DCB2_DEVICE                                "IC1"
#define MOD_DCB2_DCBLOCKALGDOUBLEPREC2POLE_ADDR        8
#define MOD_DCB2_DCBLOCKALGDOUBLEPREC2POLE_FIXPT       0x007FFCB9
#define MOD_DCB2_DCBLOCKALGDOUBLEPREC2POLE_VALUE       SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.9999)
#define MOD_DCB2_DCBLOCKALGDOUBLEPREC2POLE_TYPE        SIGMASTUDIOTYPE_FIXPOINT

/* Module DCB1 - DC Blocking*/
#define MOD_DCB1_COUNT                                 1
#define MOD_DCB1_DEVICE                                "IC1"
#define MOD_DCB1_DCBLOCKALGDOUBLEPREC1POLE_ADDR        9
#define MOD_DCB1_DCBLOCKALGDOUBLEPREC1POLE_FIXPT       0x007FFCB9
#define MOD_DCB1_DCBLOCKALGDOUBLEPREC1POLE_VALUE       SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.9999)
#define MOD_DCB1_DCBLOCKALGDOUBLEPREC1POLE_TYPE        SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain2 - Gain*/
#define MOD_GAIN2_COUNT                                1
#define MOD_GAIN2_DEVICE                               "IC1"
#define MOD_GAIN2_GAIN1940ALGNS2_ADDR                  10
#define MOD_GAIN2_GAIN1940ALGNS2_FIXPT                 0x00800000
#define MOD_GAIN2_GAIN1940ALGNS2_VALUE                 SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_GAIN2_GAIN1940ALGNS2_TYPE                  SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain1 - Gain*/
#define MOD_GAIN1_COUNT                                1
#define MOD_GAIN1_DEVICE                               "IC1"
#define MOD_GAIN1_GAIN1940ALGNS1_ADDR                  11
#define MOD_GAIN1_GAIN1940ALGNS1_FIXPT                 0x00800000
#define MOD_GAIN1_GAIN1940ALGNS1_VALUE                 SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_GAIN1_GAIN1940ALGNS1_TYPE                  SIGMASTUDIOTYPE_FIXPOINT

/* Module  - Dynamic Bass Boost*/
#define MOD__COUNT                                     65
#define MOD__DEVICE                                    "IC1"
#define MOD__ALG0_STAGE0_B0_ADDR                       12
#define MOD__ALG0_STAGE0_B0_FIXPT                      0x00800000
#define MOD__ALG0_STAGE0_B0_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_STAGE0_B0_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE0_B1_ADDR                       13
#define MOD__ALG0_STAGE0_B1_FIXPT                      0x00000000
#define MOD__ALG0_STAGE0_B1_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE0_B1_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE0_B2_ADDR                       14
#define MOD__ALG0_STAGE0_B2_FIXPT                      0x00000000
#define MOD__ALG0_STAGE0_B2_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE0_B2_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE0_A1_ADDR                       15
#define MOD__ALG0_STAGE0_A1_FIXPT                      0x00000000
#define MOD__ALG0_STAGE0_A1_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE0_A1_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE0_A2_ADDR                       16
#define MOD__ALG0_STAGE0_A2_FIXPT                      0x00000000
#define MOD__ALG0_STAGE0_A2_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE0_A2_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE1_B0_ADDR                       17
#define MOD__ALG0_STAGE1_B0_FIXPT                      0x00800000
#define MOD__ALG0_STAGE1_B0_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_STAGE1_B0_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE1_B1_ADDR                       18
#define MOD__ALG0_STAGE1_B1_FIXPT                      0x00000000
#define MOD__ALG0_STAGE1_B1_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE1_B1_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE1_B2_ADDR                       19
#define MOD__ALG0_STAGE1_B2_FIXPT                      0x00000000
#define MOD__ALG0_STAGE1_B2_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE1_B2_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE1_A1_ADDR                       20
#define MOD__ALG0_STAGE1_A1_FIXPT                      0x00000000
#define MOD__ALG0_STAGE1_A1_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE1_A1_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE1_A2_ADDR                       21
#define MOD__ALG0_STAGE1_A2_FIXPT                      0x00000000
#define MOD__ALG0_STAGE1_A2_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE1_A2_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE2_B0_ADDR                       22
#define MOD__ALG0_STAGE2_B0_FIXPT                      0x00800000
#define MOD__ALG0_STAGE2_B0_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_STAGE2_B0_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE2_B1_ADDR                       23
#define MOD__ALG0_STAGE2_B1_FIXPT                      0x00000000
#define MOD__ALG0_STAGE2_B1_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE2_B1_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE2_B2_ADDR                       24
#define MOD__ALG0_STAGE2_B2_FIXPT                      0x00000000
#define MOD__ALG0_STAGE2_B2_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE2_B2_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE2_A1_ADDR                       25
#define MOD__ALG0_STAGE2_A1_FIXPT                      0x00000000
#define MOD__ALG0_STAGE2_A1_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE2_A1_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE2_A2_ADDR                       26
#define MOD__ALG0_STAGE2_A2_FIXPT                      0x00000000
#define MOD__ALG0_STAGE2_A2_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE2_A2_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE3_B0_ADDR                       27
#define MOD__ALG0_STAGE3_B0_FIXPT                      0x00800000
#define MOD__ALG0_STAGE3_B0_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_STAGE3_B0_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE3_B1_ADDR                       28
#define MOD__ALG0_STAGE3_B1_FIXPT                      0x00000000
#define MOD__ALG0_STAGE3_B1_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE3_B1_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE3_B2_ADDR                       29
#define MOD__ALG0_STAGE3_B2_FIXPT                      0x00000000
#define MOD__ALG0_STAGE3_B2_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE3_B2_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE3_A1_ADDR                       30
#define MOD__ALG0_STAGE3_A1_FIXPT                      0x00000000
#define MOD__ALG0_STAGE3_A1_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE3_A1_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE3_A2_ADDR                       31
#define MOD__ALG0_STAGE3_A2_FIXPT                      0x00000000
#define MOD__ALG0_STAGE3_A2_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE3_A2_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE4_B0_ADDR                       32
#define MOD__ALG0_STAGE4_B0_FIXPT                      0x00800000
#define MOD__ALG0_STAGE4_B0_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_STAGE4_B0_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE4_B1_ADDR                       33
#define MOD__ALG0_STAGE4_B1_FIXPT                      0x00000000
#define MOD__ALG0_STAGE4_B1_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE4_B1_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE4_B2_ADDR                       34
#define MOD__ALG0_STAGE4_B2_FIXPT                      0x00000000
#define MOD__ALG0_STAGE4_B2_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE4_B2_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE4_A1_ADDR                       35
#define MOD__ALG0_STAGE4_A1_FIXPT                      0x00000000
#define MOD__ALG0_STAGE4_A1_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE4_A1_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_STAGE4_A2_ADDR                       36
#define MOD__ALG0_STAGE4_A2_FIXPT                      0x00000000
#define MOD__ALG0_STAGE4_A2_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD__ALG0_STAGE4_A2_TYPE                       SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_BASSFREQUENCY_ADDR                   37
#define MOD__ALG0_BASSFREQUENCY_FIXPT                  0x0001015B
#define MOD__ALG0_BASSFREQUENCY_VALUE                  SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.00785396144863598)
#define MOD__ALG0_BASSFREQUENCY_TYPE                   SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_B0_ADDR                              38
#define MOD__ALG0_B0_FIXPT                             0x00000892
#define MOD__ALG0_B0_VALUE                             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.000261651801447962)
#define MOD__ALG0_B0_TYPE                              SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_B1_ADDR                              39
#define MOD__ALG0_B1_FIXPT                             0x00001125
#define MOD__ALG0_B1_VALUE                             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.000523303602895924)
#define MOD__ALG0_B1_TYPE                              SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_B2_ADDR                              40
#define MOD__ALG0_B2_FIXPT                             0x00000892
#define MOD__ALG0_B2_VALUE                             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.000261651801447962)
#define MOD__ALG0_B2_TYPE                              SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_A1_ADDR                              41
#define MOD__ALG0_A1_FIXPT                             0x00FA1389
#define MOD__ALG0_A1_VALUE                             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.95372127660762)
#define MOD__ALG0_A1_TYPE                              SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_A2_ADDR                              42
#define MOD__ALG0_A2_FIXPT                             0xFF85CA2B
#define MOD__ALG0_A2_VALUE                             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-0.954767883813409)
#define MOD__ALG0_A2_TYPE                              SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE0_ADDR                          43
#define MOD__ALG0_TABLE0_FIXPT                         0x00800000
#define MOD__ALG0_TABLE0_VALUE                         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE0_TYPE                          SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE1_ADDR                          44
#define MOD__ALG0_TABLE1_FIXPT                         0x00800000
#define MOD__ALG0_TABLE1_VALUE                         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE1_TYPE                          SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE2_ADDR                          45
#define MOD__ALG0_TABLE2_FIXPT                         0x00800000
#define MOD__ALG0_TABLE2_VALUE                         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE2_TYPE                          SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE3_ADDR                          46
#define MOD__ALG0_TABLE3_FIXPT                         0x00800000
#define MOD__ALG0_TABLE3_VALUE                         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE3_TYPE                          SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE4_ADDR                          47
#define MOD__ALG0_TABLE4_FIXPT                         0x00800000
#define MOD__ALG0_TABLE4_VALUE                         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE4_TYPE                          SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE5_ADDR                          48
#define MOD__ALG0_TABLE5_FIXPT                         0x00800000
#define MOD__ALG0_TABLE5_VALUE                         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE5_TYPE                          SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE6_ADDR                          49
#define MOD__ALG0_TABLE6_FIXPT                         0x00800000
#define MOD__ALG0_TABLE6_VALUE                         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE6_TYPE                          SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE7_ADDR                          50
#define MOD__ALG0_TABLE7_FIXPT                         0x00800000
#define MOD__ALG0_TABLE7_VALUE                         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE7_TYPE                          SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE8_ADDR                          51
#define MOD__ALG0_TABLE8_FIXPT                         0x00800000
#define MOD__ALG0_TABLE8_VALUE                         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE8_TYPE                          SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE9_ADDR                          52
#define MOD__ALG0_TABLE9_FIXPT                         0x00800000
#define MOD__ALG0_TABLE9_VALUE                         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE9_TYPE                          SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE10_ADDR                         53
#define MOD__ALG0_TABLE10_FIXPT                        0x00800000
#define MOD__ALG0_TABLE10_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE10_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE11_ADDR                         54
#define MOD__ALG0_TABLE11_FIXPT                        0x00800000
#define MOD__ALG0_TABLE11_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE11_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE12_ADDR                         55
#define MOD__ALG0_TABLE12_FIXPT                        0x00800000
#define MOD__ALG0_TABLE12_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE12_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE13_ADDR                         56
#define MOD__ALG0_TABLE13_FIXPT                        0x00800000
#define MOD__ALG0_TABLE13_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE13_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE14_ADDR                         57
#define MOD__ALG0_TABLE14_FIXPT                        0x00800000
#define MOD__ALG0_TABLE14_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE14_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE15_ADDR                         58
#define MOD__ALG0_TABLE15_FIXPT                        0x00800000
#define MOD__ALG0_TABLE15_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE15_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE16_ADDR                         59
#define MOD__ALG0_TABLE16_FIXPT                        0x00800000
#define MOD__ALG0_TABLE16_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE16_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE17_ADDR                         60
#define MOD__ALG0_TABLE17_FIXPT                        0x00800000
#define MOD__ALG0_TABLE17_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE17_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE18_ADDR                         61
#define MOD__ALG0_TABLE18_FIXPT                        0x00800000
#define MOD__ALG0_TABLE18_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE18_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE19_ADDR                         62
#define MOD__ALG0_TABLE19_FIXPT                        0x00800000
#define MOD__ALG0_TABLE19_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE19_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE20_ADDR                         63
#define MOD__ALG0_TABLE20_FIXPT                        0x00800000
#define MOD__ALG0_TABLE20_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE20_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE21_ADDR                         64
#define MOD__ALG0_TABLE21_FIXPT                        0x00800000
#define MOD__ALG0_TABLE21_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE21_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE22_ADDR                         65
#define MOD__ALG0_TABLE22_FIXPT                        0x00800000
#define MOD__ALG0_TABLE22_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE22_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE23_ADDR                         66
#define MOD__ALG0_TABLE23_FIXPT                        0x00800000
#define MOD__ALG0_TABLE23_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD__ALG0_TABLE23_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE24_ADDR                         67
#define MOD__ALG0_TABLE24_FIXPT                        0x00A12477
#define MOD__ALG0_TABLE24_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.25892541179417)
#define MOD__ALG0_TABLE24_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE25_ADDR                         68
#define MOD__ALG0_TABLE25_FIXPT                        0x00E39EA8
#define MOD__ALG0_TABLE25_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.77827941003892)
#define MOD__ALG0_TABLE25_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE26_ADDR                         69
#define MOD__ALG0_TABLE26_FIXPT                        0x00E39EA8
#define MOD__ALG0_TABLE26_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.77827941003892)
#define MOD__ALG0_TABLE26_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE27_ADDR                         70
#define MOD__ALG0_TABLE27_FIXPT                        0x00E39EA8
#define MOD__ALG0_TABLE27_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.77827941003892)
#define MOD__ALG0_TABLE27_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE28_ADDR                         71
#define MOD__ALG0_TABLE28_FIXPT                        0x00E39EA8
#define MOD__ALG0_TABLE28_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.77827941003892)
#define MOD__ALG0_TABLE28_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE29_ADDR                         72
#define MOD__ALG0_TABLE29_FIXPT                        0x00E39EA8
#define MOD__ALG0_TABLE29_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.77827941003892)
#define MOD__ALG0_TABLE29_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE30_ADDR                         73
#define MOD__ALG0_TABLE30_FIXPT                        0x00E39EA8
#define MOD__ALG0_TABLE30_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.77827941003892)
#define MOD__ALG0_TABLE30_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE31_ADDR                         74
#define MOD__ALG0_TABLE31_FIXPT                        0x00E39EA8
#define MOD__ALG0_TABLE31_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.77827941003892)
#define MOD__ALG0_TABLE31_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TABLE32_ADDR                         75
#define MOD__ALG0_TABLE32_FIXPT                        0x00E39EA8
#define MOD__ALG0_TABLE32_VALUE                        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.77827941003892)
#define MOD__ALG0_TABLE32_TYPE                         SIGMASTUDIOTYPE_FIXPOINT
#define MOD__ALG0_TIMECONSTANT_ADDR                    76
#define MOD__ALG0_TIMECONSTANT_FIXPT                   0x000006D3
#define MOD__ALG0_TIMECONSTANT_VALUE                   SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.000208311633451363)
#define MOD__ALG0_TIMECONSTANT_TYPE                    SIGMASTUDIOTYPE_FIXPOINT

/* Module ESC1 - Enhanced Stereo Capture (ESC)*/
#define MOD_ESC1_COUNT                                 7
#define MOD_ESC1_DEVICE                                "IC1"
#define MOD_ESC1_ALG0_ESC1ALG1GAIN_ADDR                77
#define MOD_ESC1_ALG0_ESC1ALG1GAIN_FIXPT               0x000CCCCC
#define MOD_ESC1_ALG0_ESC1ALG1GAIN_VALUE               SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.1)
#define MOD_ESC1_ALG0_ESC1ALG1GAIN_TYPE                SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF0_ADDR              78
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF0_FIXPT             0x007FAAE7
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF0_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.997403050860832)
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF0_TYPE              SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF1_ADDR              79
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF1_FIXPT             0x00CA9A58
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF1_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.5828352489552)
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF1_TYPE              SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF2_ADDR              80
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF2_FIXPT             0xFF3565A8
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF2_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1.5828352489552)
#define MOD_ESC1_ALG0_ESC1ALG1A1HPF2_TYPE              SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF0_ADDR              81
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF0_FIXPT             0x007B1A7E
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF0_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.961745990890059)
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF0_TYPE              SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF1_ADDR              82
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF1_FIXPT             0x00083864
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF1_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.0642209842030655)
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF1_TYPE              SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF2_ADDR              83
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF2_FIXPT             0x00000000
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF2_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_ESC1_ALG0_ESC1ALG1A1LPF2_TYPE              SIGMASTUDIOTYPE_FIXPOINT

#endif
