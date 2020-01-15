#include <HDC2080.h>
#define ADDR 0x40
HDC2080 sensor(ADDR);

float temperature = 0, humidity = 0;

void setup() {

  Serial.begin(115200);
  while (!Serial);

  // Initialize I2C communication
  sensor.begin();

  // Begin with a device reset
  sensor.reset();

  // Configure Measurements
  sensor.setMeasurementMode(TEMP_AND_HUMID);  // Set measurements to temperature and humidity
  sensor.setRate(ONE_HZ);                     // Set measurement frequency to 1 Hz
  sensor.setTempRes(FOURTEEN_BIT);
  sensor.setHumidRes(FOURTEEN_BIT);

  sensor.triggerMeasurement();
  delay(1000);
  Serial.print("Temperature (C): "); Serial.print(sensor.readTemp());
  Serial.print("\t\tHumidity (%): "); Serial.println(sensor.readHumidity());
  Serial.println("Applying offset");
  //Page 22 of datasheet
  sensor.setTempOffsetAdjust(128); // offset –20.62°C
  sensor.setHumidityOffsetAdjust(128); // offset –25%RH
  delay(1000);
  Serial.print("Temperature (C): "); Serial.print(sensor.readTemp());
  Serial.print("\t\tHumidity (%): "); Serial.println(sensor.readHumidity());
  Serial.println("Reset offset");
  sensor.setTempOffsetAdjust(0); // offset 0°C
  sensor.setHumidityOffsetAdjust(0); // offset 0%RH
  delay(1000);
}

void loop() {
  // Wait 2 seconds for the next reading
  static uint32_t t = 0;
  if (millis() - t > 2000) {
    t = millis();
    Serial.print("Temperature (C): "); Serial.print(sensor.readTemp());
    Serial.print("\t\tHumidity (%): "); Serial.println(sensor.readHumidity());
  }
}
