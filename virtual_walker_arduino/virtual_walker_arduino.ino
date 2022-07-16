#include <Wire.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

// i2c
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

void setup() 
{
  Serial.begin(115200);
  lsm.begin();
}

void loop() 
{
  lsm.read();  /* ask it to read in the data */ 

  /* Get a new sensor event */ 
  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 

  Serial.print("AX: "); Serial.print(a.acceleration.x);Serial.print(" ");
  Serial.print("\tAY: "); Serial.print(a.acceleration.y);Serial.print(" ");
  Serial.print("\tAZ: "); Serial.print(a.acceleration.z);Serial.print(" ");

  Serial.print("\tGX: "); Serial.print(g.gyro.x);Serial.print(" ");
  Serial.print("\tGY: "); Serial.print(g.gyro.y);Serial.print(" ");
  Serial.print("\tGZ: "); Serial.print(g.gyro.z);Serial.print(" ");

  Serial.println();
}
