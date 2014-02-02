#ifndef _ADC
#define _ADC

#define ADCTERM PC0
#define ADC_MAKS F_CPU/128/13 //128 - preskaler, 13 cykli na odczyt
unsigned long int PRESKALER; //wlasny preskaler

void ADC_Init();

#endif // _ADC
