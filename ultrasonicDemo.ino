const int trigPin1 = 13;
const int echoPin1 = 12;
const int trigPin2 = 11;
const int echoPin2 = 10;
const int trigPin3 = 9;
const int echoPin3 = 8;
const int trigPin4 = 7;
const int echoPin4 = 6;
const int trigPin5 = 4;
const int echoPin5 = 3;
const int LEDpin = 2;
const int buzzer = 5;

float duration1, duration2,duration3,duration4,duration5;
float pingdistance1, pingdistance2,pingdistance3, pingdistance4,pingdistance5;
float oldping1, oldping2, oldping3, oldping4, oldping5;
float alarm ,deltaping1, deltaping2, deltaping3, deltaping4, deltaping5;

void setup() {
  Serial.begin (9600); 
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(trigPin5, OUTPUT);
  pinMode(echoPin5, INPUT);

  pinMode(LEDpin, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);     //manufacturere and everbody on the internet uses this delay to 'reset' the sensor
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);    // this is how lng the pulse lasts
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH, 17500);  //17500 is the timeout in microseconds, about 300 cm
  pingdistance1 = (duration1*.0343)/2;   //this gives distance in cm, based on speed of sound
    if (pingdistance1 > 500) pingdistance1 = 500; //occacionally it gets a random reading of 2000
    if (pingdistance1 < 0.001) pingdistance1 = 500; //occasionally it randomly reads 0, it's a cheap sensor
deltaping1 = pingdistance1 - oldping1;
oldping1 = pingdistance1;

    delayMicroseconds(10);      //all the codes i found online use this delay to pevent interference
                                //i don't think it contributes significantly to my refresh issue
    digitalWrite(trigPin2, LOW);
      delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
   duration2 = pulseIn(echoPin2, HIGH, 17500);
  pingdistance2 = (duration2*.0343)/2;
    if (pingdistance2 > 500) pingdistance2 = 500;
      if (pingdistance2 < 0.001) pingdistance2 = 500; 
deltaping2 = pingdistance2 - oldping2;
oldping2 = pingdistance2;
  delayMicroseconds(10);
 
    digitalWrite(trigPin3, LOW);
      delayMicroseconds(2);
    digitalWrite(trigPin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
   duration3 = pulseIn(echoPin3, HIGH,17500);
  pingdistance3 = (duration3*.0343)/2;
    if (pingdistance3 > 500) pingdistance3 = 500;
      if (pingdistance3 < 0.001) pingdistance3 = 500; 
deltaping3 = pingdistance3 - oldping3;
oldping3 = pingdistance3;
    delayMicroseconds(10);
 
    digitalWrite(trigPin4, LOW);
      delayMicroseconds(2);
    digitalWrite(trigPin4, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin4, LOW);
   duration4 = pulseIn(echoPin4, HIGH, 17500);
  pingdistance4 = (duration4*.0343)/2;
    if (pingdistance4 > 500) pingdistance4 = 500;
      if (pingdistance4 < 0.001) pingdistance4 = 500; 
deltaping4 = pingdistance4 - oldping4;
oldping4 = pingdistance4;
    delayMicroseconds(10);
 
    digitalWrite(trigPin5, LOW);
      delayMicroseconds(2);
    digitalWrite(trigPin5, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin5, LOW);
   duration5 = pulseIn(echoPin5, HIGH, 17500);
  pingdistance5 = (duration5*.0343)/2;
    if (pingdistance5 > 500) pingdistance5 = 500;
      if (pingdistance5 < 0.001) pingdistance5 = 500; 
deltaping5 = pingdistance5 - oldping5;
oldping5 = pingdistance5;

Serial.print(deltaping1);
Serial.print("  ");
Serial.print(deltaping2);
Serial.print("  ");
Serial.print(deltaping3);
Serial.print("  ");
Serial.print(deltaping4);
Serial.print("  ");
Serial.print(deltaping5);

alarm = 0;

if (deltaping1 < -7 && deltaping1 > -15 && pingdistance1 < 195) 
{alarm = alarm +1;
}
if (deltaping2 < -7 && deltaping2 > -15 && pingdistance2 < 195) 
{alarm = alarm +1;
}
if (deltaping3 < -7 && deltaping3 > -15 && pingdistance3 < 195) 
{alarm = alarm +1;
}
if (deltaping4 < -7 && deltaping4 > -15 && pingdistance4 < 195) 
{alarm = alarm +1;
}
if (deltaping5 < -7 && deltaping5 > -15 && pingdistance5 < 195) 
{alarm = alarm +1;
}

if (alarm >0)
{ digitalWrite(LEDpin,HIGH);
    tone(buzzer, 1000);
}
else {
   digitalWrite(LEDpin, LOW);
    noTone(buzzer);
}

Serial.println(); 
  delay(100);
   
}
