/*
 * HDC2080.ino
 * This sketch is released AS-IS into the public domain, no guarantee or warranty is given.
 * This Code is not supported by Texas Instruments.
 * 
 * Description: This sketch configures the HDC2080 to monitor for a specific temperature 
 * and humidity range, with regular one second samples. 
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include <HDC2080.h>

#define ADDR 0x40
HDC2080 sensor(ADDR);

float temperature = 0, humidity = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("TinkeringTech HDC2080 Test");

  // Initialize I2C communication
  sensor.begin();
    
  // Begin with a device reset
  sensor.reset();
  
  // Set up the comfort zone
  sensor.setHighTemp(28);         // High temperature of 28C
  sensor.setLowTemp(22);          // Low temperature of 22C
  sensor.setHighHumidity(55);     // High humidity of 55%
  sensor.setLowHumidity(40);      // Low humidity of 40%
  
  // Configure Measurements
  sensor.setMeasurementMode(TEMP_AND_HUMID);  // Set measurements to temperature and humidity
  sensor.setRate(ONE_HZ);                     // Set measurement frequency to 1 Hz
  sensor.setTempRes(FOURTEEN_BIT);
  sensor.setHumidRes(FOURTEEN_BIT);
  
  //begin measuring
  sensor.triggerMeasurement();
}

void loop() {

  Serial.print("Temperature (C): "); Serial.print(sensor.readTemp());
  Serial.print("\t\tHumidity (%): "); Serial.println(sensor.readHumidity());
  
  // Wait 1 second for the next reading
  delay(1000);
  
}