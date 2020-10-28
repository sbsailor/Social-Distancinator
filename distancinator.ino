#include <Wire.h> //Used for I2C
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

#define    LIDARLite_ADDRESS   0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure     0x00          // Register to write to initiate ranging.
#define    MeasureValue        0x04          // Value to initiate ranging.
#define    RegisterHighLowB    0x8F          // Register to get both High and Low bytes in 1 call.

byte en_LIDAR = A0; //Low makes LIDAR go to sleep, high is normal operation

Adafruit_MMA8451 mma = Adafruit_MMA8451();

const int LEDpin = 10;
const int buzzer = 5;

float velocity1, velocity2, velocity3;
float zAccelOld,zAccelOlder;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  pinMode(LEDpin, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.println("Coming online");
  delay(1000);

  while (readLIDAR() == 0)
  {
    Serial.println("Failed LIDAR read");
    delay(100);
  }
  
  Serial.println("Adafruit MMA8451 test!");
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  
  Serial.println("MMA8451 found!");
  mma.setRange(MMA8451_RANGE_8_G);
  Serial.print("Range = "); Serial.print(2 << mma.getRange());
  Serial.println("G");

  zAccelOld = 9.7;
  zAccelOlder = 9.7;
  velocity1 = 0;
  velocity2 = 0;
  velocity3 = 0;
  delay(500);

}

void loop()
{
  static int oldDistance = 0;
  static unsigned long oldTime = 0;
  int newTime = millis();
  int newDistance = readLIDAR();
  
  int dt = newTime - oldTime;
  oldTime = newTime;
  
  int dx = newDistance - oldDistance;
  oldDistance = newDistance;
  dx = abs(dx);
  
  velocity3 = velocity2;
  velocity2 = velocity1; 
  velocity1 = (float)dx / (float)dt;

  //22.36936 comes from a big coversion from cm/ms to mile/hour - Math confirmed by Sam
  float instantMPH = 22.3696 * (velocity1 + velocity2 + velocity3) / 3;

  Serial.print("  Cm distance : ");   //print to make sure things are working during testing
  Serial.print(newDistance);
  Serial.print("  speed:");
  Serial.print(abs(instantMPH), 2);
  Serial.print(" mph");
  Serial.println();

  //now use the accelerometer to see if I'm walking
  sensors_event_t event;
  mma.getEvent(&event);
  float zAccel = event.acceleration.z ; //this is z axis, vertical acceleration value
  
  //the difference in acceleration in accel was the cleanest indicator of me walking as my head goes up and down
  avgDelta = abs(zAccel - zAccelOld); // use a floating average of the differences
  avgDelta = avgDelta + abs(zAccelOld - zAccelOlder); // use a floating average of the differences
  avgDelta = 0.5*avgDelta; // use a floating average of the differences
  zAccelOlder = zAccelOld;
  zAccelOld = zAccel;

  bool buzzerFlag = false;
  int mode = 1;

  if( distance1 < 195){
    digitalWrite(LEDpin, LOW);
    if( avgdelta > 0.35){mode = 2;}
    switch(mode){
      case 1:
        if (instantMPH > 3.2 || instantMPH < 0.6){ buzzerFlag = true;}
        break;
      case 2:
        if (instantMPH > 6 || instantMPH < 3){ buzzerFlag = true;}
        break;
      default:
        buzzerFlag = false;
        break;
    }
  } else {
    digitalWrite(LEDpin, HIGH);
    tone(buzzer, 1000);
  }
  delay(50);
}


// This part I didn't really touch yet,
// but I know we talked about it needing improvement - Sam
//==========================================================================
//Get a new reading from the distance sensor
int readLIDAR(void)
{
  int distance = 0;

  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterMeasure); // sets register pointer to  (0x00)
  Wire.write((int)MeasureValue); // sets register pointer to  (0x00)
  Wire.endTransmission(); // stop transmitting

  delay(20); // Wait 20ms for transmit

  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterHighLowB); // sets register pointer to (0x8f)
  Wire.endTransmission(); // stop transmitting

  delay(20); // Wait 20ms for transmit

  Wire.requestFrom((int)LIDARLite_ADDRESS, 2); // request 2 bytes from LIDAR-Lite

  if (Wire.available() >= 2) // if two bytes were received
  {
    distance = Wire.read(); // receive high byte (overwrites previous reading)
    distance = distance << 8; // shift high byte to be high 8 bits
    distance |= Wire.read(); // receive low byte as lower 8 bits
    return (distance);
  }
  else
  {
    Serial.println("Read fail");
    return (0);
  }
}
