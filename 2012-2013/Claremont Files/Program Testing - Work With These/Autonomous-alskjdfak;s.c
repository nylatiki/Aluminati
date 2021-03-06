#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     CMotor,        tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     AMotor,        tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_1,    ArmServo,             tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    ClawServo,            tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*******************************PLEASE WORK WITH THESE VALUES**********************************************/

#define rotationCount -1200													//how much it will rotate, may have to test + and -
#define powerPercentage 50												//how much power to rotate at




//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an Tetrix robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  nMotorEncoder[AMotor] = 0;  //resets the motor encoder

  nMotorEncoderTarget[AMotor] = -rotationCount; //set the target stopping position

  motor[AMotor] = - powerPercentage; //sets motor to power at powerPercentage

  while (nMotorRunState[AMotor] != runStateIdle) //while the encoder wheel turns
  {
    //waits for the motor to stop
  }

  motor[AMotor] = 0; //turns the motor



  wait1Msec(1000);

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


void moveServo(int sec, int power){
	servo[ArmServo] = 117 + power;
	wait1Msec(sec*1000);
	servo[ArmServo] = 117;
}

void throttle(){
	motor[motorD] = -100;
	motor[motorE] = -100;
	wait1Msec(500);
	return;
}

void spin360(){
	motor[motorD] = 100;
  motor[motorE] = -100;
  wait1Msec(500);
  return;

}


task main()
{


  waitForStart(); // Wait for the beginning of autonomous phase.

	initializeRobot();

	throttle();

	spin360();


/**************************************MAIN CODE - DO NOT TOUCH*********************************************/



}
