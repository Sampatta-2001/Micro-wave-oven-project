/* 
 * File:   main.h
 * Author: emertxe-69
 *
 * Created on 12 November, 2024, 5:04 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include "clcd.h"
#include "matrix_keypad.h"
#include "microwave_def.h"
#include "timers.h"
#include <xc.h>

#define POWER_ON_SCREEN  0x01
#define MENU_SCREEN      0x02
#define MICRO_MODE       0x11
#define GRILL_MODE       0x12
#define CONVECTION_MODE  0x13
#define START_MODE       0x14
#define RESET_NOTHING    0x00
#define RESET_MODE       0xFF
#define DISPLAY_TIME     0xDD

#define START           0xAA
#define STOP            0xBB
#define PAUSE           0xCC
#define PRE_HEAT        0xEE

#define MICRO_RESET     0x10
#define GRILL_RESET     0x20
#define CONVECTION_RESET 0x30
#define START_RESET     0x40
#define SUCCESS         0x50

#define FAN_DDR         TRISC2
#define FAN             RC2

#define BUZZER_DDR      TRISC1
#define BUZZER          RC1
#endif	

