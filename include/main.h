#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <motor.h>
#include <sensor_linha.h>
#include <sensor_giroscopio.h>
#include <suportes.h>
#include <lcd.h>

#define SDA_PIN 8
#define SCL_PIN 9

extern Sensor sensor;
extern Motor motorE;
extern Motor motorD;
extern MPU6050Sensor gyro;
extern ControleMotor mover;

static uint32_t contador;
static uint32_t ultimoTempo;

#endif
