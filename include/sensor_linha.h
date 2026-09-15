#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#define PRETO LOW
#define BRANCO HIGH

struct Sensor
{
private:
    int s1;
    int s2;
    int s3;

    float val_esq = 0;
    float val_meio = 0;
    float val_dir = 0;
    float ALFA = 0.2f;

public:

    bool esquerda;
    bool meio;
    bool direita;
    int limite;

    Sensor(int pin1, int pin2, int pin3, int limite)
        : s1(pin1), s2(pin2), s3(pin3), limite(limite)
    {
    }

    void begin()
    {
        pinMode(s1, INPUT);
        pinMode(s2, INPUT);
        pinMode(s3, INPUT);

        val_esq = analogRead(s1);
        val_meio = analogRead(s2);
        val_dir = analogRead(s3);

        esquerda = (val_esq > limite ? BRANCO : PRETO);
        meio = (val_meio > limite ? BRANCO : PRETO);
        direita = (val_dir > limite ? BRANCO : PRETO);
    }

    void update()
    {
        val_esq = val_esq * (1.0f - ALFA) + analogRead(s1) * ALFA;
        val_meio = val_meio * (1.0f - ALFA) + analogRead(s2) * ALFA;
        val_dir = val_dir * (1.0f - ALFA) + analogRead(s3) * ALFA;

        esquerda = (val_esq > limite ? BRANCO : PRETO);
        meio = (val_meio > limite ? BRANCO : PRETO);
        direita = (val_dir > limite ? BRANCO : PRETO);
    }
};

#endif