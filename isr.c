#include <xc.h>
#include "main.h"
extern int sec,min,pre_time;

void __interrupt() isr(void)
{
    static unsigned long int count = 0;
    
    if (TMR2IF == 1)
    { 
        
        //1;16 prescale 
        if (++count == 1250)
        {
            if(sec>0)
            {
                sec--;
            }
            else if(min > 0)
            {
                min--;
                sec=59;
            }
            count = 0;
        }
        
        TMR2IF = 0;
    }
}