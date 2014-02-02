/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "HD44780.h"
#include "ADC.h"

int main(void)
{
    LCD_Initalize();
    ADC_Init();
    sei();

    while(1);

    return 0;
}

ISR(ADC_vect)
{
    if (PRESKALER < ADC_MAKS)
        PRESKALER++;
    else
    {
        PRESKALER = 0;
        char Temp[8];
        sprintf(Temp, "%i", ADC);
        LCD_WriteText(Temp);
    }
}
