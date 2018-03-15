#include <TB6612_FADER.h>

#include <CapacitiveSensor.h>

#include <Joystick.h>

CapacitiveSensor cs_4_2 = CapacitiveSensor(0, 1); // 1 is sensor pin
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
const int flip = -1;

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

int TOUCH_THRESHOLD = 90;
int BUFFER = 35;

const int button1 = 9;
const int button2 = 10;
const int button3 = 4;
const int button4 = 2;
const int button5 = 6;
const int button6 = 8;

const int led1 = 4;
const int led5 = 6;
const int led6 = 7;

int currentButtonState;

int light = 255;

int b0, b1;

const byte numChars = 32;
char receivedChars[numChars];

boolean newData = false;

void setup() {
  // put your setup code here, to run once:
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  calibrateFader();
  Serial.begin(9600);
  /*while (!Serial)
      ;*/
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

int lastButtonState[6] = { 0, 0, 0, 0, 0, 0 };
void loop() {
  for (int index = 0; index < 6; index++) {
    switch (index) {
      case 0:
        currentButtonState = !digitalRead(button1);
        if (currentButtonState != lastButtonState[0]) {
          Joystick.setButton(2, currentButtonState);
          lastButtonState[0] = currentButtonState;
          break;
        }
      case 1:
        currentButtonState = !digitalRead(button2);
        if (currentButtonState != lastButtonState[1]) {
          Joystick.setButton(4, currentButtonState);
          lastButtonState[1] = currentButtonState;
        }
        break;
      case 2:
        currentButtonState = !digitalRead(button3);
        if (currentButtonState != lastButtonState[2]) {
          Joystick.setButton(2, currentButtonState);
          lastButtonState[2] = currentButtonState;
        }
        break;
      case 3:
        currentButtonState = !digitalRead(button4);
        if (currentButtonState != lastButtonState[3]) {
          Joystick.setButton(1, currentButtonState);
          lastButtonState[3] = currentButtonState;
        }
      case 4:
        currentButtonState = !digitalRead(button5);
        if (currentButtonState != lastButtonState[4]) {
          Joystick.setButton(3, currentButtonState);
          lastButtonState[4] = currentButtonState;
        }
        break;
      case 5:
        currentButtonState = !digitalRead(button6);
        if (currentButtonState != lastButtonState[5]) {
          Joystick.setButton(5, currentButtonState);
          lastButtonState[5] = currentButtonState;
        }
        break;
        //digitalWrite(index * 2 + button1 + 1, -currentButtonState);
    }
  }

  long total = cs_4_2.capacitiveSensor(3);
  //Serial.print(total);                  // print sensor output 1
  //Serial.print("\n");
  if (Serial.available() > 1) {
    /* Hack -- we use the high bit to check byte order,
       effectively using 7-bit bytes of data.

       This does not matter, as we only use 0 to 1024 anyway,
       so it's 2 bytes either way */

    softFader = Serial.parseInt();
    recvWithStartEndMarkers();
    softFader = atoi(receivedChars)
    Serial.read();
    Serial.flush();


    //Move untill we are close enough with a small buffer for overshoot compensation.
    if (analogRead(potPin) < softFader - BUFFER) {

      motor1.move(255);
    } else if (analogRead(potPin) > softFader + BUFFER) {
      motor1.move(-255);
    } else {
      motor1.brake();
    }
  }
  if (total > TOUCH_THRESHOLD) {
    Joystick.setButton(6, HIGH);
    //Serial.print("GO!");

    motor1.brake();
  } else {
    Joystick.setButton(6, LOW);
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

  Joystick.setZAxis(analogRead(potPin));
  delay(10);    //Serial delay to make it work nice
}

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  // if (Serial.available() > 0) {
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}



void calibrateFader() {
  //Ride fader to top, bottom and set limits.
  motor1.move(-255);
  delay(250);
  faderMin = analogRead(0);
  motor1.move(255);
  delay(250);
  faderMax = analogRead(0);
  motor1.brake();
}
