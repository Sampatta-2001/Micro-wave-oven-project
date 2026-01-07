/* 
 * File:   main.c
 * Author: Sampatta Ghulanawar
 *
 * Created on 21 September, 2025, 1:33 PM
 * Micro --> cook the food
 * Grill --> Grill purpose
 * Convection --> baking
 * start --> re-heat the food
 */


#include "main.h"
#pragma config WDTE = OFF
extern int min = 0,sec = 0;
unsigned char operational_flag = MENU_SCREEN;
unsigned char reset_flag = RESET_NOTHING;

static void init_config(void) 
{
    init_clcd();
    init_matrix_keypad();
    
    FAN_DDR = 0;
    FAN = 0;
    BUZZER_DDR = 0;
    BUZZER = 0;

    init_timer2();
    GIE = 1;
    PEIE = 1;
}

void main(void) 
{
    init_config();
    power_on_screen();
    unsigned char key;
    operational_flag = MENU_SCREEN;
    while (1) {
        key = read_matrix_keypad(STATE);
        if (operational_flag == MENU_SCREEN) {
            if (key == 1) 
            {
                /*Update flags and clear screen*/
                 clear_screen();
                 operational_flag = MICRO_MODE;
                 reset_flag = MICRO_RESET;
                 clcd_print("POWER: 900W",LINE2(4));
                 __delay_ms(3000);
                 clear_screen();

            } 
            else if (key == 2) 
            {
                /*Update flags and clear screen*/
                clear_screen();
                operational_flag = GRILL_MODE;
                reset_flag = GRILL_RESET;
            } else if (key == 3) 
            {
                /*Update flags and clear screen*/
                clear_screen();
                operational_flag = CONVECTION_MODE;
                reset_flag = CONVECTION_RESET;
                
            } else if (key == 4) 
            {
                /*Update flags and clear screen*/
                clear_screen();
                TMR2ON = 1;
                FAN = 1;
                operational_flag = START_MODE;
                reset_flag = START_RESET;
            }
        } 
        else if (operational_flag == DISPLAY_TIME) 
        {
            //Add logic
            if(key == 4)
            {
                sec = sec+30;
                if(sec > 59)
                {
                    min = min+1;
                    sec = sec-60;
                }
            }
            else if(key == 5)
            {
                //FAN = 0;
                operational_flag = PAUSE;
            }
            else if(key == 6)
            {
                FAN = 0;
                operational_flag = MENU_SCREEN;
            }
        } 
        else if (operational_flag == PAUSE) 
        {
            //Add logic
            if(key == 4)
            {
                TMR2ON = 1;
                FAN = 1;
                operational_flag = DISPLAY_TIME;
            }
        }

        switch (operational_flag) 
        {
//            case POWER_ON_SCREEN:
//                //Add logic
//                power_on_screen();
//                break;
            case MENU_SCREEN:
                //Add logic
                display_menu();
                break;
            case DISPLAY_TIME:
                //add logic
                display_time();
                break;
            case MICRO_MODE:
                //Add logic
                TMR2ON = 0;
                set_time(key);
                break;
            case GRILL_MODE:
               //Add logic
                TMR2ON = 0;
                set_time(key);
                break;
            case CONVECTION_MODE:
              //add logic
                set_temp(key,reset_flag);
                break;
            case START_MODE:
              //add logic
                TMR2ON=1;
                FAN=1;
                start_pre_heat();
                break;
            case PAUSE:
             //add logic
                FAN=0;
                TMR2ON=0;
                break;

        }
        reset_flag = RESET_NOTHING;
    }
    //return 0;
}

