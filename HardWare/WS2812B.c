#include "stm32f10x.h"                  // Device header
#include "TIM2.h"
#include "DMA1.h"
#include "WS2812B.h"

uint8_t WS2812B_Flag;
uint32_t WS2812B_Buf[WS2812B_LED_QUANTITY];	//0xGGRRBB
uint16_t WS2812B_Bit[24*WS2812B_LED_QUANTITY+1];
uint8_t WS2812B_Flag;

void WS2812B_IRQHandler(void);

void WS2812B_Init(void)
{
	DMA1_SetIRQHandler(WS2812B_IRQHandler);
	DMA1_Init((uint32_t)(&WS2812B_Bit));
	TIM2_Init();
}

void WS2812B_ClearBuf(void)
{
	uint8_t i;
	for(i=0;i<WS2812B_LED_QUANTITY;i++)
	{
		WS2812B_Buf[i]=0x000000;
	}
}

void WS2812B_SetBuf(uint32_t Color)
{
	uint8_t i;
	for(i=0;i<WS2812B_LED_QUANTITY;i++)
	{
		WS2812B_Buf[i]=Color;
	}
}

void WS2812B_UpdateBuf(void)
{
	uint8_t i,j;
	for(j=0;j<WS2812B_LED_QUANTITY;j++)
	{
		for(i=0;i<24;i++)
		{
			if(WS2812B_Buf[j]&(0x800000>>i)){WS2812B_Bit[j*24+i+1]=60;}
			else{WS2812B_Bit[j*24+i+1]=30;}
		}
	}
	DMA1_Start(24*WS2812B_LED_QUANTITY+1);
	TIM2_Cmd(ENABLE);
	while(WS2812B_Flag==0);
	WS2812B_Flag=0;
}

void WS2812B_IRQHandler(void)
{
	TIM2_SetCompare1(0);
	TIM2_Cmd(DISABLE);
	WS2812B_Flag=1;
}
