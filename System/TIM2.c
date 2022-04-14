#include "stm32f10x.h"                  // Device header
#include "DMA1.h"

void TIM2_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimerBaseInitStructure;
	TIM_TimerBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//1分频
	TIM_TimerBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimerBaseInitStructure.TIM_Period = 90 - 1;
	TIM_TimerBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimerBaseInitStructure.TIM_RepetitionCounter = 0;	//高级定时器才能用到
	TIM_TimeBaseInit(TIM2, &TIM_TimerBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM2, ENABLE);
	TIM_DMAConfig(TIM2, TIM_DMABase_CCR1, TIM_DMABurstLength_1Transfer);
	TIM_DMACmd(TIM2, TIM_DMA_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_Cmd(FunctionalState NewState)
{
	TIM_Cmd(TIM2, NewState);
}

void TIM2_SetCompare1(uint16_t Value)
{
	TIM_SetCompare1(TIM2,Value);
}
