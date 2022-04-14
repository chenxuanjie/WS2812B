#include "stm32f10x.h"                  // Device header
#include "TIM2.h"

void (*DMA1_Handler)(void);

void DMA1_Init(uint32_t MemoryBaseAddr)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel2);
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_BufferSize = 0;		//?
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = MemoryBaseAddr;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&TIM2->CCR1);
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);
	DMA_Cmd(DMA1_Channel2, ENABLE);
}


void DMA1_Start(uint16_t DataNumber)
{
	DMA_Cmd(DMA1_Channel2,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel2,DataNumber);
	DMA_Cmd(DMA1_Channel2,ENABLE);
}

void DMA1_SetIRQHandler(void (*IRQHandler)(void))
{
	DMA1_Handler=IRQHandler;
}

void DMA1_Channel2_IRQHandler(void)
{
	if (DMA_GetFlagStatus(DMA1_FLAG_TC2))
	{
		DMA1_Handler();
		DMA_ClearFlag(DMA1_FLAG_TC2);
	}
}
