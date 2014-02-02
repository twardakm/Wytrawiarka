#include "wytrawianie.h"
#include "HD44780.h"
#include <stdlib.h>

void wytrawianie_init()
{
    TEMPERATURA = TEMP_DOMYSLNA;
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
}
