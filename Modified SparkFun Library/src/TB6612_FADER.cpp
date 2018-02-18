#include "TB6612_FADER.h"
#include <Arduino.h>

Motor::Motor(int In1pin, int In2pin, int PWMpin, int offset)
{
  In1 = In1pin;
  In2 = In2pin;
  PWM = PWMpin;
  Offset = offset;
  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(PWM, OUTPUT);
}
void Motor::move(int speed)
{
  speed = speed * Offset;
  if (speed>=0) fwd(speed);
  else rev(-speed);
}
void Motor::fwd(int speed)
{
   digitalWrite(In1, HIGH);
   digitalWrite(In2, LOW);
   analogWrite(PWM, speed);

}
void Motor::rev(int speed)
{
   digitalWrite(In1, LOW);
   digitalWrite(In2, HIGH);
   analogWrite(PWM, speed);
}
void Motor::brake()
{
   digitalWrite(In1, HIGH);
   digitalWrite(In2, HIGH);
   analogWrite(PWM,0);
}