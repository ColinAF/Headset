#include <Wire.h>

const int MPU_ADDR = 0x68;  // I2C address of MPU-6050

void setup() {
    Wire.begin();
    Serial.begin(115200);

    // Wake up MPU-6050
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B);  // Power management register
    Wire.write(0);     // Wake up!
    Wire.endTransmission();
}

void loop() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);  // Starting register for accelerometer data
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 14, true); // Request 14 bytes (accel + gyro)

    // Read raw values
    int16_t accelX = Wire.read() << 8 | Wire.read();
    int16_t accelY = Wire.read() << 8 | Wire.read();
    int16_t accelZ = Wire.read() << 8 | Wire.read();
    int16_t temp   = Wire.read() << 8 | Wire.read(); // Temperature (ignored)
    int16_t gyroX  = Wire.read() << 8 | Wire.read();
    int16_t gyroY  = Wire.read() << 8 | Wire.read();
    int16_t gyroZ  = Wire.read() << 8 | Wire.read();

    // Send data over USB (Serial)
    Serial.print(accelX); Serial.print(",");
    Serial.print(accelY); Serial.print(",");
    Serial.print(accelZ); Serial.print(",");
    Serial.print(gyroX); Serial.print(",");
    Serial.print(gyroY); Serial.print(",");
    Serial.println(gyroZ); // Newline to signal end of data

    delay(10);  // 10ms delay (adjust based on performance needs)
}

