#ifndef _WYTRAWIANIE_H
#define _WYTRAWIANIE_H

#include "HD44780.h"

#define TEMP_DOMYSLNA 50
#define TEMP_MAKS 80
#define TEMP_MIN 20
#define NAPOW_DOMYSLNE 5
#define NAPOW_MAKS 9
#define NAPOW_MIN 0

#define PRZYCISK_KTORY_DDR DDRC
#define PRZYCISK_KTORY_PORT PORTC
#define PRZYCISK_KTORY_PIN PINC
#define PRZYCISK_TEMP_P PC1
#define PRZYCISK_TEMP_NR 1
#define PRZYCISK_NAPOW_P PC2
#define PRZYCISK_NAPOW_NR 2

#define OPOZNIENIE_MS 200

volatile unsigned short int TEMPERATURA;
volatile unsigned short int NAPOWIETRZANIE;
volatile unsigned short int AKTYWNY; //1 - temperatura, 2 - napowietrzanie;

void przyciski_init();
void ustaw_napow_aktywny();
void ustaw_temp_aktywny();
void wytrawianie_init();

#endif // _WYTRAWIANIE_H
