/* 
 * File:   microwave_def.h
 * Author: emertxe-69
 *
 * Created on 12 November, 2024, 5:03 PM
 */

#ifndef MICROWAVE_DEF_H
#define	MICROWAVE_DEF_H

/*Add Function Declarations*/
void power_on_screen();
void display_menu();
void set_time(unsigned char key);
void display_time();
void set_temp(unsigned char key,unsigned char reset_flag);
void set_pre_time();
void start_pre_heat();
void clear_screen();

#endif	/* MICROWAVE_DEF_H */

