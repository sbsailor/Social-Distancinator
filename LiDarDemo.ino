#include <LIDARLite.h>
#include <LIDARLite_v3HP.h>
#include <LIDARLite_v4LED.h>

/*------------------------------------------------------------------------------

  LIDARLite Arduino Library
  v3/GetDistancePwm

  This example shows how to read distance from a LIDAR-Lite connected over the
  PWM interface.

  Connections:
  LIDAR-Lite 5 Vdc (red) to Arduino 5v
  LIDAR-Lite Ground (black) to Arduino GND
  LIDAR-Lite Mode control (yellow) to Arduino digital input (pin 11)
  LIDAR-Lite Mode control (yellow) to 1 kOhm resistor lead 1
  1 kOhm resistor lead 2 to Arduino digital output (pin 2)

  (Capacitor recommended to mitigate inrush current when device is enabled)
  680uF capacitor (+) to Arduino 5v
  680uF capacitor (-) to Arduino GND

  See the Operation Manual for wiring diagrams and more information:
  http://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf

------------------------------------------------------------------------------*/

unsigned long pulseWidth,distance,distance1,velocity,distance2,deltax;

void setup()
{
  Serial.begin(115200); // Start serial communications

  pinMode(2, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(2, LOW); // Set trigger LOW for continuous read
  pinMode(11, INPUT); // Set pin 11 as monitor pin
  distance1 = 0;
}

void loop()
{
  pulseWidth = pulseIn(11, HIGH); // Count how long the pulse is high in microseconds
    distance = pulseWidth/10; // 10usec = 1 cm of distance - this conversion is from Garmins provided code
    Serial.print("Distance: ");
    Serial.println(distance); // Print the distance
    distance2 = distance;
    deltax = distance2-distance1;
    deltax = abs(deltax);
    velocity = deltax/.1; //divide change in distance by the delay time
  if (velocity > 1000) velocity = 0; //I got some crazy high velocity spikes, and wanted to ignore them
  Serial.print("Velocity: ");
   Serial.println(velocity);
    distance1=distance;
    delay(100);
  
}
