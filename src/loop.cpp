#include <main.h>

static unsigned long t = 0;

void fazerCurvaLEsquerda();
void fazerCurvaLDireita();

void loop() 
{
  sensor.update();

  bool E = sensor.esquerda;
  bool M = sensor.meio;
  bool D = sensor.direita;

  if ((E && D) || (!E && !M && !D))
    mover.frente();

  else if (!E && M && D)
    mover.esquerda();

  else if (E && M && !D)
    mover.direita();

  else if (!E && !M && D)
    mover.esquerda();

  else if (E && !M && !D)
    mover.direita();

  else
    mover.parar();

  contador++;

  if (millis() - ultimoTempo >= 1000) 
  {
    Serial.printf("Loops/s: %lu\n", contador);
    contador = 0;
    ultimoTempo = millis();
  }

}

void fazerCurvaLEsquerda()
{
  mover.frente(100); 
  mover.parar(200);
  gyro.resetAngle();
  mover.esquerda();
  do 
  {
    sensor.update();
    gyro.update();
  } 
  while (sensor.direita == BRANCO && gyro.getAngleZ() < 110);

}

void fazerCurvaLDireita()
{
  mover.frente(100); 
  mover.parar(200);
  gyro.resetAngle();
  mover.direita();
  do 
  {
    sensor.update();
    gyro.update();
  } 
  while (sensor.direita == BRANCO && gyro.getAngleZ() > -110);

}