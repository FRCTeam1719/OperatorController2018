#include <CapacitiveSensor.h>

#include <Joystick.h>

CapacitiveSensor touch = CapacitiveSensor(0, 1);
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  1, 0
  false, false, true,
  false, false, false,
  false, false,
  false, false, false);

const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;
const int button5 = 6;
const int button6 = 7;
void setup() {
  // put your setup code here, to run once:
  pinMode(button1, INPUT_PULLUP);

  Joystick.begin();
  Joystick.setZAxisRange(-1, 1);
}

int lastButtonState[6] = {0,0,0,0,0,0};

void loop() {
  // put your main code here, to run repeatedly:
  for (index = 0; index < 6; index ++) {
    int currentButtonState !=digitalRead(index + button1);
    if(currentButtonState != lastButtonState[index]);
    switch (index){
    case 0:
      if(currentButtonState == 1){

      }
    }
  }
  }
  
}
