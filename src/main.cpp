#include <main.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Sensor sensor(2, 3, 4, 600);
Motor motorE(10, 20, 21);     
Motor motorD(5, 6, 7);         

MPU6050Sensor gyro;
ControleMotor mover(motorE,motorD);

static uint32_t contador = 0;
static uint32_t ultimoTempo = millis();