#include "UART.h"
#include "UART_config.h"
#include "lstd.h"
#include <stdio.h>


void static Convert_IntTo_Char(int IntegerNum,  char *pt_CharOutputArray){
	
	u8_t indexOutputArray=0;
	sprintf(pt_CharOutputArray,"%d",IntegerNum);
		
}

void HC05_Initialization(void){

 UART_Initialization(&UARTChannel1_Config, GPIO_AFSELUARTConfig_ArrPtrStruct[1]);

}

void HC05_ReadChar(u8_t *CharacterRead){

    UART_RecieveChar_Polling(UART_Channel1, CharacterRead);
}


void HC05_WriteChar(u8_t *pTxBuffer){
 UART_TransmitChar_Polling(UART_Channel1, pTxBuffer);

}

void HC05_WriteString(u8_t*PtString ){
	while(*PtString ){
		HC05_WriteChar(PtString++);
	}
}
void HC05_WriteNumber(int IntegerNum ){

	unsigned char x;
	u8_t indexnum=0;
	char OutputArray[20];
	Convert_IntTo_Char( IntegerNum,OutputArray );
   
	while(OutputArray[indexnum]!= '\0'){

		     x =(unsigned char)OutputArray[indexnum];
        HC05_WriteChar(&x);
			  indexnum++;
		    HC05_WriteChar("\n");
	}
    
}

