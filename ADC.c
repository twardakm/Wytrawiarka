#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "ADC.h"
#include "HD44780.h"

void ADC_Init()
{
    ADCSRA |= (1 << ADEN) | (1 << ADFR) | (1 << ADIE) |
    (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);//ADEN: ADC Enable, free running, interrupt preskaler 128
    ADMUX = (1 << REFS1) | (1 << REFS0); //wewntrzne napicie odniesienia 2.56 V, wejœcie ADC0
    DDRC &= ~(1 << ADCTERM); //wejscie ADC
    PRESKALER = 0;

    //start pierwszej konwersji
    ADCSRA |= (1 << ADSC);
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
