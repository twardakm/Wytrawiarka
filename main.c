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
    przekazniki_init();
    timer_init();
    sei();

    while(1)
    {
        if(bit_is_clear(PRZYCISK_KTORY_PIN, PRZYCISK_TEMP_NR))
            ustaw_temp_aktywny();
        if(bit_is_clear(PRZYCISK_KTORY_PIN, PRZYCISK_NAPOW_NR))
            ustaw_napow_aktywny();
        _delay_ms(50);
    }

    return 0;
}
