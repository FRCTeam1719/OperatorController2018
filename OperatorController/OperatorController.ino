
#include <CapacitiveSensor.h>

#include <Joystick.h>


CapacitiveSensor touch = CapacitiveSensor(0, 13); // 1 is sensor pin
Joystick_ Joystick(0x03, JOYSTICK_TYPE_JOYSTICK, //ID of HID device, type of joystick,
                   7, 0, //Button count, Hat switch count,
                   false, false, true, //has X axis, has Y axis, has Z axis,
                   false, false, false, // has rotational X axis, has rotational Y axis, has rotational Z axis,
                   false, false, //has rudder, has throttle,
                   false, false, false); //hass accelerator, has break, has steering.

const int potPin = 0;
int potVal = 0;
const int faderSpeedPin = 3;
const int faderDirectionPin = 4;

#define AIN1 5
#define AIN2 6
#define PWMA 7

int In1 = 5;
int In2 = 6;
int PWM = 7;


int faderMax;
int faderMin;
int softFader = 0;
int lastValue = 0;

int TOUCH_THRESHOLD = 2000;
int BUFFER = 10;

const int button1 = 0;
const int button2 = 1;
const int button3 = 2;
const int button4 = 3;
const int button5 = 4;
const int button6 = 5;

const int led1 = 8;
const int led2 = 9;
const int led3 = 10;
const int led4 = 11;
const int led5 = 12;
const int led6 = 13;
int light = 255;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(led1, OUTPUT);
  Joystick.begin();
}

int lastButtonState[6] = {0, 0, 0, 0, 0, 0};
void loop() {
  for (int index = 0; index < 6; index ++) {
    int currentButtonState = !digitalRead(index + button1);
    if (currentButtonState != lastButtonState[index]) {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
      //digitalWrite(led1, currentButtonState);

    }
  }

  if (Serial.available() < 0) {
    char t[2];
    Serial.readBytesUntil('\n', t, 2);
    softFader = atoi(t);

    //Cap the values before moving
    if (softFader > faderMax) {
      softFader = faderMax;
    }
    if (softFader < faderMin) {
      softFader = faderMin;
    }


    //Move untill we are close enough with a small buffer for overshoot compensation.
    if (analogRead(potPin) < softFader - BUFFER) {
      while (analogRead(potPin) < softFader - BUFFER) {
        digitalWrite(faderDirectionPin, HIGH);
        analogWrite(faderSpeedPin, 255);
      }
      analogWrite(faderSpeedPin, 0);
    } else {
      while (analogRead(potPin) > softFader + BUFFER) {
        digitalWrite(faderDirectionPin, LOW);
        analogWrite(faderSpeedPin, 255);
      }
      analogWrite(faderSpeedPin, 0);
    }





    // put your main code here, to run repeatedly:
   digitalWrite(led1, LOW);
  }
  else{
    digitalWrite(led1, HIGH);
  }/*
  }
  if(touch.capacitiveSensor(30) > TOUCH_THRESHOLD){
    Joystick.setButton(7, true);
  }else{
    Joystick.setButton(7, false);
  }
*/

  Joystick.setZAxis(analogRead(potPin));
  delay(10); //Serial delay to make it work nice
}


void calibrateFader() {
  //Ride fader to top, bottom and set limits.
  analogWrite(faderSpeedPin, 255);
  digitalWrite(faderDirectionPin, HIGH);

  delay(250);
  faderMax = analogRead(potPin);
  digitalWrite(faderDirectionPin, LOW);
  delay(250);
  faderMin = analogRead(0);

  analogWrite(faderSpeedPin, 0);
}
class 
void drive(int speed){
  
}

