#include "main.h"

extern unsigned char operational_flag = POWER_ON_SCREEN;
int min, sec,temp;
int pre_time;
char sec_arr[3], min_arr[4],temp_arr[4],pre_time_arr[4],pre_heat_arr[6];
//int temp = 0; //convection temperature
extern unsigned char reset_flag;
/*Add function definitions here*/

void power_on_screen()
{
    unsigned char i;
    for(i = 0; i < 16; i++)
    {
        clcd_putch(0xFF,LINE1(i));
        clcd_putch(0xFF,LINE4(i));
        __delay_ms(100);
    }
    clcd_print("Powering On...",LINE2(0));
    clcd_print("Microwave Oven",LINE3(0));
}
void display_menu()
{
    clcd_print("1. Micro        ", LINE1(0));
    clcd_print("2. Grill        ", LINE2(0));
    clcd_print("3. Convection   ", LINE3(0));
    clcd_print("4. Start        ", LINE4(0));
}

void set_time(unsigned char key)
{
    static unsigned int delay, flag, digit_count, field; //delay-->blinking on lcd display digit_count -->how many digits user entered field-->sec or minute--mode
    
    if(reset_flag >= MICRO_RESET)
    {
        sec = 0;
        min = 0;
        delay = 0;
        flag = 0;
        digit_count = 0;
        field = 0;
        key = ALL_RELEASED;
        
        clcd_print("Set Time <MM:SS", LINE1(0));
        clcd_print("Time: 00:00",LINE2(0));
        clcd_print("*:CLEAR  #:ENTER",LINE4(0)); //*-->clear and #-->confirms
             
    }
    //here 1st digits go to seconds and next digits go to min
    //for eg sec=25,min08 like this
    if(key != ALL_RELEASED && key!='*' && key!='#')
    {
        digit_count++;
        if(digit_count <= 2)
        {
            sec = sec*10+key;
            field = 0;
            if(sec > 59)
            {
                min++;
                sec=0;
            }
        }
        else if(digit_count > 2 && digit_count < 5)
        {
            min=min*10+key;
            field = 1;
        }
        if(digit_count < 2)
        {
            field = 0;
        }
        else if(digit_count > 2 && digit_count < 5)
        {
            field = 1;
        }
    }
    else if(key == '*')
    {
        if(digit_count > 2 && digit_count < 5)
        {
            min = 0;
            digit_count = 2;
        }
        else if(digit_count <= 2)
        {
            sec = 0;
            digit_count = 0;
        }
    }
    else if(key == '#')
    {
        clear_screen();
        TMR2ON = 1;
        FAN = 1; //fan turn on
        digit_count = 0;
        field = 0;
        operational_flag = DISPLAY_TIME;
    }
    
    sec_arr[0]=sec/10+'0';
    sec_arr[1]=sec%10+'0';
    sec_arr[2]='\0';
    
    min_arr[0]=min/10+'0';
    min_arr[1]=min%10+'0';
    min_arr[2]=':';
    min_arr[3]='\0';
    
    if(delay++ == 50)
    {
        delay = 0;
        flag =! flag;
        clcd_print(sec_arr,LINE2(9));
        clcd_print(min_arr,LINE2(6));
    }
    if(flag)
    {
        if(!flag)
        {
            clcd_print(" ",LINE2(10));
            clcd_print(" ",LINE2(9));
        }
        else
        {
            clcd_print(" ",LINE2(7));
            clcd_print(" ",LINE2(6));
        }
    }
}

void display_time()
{
    clcd_print("Time= ",LINE1(0));
    sec_arr[0]=sec/10+'0';
    sec_arr[1]=sec%10+'0';
    sec_arr[2]='\0';
    
    clcd_print(sec_arr,LINE1(9));
    
    clcd_putch(':',LINE1(8));
    min_arr[0]=min/10+'0';
    min_arr[1]=min%10+'0';
    min_arr[2]='\0';
    
    clcd_print(min_arr,LINE1(6));
    
    clcd_print("4.Start/Resume",LINE2(0));
    clcd_print("5.Pause",LINE3(0));
    clcd_print("6.Stop",LINE4(0));
    
    if(min==0 && sec==0)
    {
        clear_screen();
        FAN = 0;
        clcd_print("Time up!!!!",LINE2(4));
        clcd_print("Enjoy your meal!!",LINE3(0));
        BUZZER = 1;
        __delay_ms(5000);
        BUZZER = 0;
        operational_flag = MENU_SCREEN;
    }
}

void set_temp(unsigned char key, unsigned char reset_flag)
{
    static unsigned int temp_count, delay, flag;
    if(reset_flag == CONVECTION_RESET)
    {
        temp = 0;
        key = ALL_RELEASED;
        temp_count = 0;
        flag = 0;
        delay = 0;
        clcd_print("SET TEMP <*C>",LINE1(0));
        clcd_print("Temp: 000",LINE2(0));
        clcd_print("*:CLEAR  #:ENTER",LINE4(0));
        
    }
    
    if(key != ALL_RELEASED && key != '*' && key != '#')
    {
        temp_count++;
        if(temp_count <= 3)
        {
            temp = temp*10+key;
            if(temp > 180)
            {
                temp = 180;
            }
        }
    }
    else if(key == '*')
    {
        temp = 0;
        temp_count = 0;
    }
    else if(key == '#')
    {
        clear_screen();
        TMR2ON = 1;
        FAN = 1;
        pre_time = 60;
        clcd_print("Pre-Heating",LINE1(4));
        
        while(pre_time>0)
        {
            clcd_print("Time left: ",LINE2(0));
            pre_time_arr[0] = '0';
            pre_time_arr[1] = pre_time/10+'0';
            pre_time_arr[2] = pre_time%10+'0';
            pre_time_arr[4] = '\0';
            
            clcd_print(pre_time_arr,LINE2(10));
            clcd_putch('s',LINE2(13));
            
            __delay_ms(1000);
            pre_time--;
        }
        
        if(pre_time==0)
        {
            clear_screen();
            BUZZER = 1;
            FAN    = 0;
            clcd_print("Pre Heating done",LINE1(0));
            __delay_ms(3000);
            BUZZER = 0;
            TMR2ON = 0;
            
            clear_screen();
            
            operational_flag = MICRO_MODE;
            reset_flag = MICRO_RESET;
            clcd_print("Set Time <MM:SS>",LINE1(0));
            clcd_print("Time: 00:00",LINE2(0));
            
            clcd_print("*:CLEAR #:ENTER",LINE4(0));
            
            sec = 0;
            min = 0;
        }
    }
    
    temp_arr[0] = (temp/100)+'0';
    temp_arr[1] = ((temp/10)%10)+'0';
    temp_arr[2] = (temp%10)+'0';
    temp_arr[3] = '\0';
    
    if(delay++==50)
    {
        delay = 0;
        flag =! flag;
        clcd_print(temp_arr,LINE2(6));
    }
    if(flag)
    {
        clcd_print(" ",LINE2(6));
        clcd_print(" ",LINE2(7));
        clcd_print(" ",LINE2(8));
        
    }
}
void start_pre_heat()
{
    pre_time = 30;
    clcd_print("Pre-Heating",LINE1(4));
    
    while(pre_time > 0)
    {
        clcd_print("Time left: ",LINE2(0));
        pre_heat_arr[0] = '0';
        pre_heat_arr[1] = '0';
        pre_heat_arr[2] = ':';
        pre_heat_arr[3] = pre_time/10+'0';
        pre_heat_arr[4] = pre_time%10+'0';
        pre_heat_arr[5] = '\0';
        
        clcd_print(pre_heat_arr,LINE2(10));
        clcd_putch('s', LINE2(15));
        
        __delay_ms(1000);
        pre_time--;    
    }
    if(pre_time == 0)
    {
        clear_screen();
        BUZZER = 1;
        FAN = 0;
        clcd_print("Pre Heating done",LINE1(0));
        __delay_ms(3000);
        BUZZER = 0;
        TMR2ON = 0;
        
        clear_screen();
        operational_flag = MENU_SCREEN;
    }
    
}
void clear_screen()
{
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE); // clear the previous screen
    __delay_us(500);
}