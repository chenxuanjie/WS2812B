#ifndef __DMA1_H__
#define __DMA1_H__

void DMA1_Init(uint32_t MemoryBaseAddr);
void DMA1_Start(uint16_t DataNumber);
void DMA1_SetIRQHandler(void (*IRQHandler)(void));

#endif
