#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Motor,  mtr_S1_C1_1,     RightBase,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     Elev,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     LeftBase,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Arm,           tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

#define MOTORBOUND(X) (X)*(100/127)
#define DEADZONE(X) ((abs(X) <10)? 0: X)

void moveBase(int x, int y){
	x = DEADZONE(x);
	y = DEADZONE(y);
	//int rightPower = DEADZONE(joystick.joy1_x1 + joystick.joy1_y1);
	motor[RightBase] = MOTORBOUND(DEADZONE(x) + DEADZONE(y));
	motor[LeftBase] = MOTORBOUND(DEADZONE(y) - DEADZONE(x));
}

void lift(){
	motor[Elev] = MOTORBOUND(DEADZONE(joystick.joy2_y1));
}

void para(){
	motor[Arm] = MOTORBOUND(DEADZONE(joystick.joy2_y2));
}

task main()
{

	waitForStart();
	while(true){
		getJoystickSettings(joystick);
		moveBase(joystick.joy1_x1, joystick.joy1_y1);
		lift();
		para();

	}
}
