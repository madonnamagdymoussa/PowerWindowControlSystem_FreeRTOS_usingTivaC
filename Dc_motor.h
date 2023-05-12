/*
 * Dc_motor.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Dell
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "lstd.h"

void DcMotor_TurnOn_clockWise(u8_t MotorID);
void DcMotor_TurnOn_AnticlockWise(u8_t MotorID);

void DcMotor_TurnOff(void);
void DcMotor_Initialization(void);
void DcMotorDriver_TurnOff(void);
void DcMotorPassenger_TurnOff(void);
#define MotorNum (2)
#define MotorPins (2)

#define MotorID_1 (0)
#define MotorID_2  (1)
#endif /* DC_MOTOR_H_ */
