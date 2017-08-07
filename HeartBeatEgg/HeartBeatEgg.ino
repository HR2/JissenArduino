#include <CapacitiveSensor.h>

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4, 2);
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4, 6);
const int solenoidPin = 13;
const int thresholdPin = A0;

void setup() {
  pinMode(solenoidPin, OUTPUT);
  Serial.begin(9600);

  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_4_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void loop() {
  long sensor1 =  cs_4_2.capacitiveSensor(30);
  long sensor2 =  cs_4_6.capacitiveSensor(30);
  Serial.print(sensor1);
  Serial.print(" / ");
  Serial.print(sensor2);
  Serial.println("");

  int threshold = analogRead( thresholdPin );
  threshold = map( threshold, 0, 1023, 200, 1200);

  if ( (sensor1 > threshold) && (sensor2 > threshold)) {
    digitalWrite(solenoidPin, HIGH);
    delay(100);
    digitalWrite(solenoidPin, LOW);
    delay(200);
    digitalWrite(solenoidPin, HIGH);
    delay(50);
    digitalWrite(solenoidPin, LOW);
    delay(1000);
  } else {
    digitalWrite(solenoidPin, LOW);
  }

  delay(10);
}
