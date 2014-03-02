#include "wytrawianie.h"
#include "HD44780.h"
#include "EEPROM.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void przekazniki_init()
{
    PRZEKAZNIK_KTORY_DDR |= (1 << PRZEKAZNIK_NAPOW_P) | (1 << PRZEKAZNIK_TEMP_P);
    PRZEKAZNIK_KTORY_PORT &= ~(1 << PRZEKAZNIK_NAPOW_P) | (1 << PRZEKAZNIK_TEMP_P); //domyœlnie wylaczone

    GRZANIE = 0;
    MIESZANIE = 0;
}

void przyciski_init()
{
    PRZYCISK_KTORY_DDR &= ~(1 << PRZYCISK_KTORY_P);
    PRZYCISK_KTORY_PORT |= (1 << PRZYCISK_KTORY_P); // stan wysoki na przycisku, niski uruchamia

    //INT0 i INT1 niski stan wyzwala przerwanie
    DDRD &= ~((1 << PD2) | (1 << PD3));
    PORTD |= (1 << PD2) | (1 << PD3);

    MCUCR = 0;
    GICR = (1 << INT1) | (1 << INT0);
}

void sprawdz_grzanie(int aktualna_temp)
{
    if (GRZANIE == 1)
    {
        if (aktualna_temp < (TEMPERATURA + TEMPERATURA*DOKLADNOSC))
            return;
        wylacz_grzanie();
    }
    else
    {
        if (aktualna_temp < (TEMPERATURA - TEMPERATURA*DOKLADNOSC))
            wlacz_grzanie();
    }
}

void timer_init()
{
    TCCR1B |= (1 << CS12); //preskaler 256
    TIMSK |= (1 << TOIE1); //wlaczenie przerwania - okolo 1 s
    TIMER_MIESZANIE = 0;
    TIMER_ILE_SEK = 0;
    MIESZANIE_ILE_BEZ = 0;
    MIESZANIE_ILE_Z = 0;
}

void wlacz_grzanie()
{
    PRZEKAZNIK_KTORY_PORT |= (1 << PRZEKAZNIK_TEMP_P);
    LCD_GoTo(14,0);
    LCD_WriteText("*");
    GRZANIE = 1;
}

void wlacz_mieszanie()
{
    PRZEKAZNIK_KTORY_PORT |= (1 << PRZEKAZNIK_NAPOW_P);
    LCD_GoTo(14,1);
    LCD_WriteText("*");
    MIESZANIE = 1;
    MIESZANIE_ILE_BEZ = 0;
    MIESZANIE_ILE_Z = 1;
}

void wylacz_grzanie()
{
    PRZEKAZNIK_KTORY_PORT &= ~(1 << PRZEKAZNIK_TEMP_P);
    LCD_GoTo(14,0);
    LCD_WriteText(" ");
    GRZANIE = 0;
}

void wylacz_mieszanie()
{
    PRZEKAZNIK_KTORY_PORT &= ~(1 << PRZEKAZNIK_NAPOW_P);
    LCD_GoTo(14,1);
    LCD_WriteText(" ");
    MIESZANIE = 0;
    MIESZANIE_ILE_BEZ = 1;
    MIESZANIE_ILE_Z = 0;
}

void wytrawianie_init()
{
    TEMPERATURA = EEPROM_read(EEPROM_TEMP);
    if (TEMPERATURA < TEMP_MIN || TEMPERATURA > TEMP_MAKS)
        TEMPERATURA = TEMP_DOMYSLNA;
    NAPOWIETRZANIE = EEPROM_read(EEPROM_NAPOW);
    if (NAPOWIETRZANIE < NAPOW_MIN || NAPOWIETRZANIE > NAPOW_MAKS)
        NAPOWIETRZANIE = NAPOW_DOMYSLNE;
    AKTYWNY = 1;

    char *temp = Int_to_char(TEMPERATURA, 2);
    LCD_GoTo(11,0);
    LCD_WriteText("/");
    LCD_WriteText(temp);
    free(temp);

    temp = Int_to_char(NAPOWIETRZANIE, 1);
    LCD_GoTo(10,1);
    LCD_WriteText(temp);
    LCD_WriteText("/");
    free(temp);

    temp = Int_to_char(NAPOW_MAKS, 1);
    LCD_GoTo(12,1);
    LCD_WriteText(temp);
    free(temp);

    LCD_GoTo(15,0);
    LCD_WriteText("+");

    przyciski_init();
}

void zapisz_domyslne()
{
    int *i = malloc(sizeof(int));
    *i = 0;
    LCD_GoTo(3,0);
    LCD_WriteText("ZAPIS");
    LCD_GoTo(3,1);
    LCD_WriteText("      ");
    LCD_GoTo(3,1);
    for(*i = 0; *i < 6; (*i)++)
    {
        LCD_GoTo(3+*i,1);
        LCD_WriteText(".");
        _delay_ms(100);
    }

    if(EEPROM_read(EEPROM_TEMP) != TEMPERATURA) EEPROM_write(EEPROM_TEMP, TEMPERATURA);
    if(EEPROM_read(EEPROM_NAPOW) != NAPOWIETRZANIE) EEPROM_write(EEPROM_NAPOW, NAPOWIETRZANIE);
    free(i);

//    while(!bit_is_clear(PRZYCISK_ZAPISZ_PIN, PRZYCISK_ZAPISZ_NR)) {}
    LCD_Tekst_startowy();
}

void zmien_aktywny()
{
    if (AKTYWNY == 1)
    {
        LCD_GoTo(15,0);
        LCD_WriteText(" ");
        LCD_GoTo(15,1);
        LCD_WriteText("+");
        AKTYWNY = 2;
    }
    else
    {
        LCD_GoTo(15,1);
        LCD_WriteText(" ");
        LCD_GoTo(15,0);
        LCD_WriteText("+");
        AKTYWNY = 1;
    }
    _delay_ms(250); // żeby nie przelaczal sie jak pojebany
}

ISR(INT0_vect)
{
    if (AKTYWNY == 1 && TEMPERATURA < TEMP_MAKS) //temperatura
    {
        TEMPERATURA++;
        char *temp = Int_to_char(TEMPERATURA, 2);
        LCD_GoTo(12,0);
        LCD_WriteText(temp);
        free(temp);
    }
    if (AKTYWNY == 2 && NAPOWIETRZANIE < NAPOW_MAKS) //temperatura
    {
        NAPOWIETRZANIE++;
        char *temp = Int_to_char(NAPOWIETRZANIE, 2);
        LCD_GoTo(10,1);
        LCD_WriteText(temp);
        free(temp);
    }
    GICR = 0;
    _delay_ms(OPOZNIENIE_MS); //zeby nie napieprzalo za szybko
    GICR = (1 << INT1) | (1 << INT0);
}

ISR(INT1_vect)
{
    if (AKTYWNY == 1 && TEMPERATURA > TEMP_MIN) //temperatura
    {
        TEMPERATURA--;
        char *temp = Int_to_char(TEMPERATURA, 2);
        LCD_GoTo(12,0);
        LCD_WriteText(temp);
        free(temp);
    }
    if (AKTYWNY == 2 && NAPOWIETRZANIE > NAPOW_MIN) //temperatura
    {
        NAPOWIETRZANIE--;
        char *temp = Int_to_char(NAPOWIETRZANIE, 2);
        LCD_GoTo(10,1);
        LCD_WriteText(temp);
        free(temp);
    }
    GICR = 0;
    _delay_ms(OPOZNIENIE_MS);
    GICR = (1 << INT1) | (1 << INT0);
}

ISR(TIMER1_OVF_vect)
{
    if (TIMER_ILE_SEK < SEKUND)
        TIMER_ILE_SEK++;
    else
    {
        TIMER_ILE_SEK = 0;
        if (NAPOWIETRZANIE == NAPOW_MAKS)
        {
            if (!MIESZANIE)
                wlacz_mieszanie();
        }
        else if (NAPOWIETRZANIE == 0)
        {
            if (MIESZANIE)
                wylacz_mieszanie();
        }
        else if (MIESZANIE)
        {
            if (MIESZANIE_ILE_Z >= NAPOWIETRZANIE)
                wylacz_mieszanie();
            else
                MIESZANIE_ILE_Z++;
        }
        else if (!MIESZANIE)
        {
            if (MIESZANIE_ILE_BEZ >= NAPOW_MAKS - NAPOWIETRZANIE)
                wlacz_mieszanie();
            else
                MIESZANIE_ILE_BEZ++;
        }
    }
}
