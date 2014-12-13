#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S2,     bigBall,        sensorLightActive)
#pragma config(Sensor, S3,     smallBall,      sensorLightActive)
#pragma config(Sensor, S4,     ultrasonic,     sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     FLWheelMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     BLWheelMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     BRWheelMotor,  tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     FRWheelMotor,  tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     shooterMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     armMotor,      tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    bigGate,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    leftHook,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    rightRamp,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    leftRamp,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    smallGate,            tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

#define DEADBAND(x) ((abs(x) >= 10)? x: 0)

int motorScale(float x)
{
	x = ((x / 128) * 100);
	if (x > 100)
		x = 100;
	return x;
}

void drive(int x, int y, int r)
{
	float k = 1.0;
	float kR = 1.0;

	int xPower, yPower, rPower, FLPower, BLPower, BRPower, FRPower;

	xPower = k 	* motorScale(DEADBAND(x));
	yPower = k 	* motorScale(DEADBAND(y));
	rPower = kR	* motorScale(DEADBAND(r));

	FLPower = motorScale(		xPower	+	yPower	+	rPower);
	BLPower = motorScale( -	xPower 	+	yPower	+	rPower);
	BRPower = motorScale(		xPower	+	yPower	-	rPower);
	FRPower = motorScale( -	xPower	+	yPower	-	rPower);

	motor[FLWheelMotor] = FLPower;
	motor[BLWheelMotor] = BLPower;
	motor[BRWheelMotor] = BRPower;
	motor[FRWheelMotor] = FRPower;
}

void moveArm(int x, int y)
{
	motor[armMotor] = 50 * (x - y);
}


void servo_up (int btn_x)
{
	int hookUpRight = 150;	// smaller value is more up
	int hookUp = 250 - hookUpRight;

	if (btn_x == 1)
	{
		servo[leftHook] = hookUp;
		servo[rightHook] = hookUpRight;
	}
}

void servo_down (int btn_x)
{
	int HookDownRight = 245; // greater value is more down
	int HookDown = 253 - HookDownRight;

	if (btn_x == 1)
	{
		servo[leftHook] = HookDown;
		servo[rightHook] = HookDownRight;
	}
}

void shootOne()
{
	motor[shooterMotor] = 100;
	wait1Msec(1350);
	motor[shooterMotor] = 0;

}

task main()
{
	while (true)
	{
		getJoystickSettings(joystick);
		drive(joystick.joy1_x1, joystick.joy1_y1, joystick.joy1_x2); // normal drive

		moveArm(joy1Btn(6), joy1Btn(5));

		servo_up(joy1Btn(4)); //raise hook
		servo_down(joy1Btn(1)); //lower hook

		if (joy2Btn(8))
			shootOne();
	}
}
