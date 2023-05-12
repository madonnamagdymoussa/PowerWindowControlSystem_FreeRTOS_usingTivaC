/*
 * InfraredSensor.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Dell
 */

#ifndef INFRAREDSENSOR_H_
#define INFRAREDSENSOR_H_

#include "GPIO_config.h"

#define InfraredSensorInputPin (Channel_7)
#define InfraredSensorPort     (PortA)

extern GPIO_ConfigurePin_t InfraredSensorPin;
void InitializeInfraredSensorInputPin(void);

void InfraredSensor_DisableInterrupt(void);
void InfraredSensor_EnableInterrupt(void);
u8_t InfraredSensor_ReadState(void);
#endif /* INFRAREDSENSOR_H_ */
