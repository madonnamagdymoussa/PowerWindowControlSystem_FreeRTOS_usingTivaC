

#include "Dc_motor.h"
#include "GPIO_config.h"
#include "GPIO.h"

GPIO_ConfigurePin_t DcMotorHbridgeIN1GPIO_Config={
     PortB,
     Channel_6
};


GPIO_ConfigurePin_t DcMotorHbridgeIN2GPIO_Config={
     PortB,
     Channel_7
};

GPIO_ConfigurePin_t DcMotorHbridgeIN3GPIO_Config={
     PortB,
     Channel_4
};

GPIO_ConfigurePin_t DcMotorHbridgeIN4GPIO_Config={
     PortB,
     Channel_5
};



GPIO_ConfigurePin_t * ConfigurePin_MotorPins[MotorNum][MotorPins]={
	{&DcMotorHbridgeIN1GPIO_Config,
	 &DcMotorHbridgeIN2GPIO_Config
	},
	{
		&DcMotorHbridgeIN3GPIO_Config,
		&DcMotorHbridgeIN4GPIO_Config
	}
	
};

/*function name: DcMotor_TurnOn_clockWise
  Input Parameters: variable of type unsigned int that variable will be the index of the array
  output parameters: void 
  function description: used to turn the motor clockwise by using the bitband bits 
  to make one of the pins high and the other low  
  */
void DcMotor_TurnOn_clockWise(u8_t MotorID){
GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID][0]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID][0]->PortNumIndexArr, OutputHigh);
GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID][1]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID][1]->PortNumIndexArr, OutputLow);

}


/*function name: DcMotor_TurnOn_AnticlockWise
  Input Parameters: variable of type unsigned int that variable will be the index of the array
  output parameters: void 
  function description: used to turn the motor anti-clockwise by using the bitband bits 
  to make one of the pins high and the other low  
  */
void DcMotor_TurnOn_AnticlockWise(u8_t MotorID){
GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID][0]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID][0]->PortNumIndexArr, OutputLow);
GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID][1]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID][1]->PortNumIndexArr, OutputHigh);

}

/*function name: DcMotor_TurnOff
Input Parameters: void 
output parameters: void 
function description: that function used to set certain bitband bits to a low to disable the motor*/
void DcMotor_TurnOff(void){
    GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID_1][0]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID_1][0]->PortNumIndexArr, OutputLow);
	  GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID_1][1]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID_1][1]->PortNumIndexArr, OutputLow);
    GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID_2][0]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID_2][0]->PortNumIndexArr, OutputLow);
	  GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID_2][1]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID_2][1]->PortNumIndexArr, OutputLow);
}


/*function name: DcMotor_Initialization
Input parameters: void
output parameters: void
function description: used to configure the gpio pins of the motors as output pins*/
void DcMotor_Initialization(void){
   GPIO_ConfigureOutputPin(&DcMotorHbridgeIN1GPIO_Config);
   GPIO_ConfigureOutputPin(&DcMotorHbridgeIN2GPIO_Config);
	
	 GPIO_ConfigureOutputPin(&DcMotorHbridgeIN3GPIO_Config);
   GPIO_ConfigureOutputPin(&DcMotorHbridgeIN4GPIO_Config);
}

/*function name: DcMotorDriver_TurnOff
input parameter: void
output parameter: void
function description: that function uses the bitband bits to turn the two pins of 
motor id 1 to low*/
void DcMotorDriver_TurnOff(void){
GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID_1][0]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID_1][0]->PortNumIndexArr, OutputLow);
GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID_1][1]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID_1][1]->PortNumIndexArr, OutputLow);
}


/*function name: DcMotorPassenger_TurnOff
input parameter: void
output parameter: void
function description: that function uses the bitband bits to turn the two pins of 
motor id 1 to low*/
void DcMotorPassenger_TurnOff(void){
GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID_2][0]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID_2][0]->PortNumIndexArr, OutputLow);
GPIO_WriteBitBandBits(ConfigurePin_MotorPins[MotorID_2][1]->ConfigureChannelNum, ConfigurePin_MotorPins[MotorID_2][1]->PortNumIndexArr, OutputLow);
}