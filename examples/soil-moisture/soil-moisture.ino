#define SOIL_SENS_PIN A0

int readSoil() {
  int soil_value = analogRead(SOIL_SENS_PIN);

  float voltage = soil_value * (3.2 / 1023.0);
  // print out the value you read:
  Serial.println("voltage: " + String(voltage));
  Serial.println("value: " + String(soil_value));

  return soil_value;
}

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  
  readSoil();

  delay(1500);
}
