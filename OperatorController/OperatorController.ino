#include <TB6612_FADER.h>

#include <CapacitiveSensor.h>

#include <Joystick.h>


CapacitiveSensor   cs_4_2 = CapacitiveSensor(0, 1); // 11 is sensor pin
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
const int flip = 1;


#define AIN1 11
#define AIN2 12
#define PWMA 13

Motor motor1 = Motor(AIN1, AIN2, PWMA, flip);

int In1 = 11;
int In2 = 12;
int PWM = 13;


int faderMax;
int faderMin;
int softFader = 0;
int lastValue = 0;

int TOUCH_THRESHOLD = 75;
int BUFFER = 10;

const int button1 = 2;
const int button2 = 4;
const int button3 = 6;
const int button4 = 8;
const int button5 = 10;
const int button6 = 9;

const int led1 = 3;
const int led2 = 5;
const int led3 = 7;
const int led4 = 9;
const int led5 = 11;
const int led6 = 13;
int light = 255;

void setup() {
  // put your setup code here, to run once:
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
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
    int currentButtonState = !digitalRead(index * 2 + button1);
    if (currentButtonState != lastButtonState[index]) {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
      digitalWrite(index * 2 + button1 + 1, -currentButtonState);

    }
  }
  long total =  cs_4_2.capacitiveSensor(1);
  Serial.print(total);                  // print sensor output 1
  Serial.print("\n");



  Joystick.setButton(6, LOW);

  if (Serial.available() < 0) {
    if (total > TOUCH_THRESHOLD) {
      Joystick.setButton(6, HIGH);
      Serial.print("GO!");
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

      motor1.brake();
    } else {
      //Move untill we are close enough with a small buffer for overshoot compensation.
      if (analogRead(potPin) < softFader - BUFFER) {

        motor1.move(255);
      } else if (analogRead(potPin) > softFader + BUFFER) {
        motor1.move(-255);
      } else {
        motor1.brake();
      }
    }





    // put your main code here, to run repeatedly:
  }


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


void drive(int speed) {

}

