#include <TB6612_FADER.h>
const int potPin = 0;
int potVal = 0;
const int faderSpeedPin = 3;
const int faderDirectionPin = 4;
const int flip = -1;
#define AIN1 11
#define AIN2 12
#define PWMA 13
Motor motor1 = Motor(AIN1, AIN2, PWMA, flip);
int In1 = 11;
int In2 = 12;
int PWM = 13;
int BUFFER = 30;

unsigned int faderMax;
unsigned int faderMin;
unsigned int softFader = 0;
int lastValue = 0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("test");
  calibrateFader();
}
unsigned int integerValue = 0; // Max value is 65535
char incomingByte;
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {   // something came across serial
    integerValue = 0;      // throw away previous integerValue
    while (1) {       // force into a loop until 'n' is received
      incomingByte = Serial.read();
      if (incomingByte == '\n') break;   // exit the while(1), we're done receiving
      if (incomingByte == -1) continue;  // if no characters are in the buffer read() returns -1
      integerValue *= 10;  // shift left 1 decimal place
      // convert ASCII to integer, add, and shift left 1 decimal place
      integerValue = ((incomingByte - 48) + integerValue);
    }
    Serial.println(integerValue);   // Do something with the value
    Serial.println(analogRead(potPin));
    softFader = integerValue;
    

  }
  Serial.println("SF: " + softFader);
  if (softFader > faderMax) {
      softFader = faderMax;
    }
    if (softFader < faderMin) {
      softFader = faderMin;
    }
    //Move untill we are close enough with a small buffer for overshoot compensation.
    if (analogRead(potPin) < softFader - BUFFER) {

      motor1.move(255);
    } else if (analogRead(potPin) > softFader + BUFFER) {
      motor1.move(-255);
    } else {
      motor1.brake();
    }
}
void updateFader( int softFader ) {
  if (softFader > faderMax) {
    softFader = faderMax;
  }
  if (softFader < faderMin) {
    softFader = faderMin;
  }
  //Move untill we are close enough with a small buffer for overshoot compensation.
  if (analogRead(potPin) < softFader - BUFFER) {

    motor1.move(255);
  } else if (analogRead(potPin) > softFader + BUFFER) {
    motor1.move(-255);
  } else {
    motor1.brake();
  }
}

void calibrateFader() {
  //Ride fader to top, bottom and set limits.
  motor1.move(255);

  delay(250);
  faderMin = analogRead(0);
  motor1.move(-255);
  delay(250);
  faderMax = analogRead(0);
  motor1.brake();
}
