/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "HD44780.h"
#include "ADC.h"
#include "wytrawianie.h"

int main(void)
{
    LCD_Initalize();
    LCD_Tekst_startowy();
    wytrawianie_init();
    ADC_Init();
    sei();

    while(1);

    return 0;
}
