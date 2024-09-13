#include "Adafruit_VL53L0X.h"

// create the sensor object
Adafruit_VL53L0X tof = Adafruit_VL53L0X();

void setupToF(){
  Serial.println("Setting up VL53L0X...");
  
  if (!tof.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    Serial.println(F("Please restart your microcontroller."));
    while(1);
  } 
  
  Serial.println("VL53L0X ready (running in single reading mode).");
}

uint16_t readToF(){
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a range... ");
  tof.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    int range = measure.RangeMilliMeter;
    Serial.print("Distance (mm): "); Serial.println(range);
    return range;

  } else {
    Serial.println(" out of range ");
    return 9999;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  setupToF();
}

void loop() {
  // put your main code here, to run repeatedly:

  readToF();

  delay(2000);
}
