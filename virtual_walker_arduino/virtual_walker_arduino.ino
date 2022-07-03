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

  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2");
  Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
  Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");

//  Serial.print("Gyro X: "); Serial.print(g.gyro.x);   Serial.print(" rad/s");
//  Serial.print("\tY: "); Serial.print(g.gyro.y);      Serial.print(" rad/s");
//  Serial.print("\tZ: "); Serial.print(g.gyro.z);      Serial.println(" rad/s");

  Serial.println();

}
