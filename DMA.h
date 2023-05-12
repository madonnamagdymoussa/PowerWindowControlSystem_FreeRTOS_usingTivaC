
#ifndef DMA_H_
#define DMA_H_

#include "DMA_config.h"

void DMA_ConfigureControlTableBaseAddress(void *ptControlTable);
void DMA_PeripheralInitialization();
void DMA_ChannelInitialization(DMAChannelNum_t ChannelNum, DMA_ConfigurationChannel_t* PtrDMAConfig);

void DMA_ConfigureChannelSoftwareRequest(DMA_SoftwareRequestMode_t RequestMode,DMAChannelNum_t ChannelNum);
void DMA_ConfigurePriority(DMAConfigurePrioChannel_t ConfigurePrioChannel, DMAChannelNum_t ChannelNum);
void DMA_ConfigurePeripheralInterrupt(DMA_InterruptStatus Status);
void DMA_ConfigureChannelInterrupt(DMA_InterruptStatus Status, DMAChannelNum_t ChannelNum);
void DMA_EnableChannel(DMAChannelNum_t ChannelNum);

void DMA_AssignChannel(u8_t DMA_ChannelNum, u8_t EncodingNum);
void DMA_DeAssignChannel(u8_t DMA_ChannelNum, u8_t EncodingNum);

void DMA_ChannelControlStructureSet(DMA_ConfigurationChannel_t* ptrConfig, u32_t*SourceAddress , u32_t*DestAddress );
void DMA_RegisterCallbackFunction_SoftwareTransfer(DMAChannelNum_t ChannelNum, CallbackFunc_t pt_callback);
void DMA_RegisterCallbackFunction_ErrorHandler(DMAChannelNum_t ChannelNum, CallbackFunc_t pt_callback);

void DMA_MemoryToMemory_Transfer(u8_t*SourceAddress , u8_t*DestAddress);

#endif /* DMA_H_ */
