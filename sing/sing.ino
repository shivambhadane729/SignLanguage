#include <Wire.h>

#define MPU_ADDR 0x68

// -------- FLEX SENSOR PINS --------
#define FLEX_THUMB   32
#define FLEX_INDEX   33
#define FLEX_MIDDLE  34
#define FLEX_RING    35
#define FLEX_PINKY   26   // ADC2 pin (OK since no WiFi/BT)

// -------- MPU6050 VARIABLES --------
int16_t ax, ay, az;
int16_t gx, gy, gz;

bool headerPrinted = false;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // -------- ADC SETUP --------
  analogReadResolution(12);        // 0–4095
  analogSetAttenuation(ADC_11db);  // Full 3.3V range

  // -------- I2C SETUP --------
  Wire.begin(21, 22);  // SDA, SCL

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
}

void loop() {

  // Print CSV header once
  if (!headerPrinted) {
    Serial.println("thumb,index,middle,ring,pinky,accX,accY,accZ,gyroX,gyroY,gyroZ");
    headerPrinted = true;
  }

  // -------- FLEX SENSOR READINGS --------
  int thumb  = analogRead(FLEX_THUMB);
  int index  = analogRead(FLEX_INDEX);
  int middle = analogRead(FLEX_MIDDLE);
  int ring   = analogRead(FLEX_RING);
  int pinky  = analogRead(FLEX_PINKY);

  // -------- MPU6050 READINGS --------
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read(); // temperature ignored
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();

  // -------- CSV OUTPUT (TRAINING DATA) --------
  Serial.print(thumb);  Serial.print(",");
  Serial.print(index);  Serial.print(",");
  Serial.print(middle); Serial.print(",");
  Serial.print(ring);   Serial.print(",");
  Serial.print(pinky);  Serial.print(",");
  Serial.print(ax);     Serial.print(",");
  Serial.print(ay);     Serial.print(",");
  Serial.print(az);     Serial.print(",");
  Serial.print(gx);     Serial.print(",");
  Serial.print(gy);     Serial.print(",");
  Serial.println(gz);

  delay(50);  // 20 Hz sampling (ML-friendly)
}
