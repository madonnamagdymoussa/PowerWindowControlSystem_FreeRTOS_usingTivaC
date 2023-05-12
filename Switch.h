/*
 * Switch.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Dell
 */

#ifndef SWITCH_H_
#define SWITCH_H_
#include "GPIO.h"
#include  "lstd.h"

#define ManualSwitchNum (4)
#define ManualSwitch1 (0)
#define ManualSwitch2 (1)
#define ManualSwitch3 (2)
#define ManualSwitch4 (3)

#define AutoSwitch1 (0)
#define AutoSwitch2 (1)
#define AutoSwitch3 (2)
#define AutoSwitch4 (4)


#define LimitSwitch1 (0)
#define LimitSwitch2 (1)
void Switch_Initialization();
u8_t ManuelSwitch_ReadInputState(u8_t SwitchID);
u8_t AutoSwitch_ReadInputState(u8_t AutoSwitchID);
u8_t ON_OFFSwitch_ReadInputState();
u8_t LimitSwitch_ReadInputState(u8_t SwitchID);

void LimitSwitch1_DisableInterrupt(void);
void LimitSwitch2_DisableInterrupt(void);
void LimitSwitch1_EnableInterrupt(void);
void LimitSwitch2_EnableInterrupt(void);
void LimitSwitch1_EXTIClearInterrupt(void);
void LimitSwitch2_EXTIClearInterrupt(void);
#define SwitchIsPressed  (1) 


extern GPIO_ConfigurePin_t* GPIO_ConfigLimitSwitch[2];
#endif /* SWITCH_H_ */
