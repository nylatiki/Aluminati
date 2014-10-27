#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S3,     IRseekA,        sensorI2CCustom)
#pragma config(Sensor, S4,     IRseekB,        sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     RightBase,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     LeftBase,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     Arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Elev,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//THIS DOES NOT USE SONAR

#define FINAL_INTENSITY 200 //Value between 0 and 255
#define VERTICAL 172
#define SLANTED 230

#include "hitechnic-irseeker-v2.h"

//CONDITIONAL METHODS

int maxSigA, maxSigB = 0;

int getIntensity(){
	int acS1A, acS2A, acS3A, acS4A, acS5A = 0;
	int acS1B, acS2B, acS3B, acS4B, acS5B = 0;
	maxSigA = 0;
	maxSigB = 0;
	int maxSig = 0;
	if (!HTIRS2readAllACStrength(IRseekA, acS1A, acS2A, acS3A, acS4A, acS5A ))
		{
		// error! - write to debug stream and then break.
		writeDebugStreamLine("Read sig ERROR!");
	}
	else{
		maxSigA = (acS1A > acS2A) ? acS1A : acS2A;
		maxSigA = (maxSigA > acS3A) ? maxSigA : acS3A;
		maxSigA = (maxSigA > acS4A) ? maxSigA : acS4A;
		maxSigA = (maxSigA > acS5A) ? maxSigA : acS5A; //sets maxSig to maximum intensity
	}

	if (!HTIRS2readAllACStrength(IRseekB, acS1B, acS2B, acS3B, acS4B, acS5B ))
		{
		// error! - write to debug stream and then break.
		writeDebugStreamLine("Read sig ERROR!");
	}
	else{
		maxSigB = (acS1B > acS2B) ? acS1B : acS2B;
		maxSigB = (maxSigB > acS3B) ? maxSigB : acS3B;
		maxSigB = (maxSigB > acS4B) ? maxSigB : acS4B;
		maxSigB = (maxSigB > acS5B) ? maxSigB : acS5B; //sets maxSig to maximum intensity
	}
	maxSig = (maxSigA > maxSigB)? maxSigA : maxSigB;
	return maxSig; //makes getIntensity() return the highest intensity
}

/******BASE MOVEMENT*******/
void move(int x){
	motor[LeftBase] = x;
	motor[RightBase] = x;
	wait1Msec(50);
}

void stopMotors(){
	motor[LeftBase] = 0;
	motor[RightBase] = 0;
	wait1Msec(50);
}

void moveForward(int sec){
	move(100);
	wait1Msec(sec*1000);
	stopMotors();
	wait1Msec(500);
}

void moveBackward(int sec){
	move(-100);
	wait1Msec(sec*1000);
	stopMotors();
	wait1Msec(100);
}

void pointTurn(float sec, int dir){
		motor[LeftBase] = 100*dir; //+1 is right turn
		motor[RightBase] = -100*dir;
		wait1Msec(sec*1000);
		stopMotors();
		wait1Msec(100);
}

void turnRight(int angle){
	float time = (angle * 0.0091);
		pointTurn(time, 1);
}

void turnLeft(int angle){
	float time = (angle * 0.0091);
	pointTurn(time, -1);
}

//INITIALIZE
//void initializeRobot(){
	nMotorEncoder[Elev] = 0;
	turnRight(45);

	/**********RAISE THE ELEVATOR*******/

	/*nMotorEncoder[Elev] = 0; //hopefully zeroes encoder
	nMotorEncoderTarget[Elev] = 500;//Adjust Target
	motor[Elev] = -100;
	while (nMotorRunState[Elev] != runStateIdle){
    // Waits for motors to stop before continuing.
  }
  motor[Elev] = 0;
	wait1Msec(50);*/

	//Raise the Arm
	motor[Arm] = 50;
	wait1Msec(450); //Time is variable******ADJUST
	motor[Arm] = 20; //Adjust the power to keep it constant
	wait1Msec(50);

	//ADJUST SERVO
	servo[servo1] = VERTICAL;
}

/*******************************MAIN PROGRAM*******************/

	int IRZone = 0;
	int dirA = 0;
	int dirB = 0;
	bool hasRing = true;
//	int k = 65; //need to adjust for turning, is turning constant*****ADJUST
	int intensity = getIntensity();


task main()
{

	int a, b, c, d, e;
	initializeRobot(); //moves robot into initial position

	tHTIRS2DSPMode _mode = DSP_1200;

	if (HTIRS2setDSPMode(IRseekA, _mode))
	{
		// unsuccessful at setting the mode.
		// display error message.
		eraseDisplay();
		nxtDisplayCenteredTextLine(0, "ERROR!");
		nxtDisplayCenteredTextLine(2, "Init failed!");
		nxtDisplayCenteredTextLine(3, "Connect sensor");
		nxtDisplayCenteredTextLine(4, "to Port 3.");
		// make a noise to get their attention.
		PlaySound(soundBeepBeep);
		// wait so user can read message, then leave main task.
		wait10Msec(300);
		return;
	}
	eraseDisplay();

	if (HTIRS2setDSPMode(IRseekB, _mode) == 0)
	{
		// unsuccessful at setting the mode.
		// display error message.
		eraseDisplay();
		nxtDisplayCenteredTextLine(0, "ERROR!");
		nxtDisplayCenteredTextLine(2, "Init failed!");
		nxtDisplayCenteredTextLine(3, "Connect sensor");
		nxtDisplayCenteredTextLine(4, "to Port 4.");
		// make a noise to get their attention.
		PlaySound(soundBeepBeep);
		// wait so user can read message, then leave main task.
		wait10Msec(300);
		return;
	}
	eraseDisplay();



	while(!HTIRS2readAllACStrength(IRseekA, a, b, c, d, e)){ //moves until IR finds beacon location
		move(100);
	}
	stopMotors();
	moveForward(1);

	while(hasRing){

		dirA = HTIRS2readACDir(IRseekA);
		dirB = HTIRS2readACDir(IRseekB);
		IRZone = 10 - dirA - dirB;
		intensity = getIntensity();

		nxtDisplayCenteredTextLine(1, "DirA=%d", dirA);
		nxtDisplayCenteredTextLine(2, "SigA=%d", maxSigA);
		nxtDisplayCenteredTextLine(3, "DirB=%d", dirB);
		nxtDisplayCenteredTextLine(4, "SigB=%d", maxSigB);
		nxtDisplayCenteredTextLine(5, "Val=%d", IRZone);

		motor[LeftBase] = 20 + (IRZone * 4);
		motor[RightBase] = 20 -(IRZone * 4);

		if (intensity >= FINAL_INTENSITY){
			stopMotors();
			/*motor[Arm] = 50;
			wait1Msec(1000);*/


			/*servo[servo1] = VERTICAL; //MOVES SERVO
			wait1Msec(5000);
			servo[servo1] = SLANTED;
			wait1Msec(400);*/

			/*//MOVES ELEVATOR DOWN SLIGHTLY
			nMotorEncoderTarget[Elev] = 3000;//Adjust Target
			motor[Elev] = -100;
			while (nMotorRunState[Elev] != runStateIdle){
		    // Waits for motors to stop before continuing.
		  }
		  motor[Elev] = 0;
			wait1Msec(50);*/

			//MOVES OUT OF THE WAY AND LOWERS THE ARM
			motor[Arm] = -25;
			wait1Msec(3750);
			motor[Arm] = 10;
			moveBackward(2);


			/*//MOVE ELEVATOR BACK DOWN TO 0
			nMotorEncoderTarget[Elev] = 100; //Adjust Target
			motor[Elev] = -100;
			while (nMotorRunState[Elev] != runStateIdle){
		    // Waits for motors to stop before continuing.
		  }
		  motor[Elev] = 0;
			wait1Msec(50);*/

			turnRight(180); //Turns 180 degrees
			hasRing = false;
		}

		wait1Msec(50);

	}

}
