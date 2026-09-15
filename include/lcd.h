#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

extern LiquidCrystal_I2C lcd;

inline void exibir_texto(const char *texto, uint8_t linha = 0, uint8_t coluna = 0) {
    lcd.setCursor(coluna, linha);
    lcd.printf("%-16s", texto);   
}

#endif