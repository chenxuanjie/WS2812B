#ifndef __TIM2_H__
#define __TIM2_H__

extern uint16_t Num;

void TIM2_Init(void);
void DMA1_Init(uint32_t MemoryBaseAddr);
void TIM2_Cmd(FunctionalState NewState);
void TIM2_SetCompare1(uint16_t Value);
void WS2812B_IRQHandler(void);

#endif
