

#include "GPIO_config.h"
#include "GPIO.h"
#include "GPTM.h"
#include "GPTM_config.h"
#include "lstd.h"
#include "NVIC.h"
/**********************************AutomaticSwitch***************************************/
static GPIO_ConfigurePin_t AutoSwitch1={
     PortC,
     Channel_4
};

static GPIO_ConfigurePin_t AutoSwitch2={
     PortC,
     Channel_5
};

static GPIO_ConfigurePin_t AutoSwitch3={
     PortC,
     Channel_6
};

static GPIO_ConfigurePin_t AutoSwitch4={
     PortC,
     Channel_7
};
/**********************************AutomaticSwitch***************************************/


static GPIO_ConfigurePin_t ON_OFF_Switch={
     PortE,
     Channel_5
};

static GPIO_ConfigurePin_t Manual1Switch={
     PortA,
     Channel_2
};

static GPIO_ConfigurePin_t Manual2Switch={
     PortA,
     Channel_3
};


static GPIO_ConfigurePin_t Manual3Switch={
     PortA,
     Channel_4
};

static GPIO_ConfigurePin_t Manual4Switch={
     PortA,
     Channel_5
};

/**********************************LimitSwitch***************************************/
static GPIO_ConfigurePin_t Limit1Switch={
     PortD,
     Channel_6
};

static GPIO_ConfigurePin_t Limit2Switch={
     PortE,
     Channel_3
};

/**********************************Array of pointer to struct ***************************************/
 static GPIO_ConfigurePin_t * GPIO_ConfigManuelSwitch[4]={
	&Manual1Switch,
	&Manual2Switch,
	&Manual3Switch,
	&Manual4Switch
};


static GPIO_ConfigurePin_t* GPIO_ConfigAutoSwitch[4]={
	&AutoSwitch1,
	&AutoSwitch2,
	&AutoSwitch3,
	&AutoSwitch4
};

 GPIO_ConfigurePin_t* GPIO_ConfigLimitSwitch[2]={
	&Limit1Switch,
	&Limit2Switch
};

u8_t AutoSwitchPressed_FlagArr[4]={0,0,0,0};
u8_t  ManualSwitchPressed_FlagArr[4]={0,0,0,0};
u8_t ON_OFFSwitch_PressedFlag=0;
u8_t LimitSwitch_PressedFlagArr[2]={0,0};

void Switch_Initialization(){

  GPIO_ConfigureInputPin(&AutoSwitch1);
	GPIO_ConfigureInputPin(&AutoSwitch2);
	GPIO_ConfigureInputPin(&AutoSwitch3);
	GPIO_ConfigureInputPin(&AutoSwitch4);
	
	GPIO_ConfigureInputPin(&Manual1Switch);
	GPIO_ConfigureInputPin(&Manual2Switch);
	GPIO_ConfigureInputPin(&Manual3Switch);
	GPIO_ConfigureInputPin(&Manual4Switch);
	
	GPIO_ConfigureInputPin(&Limit1Switch);
	GPIO_ConfigureInputPin(&Limit2Switch);
	GPIO_ConfigureInterruptSource(FallingEdge,GPIO_ConfigLimitSwitch[0]->PortNumIndexArr,  GPIO_ConfigLimitSwitch[0]->ConfigureChannelNum );
	GPIO_ConfigureInterruptSource(FallingEdge,GPIO_ConfigLimitSwitch[1]->PortNumIndexArr,  GPIO_ConfigLimitSwitch[1]->ConfigureChannelNum );

	
	GPIO_ConfigureInputPin(&ON_OFF_Switch);
	
	GPTM_InitializeDelayMode(GPIO_TimerAFSELConfig_ArrPtrStruct[0], GPTM_Config_ArrPtrStruct[0]);
}


/*Function Name: AutoSwitch_ReadInputState 

  Input Parameters: The function takes the switch variable ID as an input 
  and that variable will be the index of the array of structure 

  Output Parameters: the function returns a value of type unsigned char if
                     the switch is pressed then the output variable will be 1
fnuction description: the function uses the bitbands bits and check 
the input state of the pull up pin if  it have a falling edge then 
it returns 1 if there is a falling edge which means that the switch is presssed 
is */
u8_t AutoSwitch_ReadInputState(u8_t AutoSwitchID){

    /**********************Check for button 1**********************/
        if( 0 == GPIO_ReadBitBandBits(GPIO_ConfigAutoSwitch[AutoSwitchID]->ConfigureChannelNum ,GPIO_ConfigAutoSwitch[AutoSwitchID]->PortNumIndexArr) ){

             GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 300, milli_Sec);

                 if(0 == GPIO_ReadBitBandBits(GPIO_ConfigAutoSwitch[AutoSwitchID]->ConfigureChannelNum, GPIO_ConfigAutoSwitch[AutoSwitchID]->PortNumIndexArr) ){
                     AutoSwitchPressed_FlagArr[AutoSwitchID]=1;
                 GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 75, milli_Sec);
             }

        }

        else{
            AutoSwitchPressed_FlagArr[AutoSwitchID]=0;
        }

  return AutoSwitchPressed_FlagArr[AutoSwitchID];
}


/*Function Name: ManuelSwitch_ReadInputState 

  Input Parameters: The function takes the switch variable ID as an input 
  and that variable will be the index of the array of structure 

  Output Parameters: the function returns a value of type unsigned char if
                     the switch is pressed then the output variable will be 1
fnuction description: the function uses the bitbands bits and check 
the input state of the pull up pin if  it have a falling edge then 
it returns 1 if there is a falling edge which means that the switch is presssed 
 */

u8_t ManuelSwitch_ReadInputState(u8_t SwitchID){

    /**********************Check for button 1**********************/
	        if( 0 == GPIO_ReadBitBandBits(GPIO_ConfigManuelSwitch[SwitchID]->ConfigureChannelNum, GPIO_ConfigManuelSwitch[SwitchID]->PortNumIndexArr)  ){

             GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 50, milli_Sec);

                 if(0 == GPIO_ReadBitBandBits(GPIO_ConfigManuelSwitch[SwitchID]->ConfigureChannelNum, GPIO_ConfigManuelSwitch[SwitchID]->PortNumIndexArr)  ){
                     ManualSwitchPressed_FlagArr[SwitchID]=1;
                  GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 10, milli_Sec);
             }

        }

        else{
            ManualSwitchPressed_FlagArr[SwitchID]=0;
        }

  return ManualSwitchPressed_FlagArr[SwitchID];
}


/*Function Name: LimitSwitch_ReadInputState 

  Input Parameters: The function takes the switch variable ID as an input 
  and that variable will be the index of the array of structure 

  Output Parameters: the function returns a value of type unsigned char if
                     the switch is pressed then the output variable will be 1
fnuction description: the function uses the bitbands bits and check 
the input state of the pull up pin if  it have a falling edge then 
it returns 1 if there is a falling edge which means that the switch is presssed 
 */
u8_t LimitSwitch_ReadInputState(u8_t SwitchID){

  if( 0 == GPIO_ReadBitBandBits(GPIO_ConfigLimitSwitch[SwitchID]->ConfigureChannelNum, GPIO_ConfigLimitSwitch[SwitchID]->PortNumIndexArr)  ){

     GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 30, milli_Sec);

       if(0 == GPIO_ReadBitBandBits(GPIO_ConfigLimitSwitch[SwitchID]->ConfigureChannelNum, GPIO_ConfigLimitSwitch[SwitchID]->PortNumIndexArr)  ){
           LimitSwitch_PressedFlagArr[SwitchID]=1;
           GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 10, milli_Sec);
        }

    }

        else{
            LimitSwitch_PressedFlagArr[SwitchID]=0;
        }

  return LimitSwitch_PressedFlagArr[SwitchID];
}

/*Function Name: ON_OFFSwitch_ReadInputState 

  Input Parameters: void 

  Output Parameters: the function returns a value of type unsigned char if
                     the switch is pressed then the output variable will be 1
fnuction description: the function uses the bitbands bits and check 
the input state of the pull up pin if  it have a falling edge that means the switch is pressed */

u8_t ON_OFFSwitch_ReadInputState(){
	
	        if( 0 == GPIO_ReadBitBandBits(ON_OFF_Switch.ConfigureChannelNum, ON_OFF_Switch.PortNumIndexArr)  ){

             GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 5, milli_Sec);

                 if(0 == GPIO_ReadBitBandBits(ON_OFF_Switch.ConfigureChannelNum, ON_OFF_Switch.PortNumIndexArr)  ){
                     ON_OFFSwitch_PressedFlag=1;
                  GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 2, milli_Sec);
             }

        }

        else{
            ON_OFFSwitch_PressedFlag=0;
        }

  return ON_OFFSwitch_PressedFlag;

}

void LimitSwitch1_DisableInterrupt(void){
	NVIC_Clear_Interrupt(3);
}

void LimitSwitch2_DisableInterrupt(void){
	NVIC_Clear_Interrupt(4);
}

void LimitSwitch1_EnableInterrupt(void){
	NVIC_Enable_Interrupt(3);
}

void LimitSwitch2_EnableInterrupt(void){
	NVIC_Enable_Interrupt(4);
}

void LimitSwitch1_EXTIClearInterrupt(void){
 GPIO_EXTIClearInterrupt(GPIO_ConfigLimitSwitch[0]->PortNumIndexArr, GPIO_ConfigLimitSwitch[0]->ConfigureChannelNum);

}

void LimitSwitch2_EXTIClearInterrupt(void){
	 GPIO_EXTIClearInterrupt(GPIO_ConfigLimitSwitch[1]->PortNumIndexArr, GPIO_ConfigLimitSwitch[1]->ConfigureChannelNum);

}