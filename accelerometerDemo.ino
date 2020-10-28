 
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
const int buzzer = 5;


Adafruit_MMA8451 mma = Adafruit_MMA8451();

float count1, count2, count3, delta1, delta2, avgdelta;
  
void setup(void) {
  Serial.begin(9600);
  Serial.println("Adafruit MMA8451 test!");
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  mma.setRange(MMA8451_RANGE_8_G);
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");
  count2 = 9.7;
  count3 = 9.7;
}

void loop() {

  sensors_event_t event; 
  mma.getEvent(&event);  
  count1 = event.acceleration.z ;

 delta1 = abs(count1 - count2);
 delta2 = abs(count2 - count3);
 avgdelta = (delta1+delta2)/2;
 if (avgdelta > 0.35)
    { Serial.print("Walking");
    tone(buzzer, 400) ;
    }
    else { Serial.print("Standing");
    noTone(buzzer) ;
    }
     count3 = count2;
    count2 = count1;
  Serial.println();
  delay(100);

  
}
