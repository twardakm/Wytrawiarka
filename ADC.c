#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "ADC.h"
#include "HD44780.h"
#include "wytrawianie.h"

void ADC_Init()
{
    ADCSRA |= (1 << ADEN) | (1 << ADFR) | (1 << ADIE) |
    (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);//ADEN: ADC Enable, free running, interrupt preskaler 128
    ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << ADLAR); //wewntrzne napicie odniesienia 2.56 V, wejœcie ADC0, do lewej strony
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
        //wlaczenie badz wylaczenie grzania
        sprawdz_grzanie(ADCH-ODNIESIENIE);
        char *temp = Int_to_char(ADCH - ODNIESIENIE, 8); //wzor strona 199
        LCD_GoTo(9, 0);
        LCD_WriteText(temp);
        free(temp);
    }
}
