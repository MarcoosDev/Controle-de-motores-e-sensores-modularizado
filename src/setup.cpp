#include <main.h>

void setup()
{
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.init();
  lcd.backlight();
  sensor.begin();

  bool inicializado = false;

  for (int tentativa = 1; tentativa <= 5; tentativa++)
  {
    if((gyro.begin()))
    {
      inicializado = true;
      break;
    }
  } 
  if (!inicializado) ESP.restart();
  
  gyro.update();
  gyro.resetAngle();
  mover.begin();
  esperar_segundos(1);
}