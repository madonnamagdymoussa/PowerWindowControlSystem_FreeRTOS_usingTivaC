#include "DMA_config.h"
#include "UART_reg.h"

/*
 * typedef struct{
    DMAChannelNum_t ChannelNum;
    DMA_DestAddressIncrement_t DestAddressIncrement;
    DMA_SrcAddressIncrement_t SrcAddressIncrement;
    DMA_DestDataSize_t DestDataSize;
    DMA_SrcDataSize_t SrcDataSize;
}DMA_ChannelControlWordConfig_t;
 *
 */

DMA_ConfigurationChannel_t  DMAChannel8_UARTChannel0RX={
     DMAChannel_8,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};

DMA_ConfigurationChannel_t DMAChannel9_UARTChannel0TX={
     DMAChannel_9,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};

/****************************************************************************************************/
DMA_ConfigurationChannel_t  DMAChannel22_UARTChannel1RX={
     DMAChannel_22,
     Byte_DestInc,
     NoIncrement_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     EncodingNum_1
};

DMA_ConfigurationChannel_t  DMAChannel23_UARTChannel1TX={
     DMAChannel_9,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     EncodingNum_1
};
/****************************************************************************************************/
DMA_ConfigurationChannel_t DMAChannel0_UARTChannel2RX={
     DMAChannel_0,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};

DMA_ConfigurationChannel_t DMAChannel23_UARTChannel2TX={
     DMAChannel_1,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};
/****************************************************************************************************/

DMA_ConfigurationChannel_t DMAChannel16_UARTChannel3RX={
     DMAChannel_16,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};

DMA_ConfigurationChannel_t DMAChannel17_UARTChannel3TX={
     DMAChannel_17,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};
/****************************************************************************************************/
DMA_ConfigurationChannel_t  DMAChannel18_UARTChannel4RX={
     DMAChannel_18,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};

DMA_ConfigurationChannel_t DMAChannel19_UARTChannel4TX={
     DMAChannel_19,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};
/****************************************************************************************************/


DMA_ConfigurationChannel_t DMAChannel6_UARTChannel5RX={
     DMAChannel_6,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};

DMA_ConfigurationChannel_t DMAChannel7_UARTChannel5TX={
     DMAChannel_7,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};
/****************************************************************************************************/
DMA_ConfigurationChannel_t DMAChannel10_UARTChannel6RX={
     DMAChannel_10,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};

DMA_ConfigurationChannel_t DMAChannel11_UARTChannel6TX={
     DMAChannel_11,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};
/****************************************************************************************************/
DMA_ConfigurationChannel_t DMAChannel20_UARTChannel7RX={
     DMAChannel_20,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};

DMA_ConfigurationChannel_t DMAChannel21_UARTChannel7TX={
     DMAChannel_21,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode
};
/****************************************************************************************************/

DMA_ConfigurationChannel_t  *   DMA_ChannelsConfigTX[8]={

  &DMAChannel9_UARTChannel0TX,
  &DMAChannel23_UARTChannel1TX,
  &DMAChannel23_UARTChannel2TX,
  &DMAChannel17_UARTChannel3TX,
  &DMAChannel19_UARTChannel4TX,
  &DMAChannel7_UARTChannel5TX,
  &DMAChannel11_UARTChannel6TX,
  &DMAChannel21_UARTChannel7TX
};

DMA_ConfigurationChannel_t *DMA_ChannelsConfigRX[8]={

   &DMAChannel8_UARTChannel0RX,
   &DMAChannel22_UARTChannel1RX,
   &DMAChannel0_UARTChannel2RX,
   &DMAChannel16_UARTChannel3RX,
   &DMAChannel18_UARTChannel4RX,
   &DMAChannel6_UARTChannel5RX,
   &DMAChannel10_UARTChannel6RX,
   &DMAChannel20_UARTChannel7RX

 };


/****************************************************************************************************/
DMA_ConfigurationChannel_t  DMAChannel30_MemToMem={
     DMAChannel_30,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     AutoRequest,
     EncodingNum_0,
     _8_Transfers
};

DMA_ConfigurationChannel_t *Pt_DMAChannel30_MemToMem=&DMAChannel30_MemToMem;
/****************************************************************************************************/
