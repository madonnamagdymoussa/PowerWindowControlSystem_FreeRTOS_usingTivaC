#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>
#include "semphr.h"
#include "GPIO.h"
#include "GPIO_config.h"
#include "UART.h"
#include "UART_config.h"
#include "Button.h"
#include "GPTM.h"
#include "GPTM_config.h"
#include "HC-05.h"
#include "InfraredSensor.h"
#include "lstd.h"
#include "Switch.h"
#include "Dc_motor.h"


/* The priority of the software interrupt.  The interrupt service routine uses
an (interrupt safe) FreeRTOS API function, so the priority of the interrupt must
be equal to or lower than the priority set by
configMAX_SYSCALL_INTERRUPT_PRIORITY - remembering that on the Cortex M3 high
numeric values represent low priority values, which can be confusing as it is
counter intuitive. */
#define mainSOFTWARE_INTERRUPT_PRIORITY 		( 7 )

xTaskHandle ON_OFFSwitchTaskHandle;

static SemaphoreHandle_t xBinarySemaphore;

static SemaphoreHandle_t BinarySemaphoreManualSwitch1;
static SemaphoreHandle_t BinarySemaphoreLimitSwitch1;
static SemaphoreHandle_t BinarySemaphoreLimitSwitch2;
static SemaphoreHandle_t MutexInfraredSensor;
static SemaphoreHandle_t MutexLimitSwitch1;
static SemaphoreHandle_t MutexLimitSwitch2;

static  xQueueHandle AutoSwitch1Queue;
static  xQueueHandle AutoSwitch2Queue;
static  xQueueHandle AutoSwitch3Queue;
static  xQueueHandle AutoSwitch4Queue;
static unsigned long  AutoSwitchQueue_CounterVar;
static u8_t AutoSwitch1Jam_Flag=0;
static u8_t AutoSwitch2Jam_Flag=0;

/******************************Tasks********************************************/
void InfraredSensorHandler(void*pvParameters);
void ContinousCounterTask(void*pvParameters);
void AutoSwitchTask(void*pvParameters);
void OpenWindowAutomatically(void*pvParameters);
void ManualSwitchTask(void*pvParameters);
void OpenWindowManually(void*pvParameters);
void ON_OFFSwitchTask(void *pvParameters);
void LimitSwitch1Handler(void *pvParameters);
void LimitSwitch2Handler(void *pvParameters);
/**************************************************************************/

#define mainSW_INTERRUPT_ID		( ( IRQn_Type ) 0 )
#define mainSW_INTERRUPT_ID_PortD ( ( IRQn_Type ) 3 )
#define mainSW_INTERRUPT_ID_PortE ( ( IRQn_Type ) 4 )

u8_t IRSensor_HC_05[30]={"obstacle detected"};



void IRApplicationCallBackFunc(void){

    GPIO_EXTIClearInterrupt(InfraredSensorPin.PortNumIndexArr, InfraredSensorPin.ConfigureChannelNum);

		portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	  xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );
	    AutoSwitch1Jam_Flag=1;
	    AutoSwitch2Jam_Flag=1;
	   portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );

}

void LimitSwitch1ApplicationCallBack(void){
	LimitSwitch1_EXTIClearInterrupt();
	portBASE_TYPE xHigherPriorityTaskWoken1 = pdFALSE;
	  xSemaphoreGiveFromISR( BinarySemaphoreLimitSwitch1, &xHigherPriorityTaskWoken1 );
	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken1 );
}

void LimitSwitch2ApplicationCallBack(void){
	LimitSwitch2_EXTIClearInterrupt();
		portBASE_TYPE xHigherPriorityTaskWoken2 = pdFALSE;
	  xSemaphoreGiveFromISR( BinarySemaphoreLimitSwitch2, &xHigherPriorityTaskWoken2 );
	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken2 );

}


int main(void)
{
    RegisterCallbackFunction(InfraredSensorPin.PortNumIndexArr ,IRApplicationCallBackFunc);
	  RegisterCallbackFunction(GPIO_ConfigLimitSwitch[0]->PortNumIndexArr,LimitSwitch1ApplicationCallBack);
	  RegisterCallbackFunction(GPIO_ConfigLimitSwitch[1]->PortNumIndexArr,LimitSwitch2ApplicationCallBack);
	
    InitializeInfraredSensorInputPin();
	  Switch_Initialization();
	  DcMotor_Initialization();
	  HC05_Initialization();
	  DcMotor_TurnOff();
	
	  vSemaphoreCreateBinary( xBinarySemaphore );
	   vSemaphoreCreateBinary(BinarySemaphoreManualSwitch1);
	   vSemaphoreCreateBinary(BinarySemaphoreLimitSwitch1);
	  vSemaphoreCreateBinary(BinarySemaphoreLimitSwitch2);
	
	   MutexInfraredSensor=xSemaphoreCreateMutex();
	    MutexLimitSwitch1=xSemaphoreCreateMutex();
	   AutoSwitch1Queue = xQueueCreate( 1, sizeof( unsigned char ) );
	   AutoSwitch2Queue = xQueueCreate( 1, sizeof( unsigned char ) );
	   AutoSwitch3Queue = xQueueCreate( 1, sizeof( unsigned char ) );
	   AutoSwitch4Queue = xQueueCreate( 1, sizeof( unsigned char ) );
		 
     NVIC_SetPriority( mainSW_INTERRUPT_ID, 7 );
		 NVIC_SetPriority( mainSW_INTERRUPT_ID_PortD, 7 );
		 NVIC_SetPriority( mainSW_INTERRUPT_ID_PortE, 7 );
       

  	 xTaskCreate(InfraredSensorHandler, "IR sensorrr",300,NULL,6,NULL);
		 
	   xTaskCreate(AutoSwitchTask, "AutoSwitchhh",300,NULL,2,NULL);
	   xTaskCreate(ManualSwitchTask, "ManuelSwitchhh",200,NULL,2,NULL);
		
	   xTaskCreate(OpenWindowAutomatically, "open Window automatically",300,NULL,3,NULL);
	   xTaskCreate(OpenWindowManually, "open Window manually",200,NULL,3,NULL); 
		
	   xTaskCreate(LimitSwitch1Handler, "limit the motor",200,NULL,5,NULL);
		 xTaskCreate(LimitSwitch2Handler, "limit the motor",200,NULL,5,NULL);
		
		 xTaskCreate(ON_OFFSwitchTask, "on off switch",300,NULL,4,&ON_OFFSwitchTaskHandle);
				
	  vTaskStartScheduler();
    while(1){

    }
}




void ON_OFFSwitchTask(void *pvParameters){
	for(;;){
		
		vTaskDelay(70);
		while(SwitchIsPressed==ON_OFFSwitch_ReadInputState()){
			   DcMotorPassenger_TurnOff();
					HC05_WriteString("ON/OFF switch");
		      HC05_WriteString("\n");
			
			   if(SwitchIsPressed ==  ManuelSwitch_ReadInputState(ManualSwitch1)){
					 xSemaphoreGive(BinarySemaphoreManualSwitch1);
					 vTaskPrioritySet(ON_OFFSwitchTaskHandle,1);
				 }
				 
				  if(SwitchIsPressed ==  ManuelSwitch_ReadInputState(ManualSwitch2)){
					 xSemaphoreGive(BinarySemaphoreManualSwitch1);
					 vTaskPrioritySet(ON_OFFSwitchTaskHandle,1);
				 }
				 
				  if(SwitchIsPressed==AutoSwitch_ReadInputState(AutoSwitch1)){
					 xQueueSendToBack(AutoSwitch1Queue,&AutoSwitchQueue_CounterVar,0);
					 vTaskPrioritySet(ON_OFFSwitchTaskHandle,1);
						GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 30, milli_Sec);
				 }
				 
				 else if(SwitchIsPressed==AutoSwitch_ReadInputState(AutoSwitch2)){
					 xQueueSendToBack(AutoSwitch2Queue,&AutoSwitchQueue_CounterVar,0);
					 vTaskPrioritySet(ON_OFFSwitchTaskHandle,1);
					 GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 30, milli_Sec);
				 }



		}
		
		vTaskDelay(1000);
	}
}



void LimitSwitch1Handler(void *pvParameters){
	
	xSemaphoreTake(BinarySemaphoreLimitSwitch1,0);
	
	for(;;){
		
				xSemaphoreTake(BinarySemaphoreLimitSwitch1,portMAX_DELAY);
		   
		     DcMotorDriver_TurnOff();
		     
		     LimitSwitch1_DisableInterrupt();
				 HC05_WriteString("Limit switch1");
		     HC05_WriteString("\n");
		
		     while(1==LimitSwitch_ReadInputState(LimitSwitch1)){
					 DcMotorDriver_TurnOff();
					
				 }


    		LimitSwitch1_EnableInterrupt();
			
	}
}

void LimitSwitch2Handler(void *pvParameters){
	
	xSemaphoreTake(BinarySemaphoreLimitSwitch2,0);
	
	for(;;){
				xSemaphoreTake(BinarySemaphoreLimitSwitch2,portMAX_DELAY);
		     DcMotorPassenger_TurnOff();
		     LimitSwitch2_DisableInterrupt();
				 HC05_WriteString("Limit switch2");
		     HC05_WriteString("\n");
		
		     while(1==LimitSwitch_ReadInputState(LimitSwitch2)){
					 DcMotorPassenger_TurnOff();
				 }


    		LimitSwitch2_EnableInterrupt();
	}
}


void InfraredSensorHandler(void*pvParameters){
	xSemaphoreTake(xBinarySemaphore,0);
	
	for(;;){
		xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
		InfraredSensor_DisableInterrupt();
		HC05_WriteString(&IRSensor_HC_05[0]);
		HC05_WriteString("\n");
		xSemaphoreTake(MutexInfraredSensor,160000);
		
		
		if(1 == InfraredSensor_ReadState()){
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 500, milli_Sec);
							if(AutoSwitch1Jam_Flag==1){
				HC05_WriteString("jam protection function\n");
				DcMotor_TurnOn_clockWise(MotorID_1);
			  GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 500, milli_Sec);
			  DcMotor_TurnOff();
				AutoSwitch1Jam_Flag=0;
			}
			
			if(AutoSwitch2Jam_Flag==1){
				HC05_WriteString("jam protection function\n");
				DcMotor_TurnOn_clockWise(MotorID_2);
			  GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 500, milli_Sec);
			  DcMotor_TurnOff();
				AutoSwitch2Jam_Flag=0;
			}

		}
		
		while(1 == InfraredSensor_ReadState() ){
		
			if(SwitchIsPressed==AutoSwitch_ReadInputState(AutoSwitch1)){
			HC05_WriteString("autoSwitch 1\n");
			DcMotor_TurnOn_clockWise(MotorID_1);
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 500, milli_Sec);
			DcMotor_TurnOff();
					}
			
			
			
			if(SwitchIsPressed==AutoSwitch_ReadInputState(AutoSwitch2)){
			HC05_WriteString("autoSwitch 2\n");
			DcMotor_TurnOn_AnticlockWise(MotorID_1);
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 400, milli_Sec);
			DcMotor_TurnOff();
					}
			
	
			if(SwitchIsPressed==AutoSwitch_ReadInputState(AutoSwitch3)){
			HC05_WriteString("autoSwitch 3\n");
			DcMotor_TurnOn_clockWise(MotorID_2);
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 400, milli_Sec);
			DcMotor_TurnOff();
					}
			
	
		}
		
		xSemaphoreGive(MutexInfraredSensor);
		InfraredSensor_EnableInterrupt();
	}
}

/************************************Auto Switchhhhh**********************************************/
void AutoSwitchTask(void*pvParameters){
	
	for(;;){
		
		if(SwitchIsPressed==AutoSwitch_ReadInputState(AutoSwitch1)){
			HC05_WriteString("auto switch1 pressed\n");
			AutoSwitchQueue_CounterVar++;
			xQueueSendToBack(AutoSwitch1Queue,&AutoSwitchQueue_CounterVar,0);
			
		}
		
			else if(SwitchIsPressed==AutoSwitch_ReadInputState(AutoSwitch2)){
			HC05_WriteString("auto switch2 pressed\n");
			AutoSwitchQueue_CounterVar++;
			xQueueSendToBack(AutoSwitch2Queue,&AutoSwitchQueue_CounterVar,0);
			
		}
			
				if(SwitchIsPressed==AutoSwitch_ReadInputState(AutoSwitch3)){
			HC05_WriteString("auto switch3 pressed\n");
			AutoSwitchQueue_CounterVar++;
			xQueueSendToBack(AutoSwitch3Queue,&AutoSwitchQueue_CounterVar,0);
			
		}
				
				else if(SwitchIsPressed==AutoSwitch_ReadInputState(AutoSwitch4)){
			HC05_WriteString("auto switch4 pressed\n");
			AutoSwitchQueue_CounterVar++;
			xQueueSendToBack(AutoSwitch4Queue,&AutoSwitchQueue_CounterVar,0);
			
		}



	}
}

void OpenWindowAutomatically (void*pvParameters){
	portBASE_TYPE xStatus1;
	portBASE_TYPE xStatus2;
	portBASE_TYPE xStatus3;
	portBASE_TYPE xStatus4;
	for(;;){
		
		
	 xStatus1 = xQueueReceive( AutoSwitch1Queue, &AutoSwitchQueue_CounterVar, 100 / portTICK_RATE_MS );

		if(xStatus1 == pdPASS)
		{
			HC05_WriteString("Open window automatically switch1\n");
			DcMotor_TurnOn_clockWise(MotorID_1);
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 420, milli_Sec);
			DcMotor_TurnOff();
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 50, milli_Sec);
		}

	 xStatus2 = xQueueReceive( AutoSwitch2Queue, &AutoSwitchQueue_CounterVar, 100 / portTICK_RATE_MS );

				 if(xStatus2 == pdPASS)
		{
			HC05_WriteString("close window automatically switch2\n");
			DcMotor_TurnOn_AnticlockWise(MotorID_1);
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 420, milli_Sec);
			DcMotor_TurnOff();
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 50, milli_Sec);
		}

		
		xStatus3 = xQueueReceive( AutoSwitch3Queue, &AutoSwitchQueue_CounterVar, 100 / portTICK_RATE_MS );
		if(xStatus3 == pdPASS)
		{
			HC05_WriteString("Open window automatically switch3\n");
			DcMotor_TurnOn_clockWise(MotorID_2);
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 500, milli_Sec);
			DcMotor_TurnOff();
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 50, milli_Sec);
		}

				xStatus4 = xQueueReceive( AutoSwitch4Queue, &AutoSwitchQueue_CounterVar, 100 / portTICK_RATE_MS );
		if(xStatus4 == pdPASS)
		{
			HC05_WriteString("close window automatically switch4\n");
			DcMotor_TurnOn_AnticlockWise(MotorID_2);
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 420, milli_Sec);
			DcMotor_TurnOff();
			GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 50, milli_Sec);
		}


		vTaskPrioritySet(ON_OFFSwitchTaskHandle,4);
	}
}
/**********************************************************************************/

/*******************************************Manuel Switchhhh****************************************************/
void ManualSwitchTask(void * pvParameters){
	
	for(;;){
		
xSemaphoreTake(MutexInfraredSensor,160000);
		
		 DcMotor_TurnOff();
		if(SwitchIsPressed ==  ManuelSwitch_ReadInputState(ManualSwitch1)){
			HC05_WriteString("Manual Switch 1 Pressed\n");
			xSemaphoreGive(BinarySemaphoreManualSwitch1);
		}
		
		if(SwitchIsPressed ==  ManuelSwitch_ReadInputState(ManualSwitch2)){
			HC05_WriteString("Manual Switch 2 Pressed\n");
			xSemaphoreGive(BinarySemaphoreManualSwitch1);
		}
		
		if(SwitchIsPressed ==  ManuelSwitch_ReadInputState(ManualSwitch3)){
			HC05_WriteString("Manual Switch 3 Pressed\n");
			xSemaphoreGive(BinarySemaphoreManualSwitch1);
		}

		if(SwitchIsPressed ==  ManuelSwitch_ReadInputState(ManualSwitch4)){
			HC05_WriteString("Manual Switch 4 Pressed\n");
			xSemaphoreGive(BinarySemaphoreManualSwitch1);
		}

xSemaphoreGive(MutexInfraredSensor);
		
	}
}

void OpenWindowManually(void*pvParameters){
	
	xSemaphoreTake(BinarySemaphoreManualSwitch1,0);
	
	for(;;){
		
		
		xSemaphoreTake(BinarySemaphoreManualSwitch1,160000);
		while(SwitchIsPressed == ManuelSwitch_ReadInputState(ManualSwitch1)){
			DcMotor_TurnOn_clockWise(MotorID_1);
		}
		DcMotor_TurnOff();
		
			
		while(SwitchIsPressed == ManuelSwitch_ReadInputState(ManualSwitch2)){
			DcMotor_TurnOn_AnticlockWise( MotorID_1 );
		}
		DcMotor_TurnOff();
		
		
		while(SwitchIsPressed == ManuelSwitch_ReadInputState(ManualSwitch3)){
			DcMotor_TurnOn_clockWise(MotorID_2);
		}
		DcMotor_TurnOff();
		
		
		while(SwitchIsPressed == ManuelSwitch_ReadInputState(ManualSwitch4)){
			DcMotor_TurnOn_AnticlockWise(MotorID_2);
		}
		DcMotor_TurnOff();
    vTaskPrioritySet(ON_OFFSwitchTaskHandle,4);


	}
}
/***************************************************************************************************************/
