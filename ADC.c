#include <avr/io.h>
#include "ADC.h"

void ADC_Init()
{
    ADCSRA = (1 << ADEN) | (1 << ADFR) | (1 << ADIE) | //ADEN: ADC Enable, free running, interrupt
    (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);  // preskaler = 128
    ADMUX = (1 << REFS1) | (1 << REFS0); //wewntrzne napicie odniesienia 2.56 V, wejœcie ADC0
    DDRC &= ~(1 << ADCTERM); //wejscie ADC
    PRESKALER = 0;

    //start pierwszej konwersji
    ADCSRA |= (1 << ADSC);
}
