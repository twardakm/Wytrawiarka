#ifndef _WYTRAWIANIE_H
#define _WYTRAWIANIE_H

#include "HD44780.h"

#define TEMP_DOMYSLNA 50
#define TEMP_MAKS 80
#define NAPOW_DOMYSLNE 5
#define NAPOW_MAKS 9

volatile unsigned short int TEMPERATURA;
volatile unsigned short int NAPOWIETRZANIE;
volatile unsigned short int AKTYWNY; //1 - temperatura, 2 - napowietrzanie;

void wytrawianie_init();

#endif // _WYTRAWIANIE_H
