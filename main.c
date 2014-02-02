/*
 */

#include <avr/io.h>

int main(void)
{

    LCD_Initalize();
    LCD_WriteText("   Pierwsza");
    LCD_GoTo(3,1);
    LCD_WriteText("Druga");


    while(1);

    return 0;
}
