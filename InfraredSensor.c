#include "lstd.h"
#include "InfraredSensor.h"
#include "GPIO.h"
#include "GPIO_config.h"
#include "NVIC.h"
#include "GPTM.h"
#include "GPTM_config.h"
u8_t ObstacleDetected_Flag=0;

GPIO_ConfigurePin_t InfraredSensorPin={
    PortA,
    Channel_7
};


/*function name: InitializeInfraredSensorInputPin
Input Parameter: void
Output Parameter: void
function description: this function used to initialize the infrared sensor pin
by configuring its pin as input pin and configuring the interrupt source to be on the falling edge*/
void InitializeInfraredSensorInputPin(void){
    GPIO_ConfigureInputPin(&InfraredSensorPin);
    GPIO_ConfigureInterruptSource(FallingEdge,InfraredSensorPin.PortNumIndexArr,  InfraredSensorPin.ConfigureChannelNum );
}



void InfraredSensor_DisableInterrupt(void){
	NVIC_Clear_Interrupt(0);
}

void InfraredSensor_EnableInterrupt(void){
	NVIC_Enable_Interrupt(0);
}

/*function name: InfraredSensor_ReadState
Input parameter: void
OutPut parameter: variable of type unsigned char 
function description: the function uses the bitband bits to check 
if the obstacle is detected or not, the input pin is pull up so if there is a falling edge 
then there will be an obstacle and the return of the function will be one. 
*/
u8_t InfraredSensor_ReadState(void){

  if(0 == GPIO_ReadBitBandBits(InfraredSensorPin.ConfigureChannelNum, InfraredSensorPin.PortNumIndexArr)  ){
		GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 100, milli_Sec);
		 if(0 == GPIO_ReadBitBandBits(InfraredSensorPin.ConfigureChannelNum, InfraredSensorPin.PortNumIndexArr) ){
    ObstacleDetected_Flag=1;
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 70, milli_Sec);
		}
  }

  else{
    ObstacleDetected_Flag=0;
   }

  return ObstacleDetected_Flag;

}

