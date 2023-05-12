#include "GPTM_config.h"
#include "GPIO.h"
#include "GPIO_config.h"
#include "lstd.h"
#include "GPTM.h"

	  u8_t Button1_PressedFlag=0;
    u8_t Button2_PressedFlag=0;


void ReadButtonState(void){

        /**********************Check for button 1**********************/
            if( 0 == GPIO_ReadBitBandBits(Channel_4,PortF) ){

                 GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 170, milli_Sec);

                     if(0 == GPIO_ReadBitBandBits(Channel_4,PortF) ){
                     Button1_PressedFlag=1;
                     GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 50, milli_Sec);
                 }

            }

            else{
                Button1_PressedFlag=0;
            }

            /**********************Check for button 2**********************/
            if( 0 == GPIO_ReadBitBandBits(Channel_0,PortF) ){

                 GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 150, milli_Sec);


                 if(0 == GPIO_ReadBitBandBits(Channel_0,PortF) ){
                     Button2_PressedFlag=1;

                     GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 50, milli_Sec);
                 }

             }
            else{
                 Button2_PressedFlag=0;
             }

            GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 50, milli_Sec);
}



void ButtonInitializations(void){
	
	  GPIO_ConfigureInputPin(&GPIO_ConfigurePin_PF0);
	  GPIO_ConfigureInputPin(&GPIO_ConfigurePin_PF4);
	
    GPTM_InitializeDelayMode(GPIO_TimerAFSELConfig_ArrPtrStruct[0], GPTM_Config_ArrPtrStruct[0]);
    GPTM_InitializeDelayMode(GPIO_TimerAFSELConfig_ArrPtrStruct[1], GPTM_Config_ArrPtrStruct[2]);

		/*GPIO_ConfigureOutputPin(&GPIO_ConfigurePin_PF1);
	  GPIO_ConfigureOutputPin(&GPIO_ConfigurePin_PF2);
	  GPIO_ConfigureOutputPin(&GPIO_ConfigurePin_PF3);*/

}

