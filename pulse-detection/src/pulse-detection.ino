/* Project: src */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
    Serial.begin(9600);
  
    /* Initialize accelerometer */
    Serial.println("Adafruit MMA8451 test!");
    if (! mma.begin()) {
        Serial.println("Couldnt start");
    while (1);
    }
    Serial.println("MMA8451 found!");
  
    /* Configure Range */
    mma.setRange(MMA8451_RANGE_2_G);
    Serial.print("Range = "); Serial.print(2 << mma.getRange());  
    Serial.println("G");
    
    /* Configure Data Rate */
    mma.setDataRate(MMA8451_DATARATE_400_HZ);

    /* Configure pulse detection */
    mma.cfgPulseDetection();
}

void loop() {
    /* Read the 'raw' data in 14-bit counts */
    mma.read();
    Serial.print("X:\t"); Serial.print(mma.x); 
    Serial.print("\tY:\t"); Serial.print(mma.y); 
    Serial.print("\tZ:\t"); Serial.print(mma.z); 
    Serial.println();

    /* Get a new sensor event */ 
    sensors_event_t event; 
    mma.getEvent(&event);

    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
    Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
    Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
    Serial.println("m/s^2 ");

    /* Get the orientation of the sensor */
    uint8_t pulseStatus = mma.getPulseStatus();
    Serial.print("Pulse status: \t"); Serial.println(pulseStatus);

    if((pulseStatus & MMA8451_PULSE_XSPEFE) == MMA8451_PULSE_XSPEFE) {
        Serial.println("Single tap event detected on axis : x"); 
    }
    if((pulseStatus & MMA8451_PULSE_XDPEFE) == MMA8451_PULSE_XDPEFE) {
        Serial.println("Double tap event detected on axis : x"); 
    }
    if((pulseStatus & MMA8451_PULSE_YSPEFE) == MMA8451_PULSE_YSPEFE) {
        Serial.println("Single tap event detected on axis : y"); 
    }
    if((pulseStatus & MMA8451_PULSE_YDPEFE) == MMA8451_PULSE_YDPEFE) {
        Serial.println("Double tap event detected on axis : y"); 
    }
    if((pulseStatus & MMA8451_PULSE_ZSPEFE) == MMA8451_PULSE_ZSPEFE) {
        Serial.println("Single tap event detected on axis : z"); 
    }
    if((pulseStatus & MMA8451_PULSE_ZDPEFE) == MMA8451_PULSE_ZDPEFE) {
        Serial.println("Double tap event detected on axis : z"); 
    }
    Serial.println();
    delay(500);
}