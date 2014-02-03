#ifndef _EEPROM_H_
#define _EEPROM_H_

#define EEPROM_TEMP 0
#define EEPROM_NAPOW 1

unsigned char EEPROM_read(unsigned int uiAddress);
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

#endif // _EEPROM_H_
