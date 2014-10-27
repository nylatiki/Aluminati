#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C2_1,     LeftBase,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     RightBase,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     Arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     elev,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "hitechnic-irseeker-v2.h"
#define TIME_INTERVAL  10


#define SINGLE_BOUND_WHEEL(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!//
#define SINGLE_DEADBAND_WHEEL(x) ((abs(x) >= 10)? x: 0)

void single_main_wheel( int joy_x, int joy_y )
{
	 float k=-1;
	 int drivePower, turnPower;

   joy_y = k*joy_y;
   drivePower = SINGLE_DEADBAND_WHEEL(joy_x);
   turnPower  = SINGLE_DEADBAND_WHEEL(joy_y);

   motor[LeftBase] = SINGLE_BOUND_WHEEL(drivePower + turnPower);
   motor[RightBase] = SINGLE_BOUND_WHEEL(drivePower - turnPower);
}


/*int getIntensity(){
	int acS1A, acS2A, acS3A, acS4A, acS5A = 0;
	int acS1B, acS2B, acS3B, acS4B, acS5B = 0;
	int maxSigA = 0;
	int maxSigB = 0;
	int maxSig = 0;
	if(HTIRS2readAllACStrength(IRSeekA, acS1A, acS2A, acS3A, acS4A, acS5A)){
		maxSigA = (acS1A > acS2A) ? acS1A : acS2A;
		maxSigA = (maxSigA > acS3A) ? maxSigA : acS3A;
		maxSigA = (maxSigA > acS4A) ? maxSigA : acS4A;
		maxSigA = (maxSigA > acS5A) ? maxSigA : acS5A; //sets maxSig to maximum intensity
	}
	if(HTIRS2readAllACStrength(IRSeekB, acS1B, acS2B, acS3B, acS4B, acS5B)){
		maxSigB = (acS1B > acS2B) ? acS1B : acS2B;
		maxSigB = (maxSigB > acS3B) ? maxSigB : acS3B;
		maxSigB = (maxSigB > acS4B) ? maxSigB : acS4B;
		maxSigB = (maxSigB > acS5B) ? maxSigB : acS5B; //sets maxSig to maximum intensity
	}
	maxSig = (maxSigA > maxSigB)? maxSigA : maxSigB;
	return maxSig; //makes getIntensity() return the highest intensity
}*/


//	int SeekerValueA = SensorValue[IRSeekA];
//	int SeekerValueB = SensorValue[IRSeekB];
//	int intensity = getIntensity();

#define BOUND_WHEEL(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_WHEEL(x) ((abs(x) >= 25)? x: 0)


void right_side( int joy_y )
{
	 float k=1;
	 int drivePower;

   drivePower = DEADBAND_WHEEL(joy_y);
	 drivePower = drivePower*k;
   motor[RightBase] = BOUND_WHEEL(drivePower);
}

#define BOUND_WHEEL_2(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_WHEEL_2(x) ((abs(x) >= 25)? x: 0)

void left_side( int joy_y2 )
{
	 float k=1;
	 int drivePower;

   drivePower = DEADBAND_WHEEL(joy_y2);
	 drivePower = drivePower*k;
   motor[LeftBase] = BOUND_WHEEL(drivePower);
}

#define SLOW_BOUND_WHEEL(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define SLOW_DEADBAND_WHEEL(x) ((abs(x) >= 25)? x: 0)

void slow_right_side( int joy_y3 )
{
	 float k=3;
	 int drivePower;

   drivePower = SLOW_DEADBAND_WHEEL(joy_y3);
   drivePower = drivePower/k;
   motor[RightBase] = SLOW_BOUND_WHEEL(drivePower);
 }

#define SLOW_BOUND_WHEEL_2(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define SLOW_DEADBAND_WHEEL_2(x) ((abs(x) >= 25)? x: 0)

void slow_left_side( int joy_y4 )
{
	 float k=3;
	 int drivePower;

   drivePower = SLOW_DEADBAND_WHEEL_2(joy_y4);
   drivePower = drivePower/k;
   motor[LeftBase] = SLOW_BOUND_WHEEL_2(drivePower);
}


//#define BOUND_WHEEL(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!//
//#define DEADBAND_WHEEL(x) ((abs(x) >= 25)? x: 0)

void main_wheel( int joy_x, int joy_y )
{
	 float k=-4;
	 int drivePower, turnPower;

   joy_y = k*joy_y;
   drivePower = DEADBAND_WHEEL(joy_x);
   turnPower  = DEADBAND_WHEEL(joy_y);

   motor[LeftBase] = BOUND_WHEEL(drivePower + turnPower);
   motor[RightBase] = BOUND_WHEEL(drivePower - turnPower);
}


//#define BOUND_WHEEL_2(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!//
//#define DEADBAND_WHEEL_2(x) ((abs(x) >= 10)? x: 0)

void main_wheel_slow( int joy_m, int joy_n )
{
	 float k=6;
	 int drivePower, turnPower;

   joy_n = joy_n/k;
   joy_m = joy_m/k;
   drivePower = DEADBAND_WHEEL(joy_m);
   turnPower  = DEADBAND_WHEEL(joy_n);

   motor[LeftBase] = BOUND_WHEEL(drivePower + turnPower);
   motor[RightBase] = BOUND_WHEEL(drivePower - turnPower);
}

//-----  ARM LIFT ----
#define BOUND_ARM(x) (((x) > 50)? 60: ((x) < -50)? -15: (x)) //Makes sure that the joystick is between -100 and 100 (limits big)
#define DEADBAND_ARM(x) ((abs(x) >= 4)? x: 0) //limits sensitivity (small)

void lift(int joy_k)
{
	float k = 1 ;
	int drivePower = DEADBAND_ARM(joy_k/k);
	motor[Arm] = BOUND_ARM(drivePower);
}

//----- ARM ELEV ----
#define BOUND_ELEV(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_ELEV(x) ((abs(x) >= 10)? x: 0)
#define MOTION_LIMIT  11000
void elevMove(int joy_k)
{
	int k = 1;
	int drivePower = DEADBAND_ELEV(joy_k);
	drivePower = drivePower * k;

  if ( drivePower < 0 && nMotorEncoder[elev] >= MOTION_LIMIT )
		motor[elev] = 0;
  else
  if (drivePower > 0 && nMotorEncoder[elev] <= 0)
  	motor[elev] = 0;
	else
		motor[elev] = BOUND_ELEV(drivePower);
}

void elevMoveFree(int joy_k)
{
	int k;
	k = -1;
	int drivePower = DEADBAND_ELEV(joy_k);
	drivePower = drivePower * k;
	motor[elev] = BOUND_ELEV(drivePower);
}


#define MOTION_STEP		360*2
void elevUpDown( int btn_n, int btn_m )
{
	if ( nMotorRunState[elev] != runStateIdle  )
		return;

	if ( btn_n == 1 )
	{
		motor[elev] = 0;
		nMotorEncoderTarget[elev]=MOTION_STEP;
		motor[elev] = 10;
	}
  else
  if ( btn_m == 1 )
	{
		motor[elev] = 0;
		nMotorEncoderTarget[elev]=-MOTION_STEP;
		motor[elev] = -10;
	}
}

void resetElevEncoder(int btn_k)
{
	if ( btn_k == 1 )
  {
  	nxtDisplayTextLine(2, "Elev:%d",nMotorEncoder[elev]);
		nMotorEncoder[elev] = 0;
		motor[elev] = 0; //stop it
	}
}

//----- ARM SERVO -----
#define BOUND_SERVO(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_SERVO(x) ((abs(x) >= 50)? x: 0)
int servo_angle = 0;
void servoAngle(int btn_x)
{
	int angle;
	angle = servo_angle;
	if(btn_x == 1)
	{
		servo[servo1] = angle;
	}
}
#define BOUND_SERVO_1(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_SERVO_1(x) ((abs(x) >= 50)? x: 0)
int servo_initial = 138;
void servoInitial(int btn_y)
{
	int initial;
	initial = servo_initial;
	if (btn_y == 1)
	{
		servo[servo1] = initial;
	}
}
#define BOUND_SERVO_2(x) (((x) > 100)? 100: ((x) < -100)? -100: (x)) //*!!Makes sure that the joystick is between -100 and 100 !!*//
#define DEADBAND_SERVO_2(x) ((abs(x) >= 50)? x: 0)
int servo_drop = 250;
void servoDrop(int btn_z)
{
	int drop;
	drop = servo_drop;
	if (btn_z == 1)
	{
		servo[servo1] = drop;
	}
}

//-------Motor Encoder thing----
void displayMessage(int btn_k)
{
	if ( btn_k == 1 )
		nxtDisplayTextLine(2, "Elev:%d",nMotorEncoder[elev]);
}

void initializeRobot()
{
	nMotorEncoder[elev] = 0;
}



task main()
{

	/*tHTIRS2DSPMode _mode = DSP_1200;
	// attempt to set to DSP mode.
	if (HTIRS2setDSPMode(IRSeekA, _mode) == 0)
	{
		// unsuccessful at setting the mode.
		// display error message.
		eraseDisplay();
		nxtDisplayCenteredTextLine(0, "ERROR!");
		nxtDisplayCenteredTextLine(2, "Init failed!");
		nxtDisplayCenteredTextLine(3, "Connect sensor");
		nxtDisplayCenteredTextLine(4, "to Port 1.");
		// make a noise to get their attention.
		PlaySound(soundBeepBeep);
		// wait so user can read message, then leave main task.
		wait10Msec(300);
		return;
	}
	eraseDisplay();*/
	initializeRobot();
	while(true)
	{
		getJoystickSettings(joystick);

		/*if (joy1Btn(8) == 1)
		{
			slow_right_side(joystick.joy1_y1);
			slow_left_side(joystick.joy1_y2);
		}
		else
		{
			right_side(joystick.joy1_y1);
			left_side(joystick.joy1_y2);
		}
		*/
		single_main_wheel(joystick.joy1_x2, joystick.joy1_y2);
		main_wheel(joystick.joy1_x1, joystick.joy1_y1);

		//while ( joy1Btn(7) == 1 )
			//main_wheel_slow(joystick.joy1_x2, joystick.joy1_y2);

		lift(joystick.joy2_y1);

		if ( joy2Btn(8)== 1 )
			elevMoveFree(joystick.joy2_y2);
	  else
	  {
			elevMove(joystick.joy2_y2);
			resetElevEncoder(joy2Btn(3));
			displayMessage(joy2Btn(1));
	  }
		servoInitial(joy2Btn(2));
		servoAngle (joy2Btn(4));
		while ( joy2Btn(7) == 1 )
			servoDrop(joy2Btn(4));
		//int SeekerValueA = SensorValue[IRSeekA];
		//int SeekerValueB = SensorValue[IRSeekB];

		wait1Msec(TIME_INTERVAL);
	}

}
