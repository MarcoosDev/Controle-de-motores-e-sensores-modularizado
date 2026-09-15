#ifndef MPU6050_SENSOR_H
#define MPU6050_SENSOR_H

#include <Arduino.h>
#include <Wire.h>

class MPU6050Sensor
{
private:
    const uint8_t MPU_ADDR = 0x68;

    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;

    float gyroOffsetX = 0;
    float gyroOffsetY = 0;
    float gyroOffsetZ = 0;

    unsigned long lastTime = 0;

public:
    bool begin(){
        Wire.beginTransmission(MPU_ADDR);
        Wire.write(0x6B);
        Wire.write(0);
        if (Wire.endTransmission(true) != 0)
            return false;

        lastTime = millis();
        calibrate();

        return true;
    }

    void calibrate(){
        const int samples = 500;
        long sumX = 0, sumY = 0, sumZ = 0;

        for (int i = 0; i < samples; i++){
            int16_t gx, gy, gz;
            readRawGyro(gx, gy, gz);

            sumX += gx;
            sumY += gy;
            sumZ += gz;

            delay(2);
        }

        gyroOffsetX = (float)sumX / samples;
        gyroOffsetY = (float)sumY / samples;
        gyroOffsetZ = (float)sumZ / samples;
    }

    void update(){
        int16_t gx, gy, gz;
        readRawGyro(gx, gy, gz);

        float gyroX = (gx - gyroOffsetX) / 131.0;
        float gyroY = (gy - gyroOffsetY) / 131.0;
        float gyroZ = (gz - gyroOffsetZ) / 131.0;

        unsigned long now = millis();
        float dt = (now - lastTime) / 1000.0;
        lastTime = now;

        angleX += gyroX * dt;
        angleY += gyroY * dt;
        angleZ += gyroZ * dt;
    }

    float getAngleX() { return angleX; }
    float getAngleY() { return angleY; }
    float getAngleZ() { return angleZ; }

    void resetAngle(){
        angleX = 0;
        angleY = 0;
        angleZ = 0;
        lastTime = millis();
    }

private:
    void readRawGyro(int16_t &gx, int16_t &gy, int16_t &gz){
        Wire.beginTransmission(MPU_ADDR);
        Wire.write(0x43);
        Wire.endTransmission(false);

        Wire.requestFrom(MPU_ADDR, (uint8_t)6);

        gx = (Wire.read() << 8) | Wire.read();
        gy = (Wire.read() << 8) | Wire.read();
        gz = (Wire.read() << 8) | Wire.read();
    }
};

#endif