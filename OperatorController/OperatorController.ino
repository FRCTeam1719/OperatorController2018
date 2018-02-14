#include <CapacitiveSensor.h>

#include <Joystick.h>

CapacitiveSensor touch = CapacitiveSensor(0, 1); // 1 is sensor pin
Joystick_ Joystick(0x03,JOYSTICK_TYPE_JOYSTICK, //ID of HID device, type of joystick,
  7, 0, //Button count, Hat switch count,
  false, false, true, //has X axis, has Y axis, has Z axis,
  false, false, false, // has rotational X axis, has rotational Y axis, has rotational Z axis,
  false, false, //has rudder, has throttle,
  false, false, false); //hass accelerator, has break, has steering.

const int potPin = 2;
int potVal = 0;
const int faderSpeedPin = 3;
const int faderDirectionPin = 4;

int faderMax;
int faderMin;
int softFader = 0;
int lastValue = 0;

int TOUCH_THRESHOLD = 2000;

const int button1 = 1;
const int button2 = 2;
const int button3 = 3;
const int button4 = 4;
const int button5 = 5;
const int button6 = 6;

const int led1 = 7;
const int led2 = 8;
const int led3 = 9;
const int led4 = 10;
const int led5 = 11;
const int led6 = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);
  
  pinMode(led1, OUTPUT);
  Joystick.begin();
}

int lastButtonState[6] = {0,0,0,0,0,0};
void loop() {
  if(Serial.available()){
    char t[2];
    Serial.readBytesUntil('\n', t, 2);
    softFader = atoi(t);
  
  }
  // put your main code here, to run repeatedly:
  for (int index = 0; index < 6; index ++) {
    int currentButtonState = !digitalRead(index + button1);
    if(currentButtonState != lastButtonState[index]){
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
  }
  }
  if(touch.capacitiveSensor(30) > TOUCH_THRESHOLD){
    Joystick.setButton(7, true);
  }else{
    Joystick.setButton(7, false);
  }

  
  Joystick.setZAxis(analogRead(potPin));
  delay(50);
  }


void calibrateFader(){

  analogWrite(faderSpeedPin, 255);
  digitalWrite(faderDirectionPin, HIGH);

  delay(250);
  faderMax = analogRead(potPin);
  digitalWrite(faderDirectionPin, LOW);
  delay(250);
  faderMin = analogRead(0);

  analogWrite(faderSpeedPin, 0);
}

