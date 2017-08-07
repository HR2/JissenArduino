#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);

void setup() {
  Serial.begin(9600);
  tcs.begin();
}

void loop() {
  uint16_t red, green, blue, clear;

  tcs.getRawData(&red, &green, &blue, &clear);

  float r = red;
  float g = green;
  float b = blue;
  uint32_t sum = clear;
  
  r /= sum;
  g /= sum;
  b /= sum;
  r *= 256;
  g *= 256;
  b *= 256;

  if (Serial.available() > 0) {
    Serial.read();
    Serial.println( String((int)r) + "," + String((int)g) + "," + String((int)b));
  }
  delay( 1 );
}
