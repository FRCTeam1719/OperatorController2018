#ifndef TB6612_FADER
#define TB6612_FADER

#include <Arduino.h>

//used in some functions so you don't have to send a speed
#define DEFAULTSPEED 255 

class Motor{
	public:
		Motor(int InPin1, int InPin2, int PWMPin, int offset);
		
		void move(int speed);
		void brake();
	private:
		int In1, In2, PWM, Offset;
		
		void fwd(int speed);
		void rev(int speed);

};
#endif