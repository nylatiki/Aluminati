#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     winch,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorLeft,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     flag,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
#pragma config(SrvoPosition,  Position02,            128, 128, 128, 128, 128, 128, 128, 128)
#pragma config(SrvoPosition,  Position01,            112,  38, 128, 128, 128, 128, 128, 128)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#define TIME_INTERVAL  5

#define SINGLE_BOUND_WHEEL(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!//
#define SINGLE_DEADBAND_WHEEL(x) ((abs(x) >= 10)? x: 0)

void single_main_wheel( int joy_x, int joy_y )
{
	 float k = .35;
	 int drivePower, turnPower;

   drivePower = - SINGLE_DEADBAND_WHEEL(k * joy_x);
   turnPower  = SINGLE_DEADBAND_WHEEL(joy_y);

   motor[motorLeft] = SINGLE_BOUND_WHEEL(drivePower - turnPower);
   motor[motorRight] = SINGLE_BOUND_WHEEL(drivePower + turnPower);
}

void single_main_wheel_fast( int joy_x, int joy_y )
{
	 float k = 1;
	 int drivePower, turnPower;

   drivePower = - SINGLE_DEADBAND_WHEEL(k * joy_x);
   turnPower  = SINGLE_DEADBAND_WHEEL(joy_y);

   motor[motorLeft] = SINGLE_BOUND_WHEEL(drivePower - turnPower);
   motor[motorRight] = SINGLE_BOUND_WHEEL(drivePower + turnPower);
}

//-----  ARM LIFT ----
#define BOUND_ARM(x) (((x) > 100)? 100: ((x) < -50)? -30: (x)) //Makes sure that the joystick is between -100 and 100 (limits big)
#define DEADBAND_ARM(x) ((abs(x) >= 4)? x: 0) //limits sensitivity (small)

void lift(int joy_k)
{
	float k = - .30 ;
	float k2 = -.05;
	int drivePower = DEADBAND_ARM(k * joy_k);
	int drivePowerDown = DEADBAND_ARM(k2 * joy_k);
	if (joy_k > 0)
	  motor[arm] = BOUND_ARM(drivePower);
	else
	  motor[arm] = BOUND_ARM(drivePowerDown);
}

//----- WINCH ----
#define BOUND_WINCH(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_WINCH(x) ((abs(x) >= 10)? x: 0)

void winchmove(int joy_k)
{
	int k = -1;
	int drivePower = DEADBAND_WINCH(joy_k);
	drivePower = drivePower * k;
	motor[winch] = BOUND_WINCH(drivePower);
}

void winchmoveOneWay(int joy_k)	// only moves forward
{
	int k;
	k = -1;
	int drivePower = DEADBAND_WINCH(joy_k);
	if (drivePower < 0)
		drivePower = 0;
	drivePower = drivePower * k;
	motor[winch] = BOUND_WINCH(drivePower);
}

//----- ARM SERVO -----
//lower values tilt dustpan up, higher values tilt dustpan down

#define BOUND_SERVO(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_SERVO(x) ((abs(x) >= 50)? x: 0)
int servo_flat = 121; //value  for flat position
void servoFlat(int btn_x)
{
	int flat;   //flat position for servo1 (left)
	int flat2;  //flat position for servo2 (right)
	flat = servo_flat;
	flat2 = 128 - (servo_flat - 128) + 5; //calculates value to be inputted to servo2
	if(btn_x == 1)
	{
		servo[servo1] = flat;
		servo[servo2] = flat2;
	}
}

#define BOUND_SERVO_1(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_SERVO_1(x) ((abs(x) >= 50)? x: 0)
int servo_drop = 255;
void servoDrop(int btn_y)
{
	int drop;   //drop position for servo1
	int drop2;  //drop position for servo2
	drop = servo_drop;
	drop2 = 128 - (servo_drop - 128) + 5; //calculates value to be inputted to servo2
	if (btn_y == 1)
	{
		servo[servo1] = drop;
		servo[servo2] = drop2;
	}
}

#define BOUND_SERVO_2(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_SERVO_2(x) ((abs(x) >= 50)? x: 0)
int servo_raise = 85;
void servoRaise(int btn_z)
{
	int raise;  //raise position for servo1
	int raise2; //raise position for servo2
	raise = servo_raise;
	raise2 = 128 - (servo_raise - 128) + 5; //calculates value to be inputted to servo2
	if (btn_z == 1)
	{
		servo[servo1] = raise;
		servo[servo2] = raise2;
	}
}

#define BOUND_SERVO_3(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_SERVO_3(x) ((abs(x) >= 50)? x: 0)
int servo_angledown = 170;
void servoAngleDown(int btn_w)
{
	int angledown;  //angledown position for servo1
	int angledown2; //angledown position for servo2
	angledown = servo_angledown;
	angledown2 = 128 - (servo_angledown - 128) + 5; //calculates value to be inputted to servo2
	if(btn_w == 1)
	{
		servo[servo1] = angledown;
		servo[servo2] = angledown2;
	}
}

//----- FLAG ----

#define BOUND_FLAG(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_FLAG(x) ((abs(x) >= 10)? x: 0)

void flagmove(int joy_k)
{
	int k;
	k = -1;
	int drivePower = DEADBAND_FLAG(joy_k);
	drivePower = drivePower * k;
	motor[flag] = BOUND_FLAG(drivePower);
}

void initializeRobot()
{
	motor[arm] = - 75;
	wait1Msec(250);
	motor[arm] = 0;

  return;
}

task main()
{
  waitForStart(); // Wait for the beginning of autonomous phase.

  initializeRobot();

	motor[mtr_S1_C2_1] = - 95;
	motor[mtr_S1_C2_2] = - 95;
	wait1Msec(1500);
}
