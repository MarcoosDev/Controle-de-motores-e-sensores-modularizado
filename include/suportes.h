#ifndef SUPORTE_H
#define SUPORTE_H

#include <Arduino.h>

inline unsigned long agora() {
    return millis();
}

inline void esperar_segundos(unsigned long segundos) {
    delay(segundos * 1000);
}

#endif