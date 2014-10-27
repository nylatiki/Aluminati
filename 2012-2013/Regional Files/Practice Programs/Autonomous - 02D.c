#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C2_1,     LeftBase,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     RightBase,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     Arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Elev,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma fileExtension("rtm")
#pragma platform("NXT")

#include "AdvancedSensors.c"
#include "JoystickDriver.c"

int dist = 200;


typedef enum
{
	sonarNoSensorConnected = 254,
	sonarOutOfRange        = 255
} TSonarErrorCodes;


#pragma platform (NXT, FTC)
#pragma fileExtension("rtm")

task main()
{
	waitForStart();

	while(dist > 65){
		dist = SensorValue[sonar];
		motor[LeftBase] = -100;
		motor[RightBase] = 100;
	}
	motor[LeftBase] = 0;
	motor[RightBase] = 0;
	wait1Msec(100);
}
