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
#define PRZYCISK_KTORY_P PC3
#define PRZYCISK_KTORY_NR 3
/*#define PRZYCISK_NAPOW_P PC4
#define PRZYCISK_NAPOW_NR 4*/

/*#define PRZYCISK_ZAPISZ_DDR DDRC
#define PRZYCISK_ZAPISZ_PORT PORTC
#define PRZYCISK_ZAPISZ_PIN PINC
#define PRZYCISK_ZAPISZ_P PC1
#define PRZYCISK_ZAPISZ_NR 1*/

#define PRZEKAZNIK_KTORY_DDR DDRC
#define PRZEKAZNIK_KTORY_PORT PORTC
#define PRZEKAZNIK_TEMP_P PC2
#define PRZEKAZNIK_NAPOW_P PC5

#define OPOZNIENIE_MS 200
#define DOKLADNOSC 0.05

#define SEKUND 7

volatile unsigned short int TEMPERATURA;
volatile unsigned short int NAPOWIETRZANIE;
volatile unsigned short int AKTYWNY; //1 - temperatura, 2 - napowietrzanie;
volatile unsigned short int GRZANIE; //1 - gdy grzeje, 0 - gdy nie
volatile unsigned short int MIESZANIE; //1 - gdy miesza, 0 - gdy nie
volatile unsigned short int TIMER_MIESZANIE;
volatile unsigned short int TIMER_ILE_SEK;
volatile unsigned short int MIESZANIE_ILE_BEZ;
volatile unsigned short int MIESZANIE_ILE_Z;

void przekazniki_init();
void przyciski_init();
void sprawdz_grzanie(int aktualna_temp);
void timer_init();
void wlacz_grzanie();
void wlacz_mieszanie();
void wylacz_grzanie();
void wylacz_mieszanie();
void wytrawianie_init();
void zapisz_domyslne();
void zmien_aktywny();

#endif // _WYTRAWIANIE_H
