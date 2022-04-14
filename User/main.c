#include "stm32f10x.h"                  // Device header
#include "stdlib.h"
#include "Delay.h"
#include "OLED.h"
#include "TIM2.h"
#include "WS2812B.h"
#include "TIM3.h"


uint8_t KeyNum = 3;
uint8_t WhiteLight_Brightness, UpdateFlag=1;
uint8_t ColorLight_Mode,ColorLight_Flag;
uint16_t ColorLight_Time;

void White_Light(void);
void ColorLight_Mode0(void);
void MainLoop(void);
void ColorLight(void);

int main(void)
{
	OLED_Init( );
	WS2812B_Init();
	TIM3_SetIRQHandler(MainLoop);
	TIM3_Init();
	while (1)
	{
		ColorLight();	
	}
}

void White_Light(void)
{
	WS2812B_SetBuf(0x003F3F3F);
	WS2812B_UpdateBuf();
}

void ColorLight_Mode0(void)
{
	static uint8_t i,Color;
	ColorLight_Time=6;

	if(i==0)WS2812B_SetBuf((Color));
	if(i==1)WS2812B_SetBuf((255-Color));
	if(i==2)WS2812B_SetBuf((Color)<<8);
	if(i==3)WS2812B_SetBuf((255-Color)<<8);
	if(i==4)WS2812B_SetBuf((Color)<<16);
	if(i==5)WS2812B_SetBuf((255-Color)<<16);
	if(i==6)WS2812B_SetBuf((Color)|((Color)<<8));
	if(i==7)WS2812B_SetBuf((255-Color)|((255-Color)<<8));
	if(i==8)WS2812B_SetBuf((Color)|((Color)<<16));
	if(i==9)WS2812B_SetBuf((255-Color)|((255-Color)<<16));
	if(i==10)WS2812B_SetBuf(((Color)<<8)|((Color)<<16));
	if(i==11)WS2812B_SetBuf(((255-Color)<<8)|((255-Color)<<16));
	if(i==12)WS2812B_SetBuf(((Color))|((Color)<<8)|((Color)<<16));
	if(i==13)WS2812B_SetBuf(((255-Color))|((255-Color)<<8)|((255-Color)<<16));

	Color++;
	if(Color==0)
	{
		i++;
		i%=14;
	}
}

void ColorLight_Mode1(void)
{
	uint8_t i,RandNum;
	uint32_t G,R,B;
	static uint8_t j;
	ColorLight_Time=20;
	for(i=31;i>0;i--)
	{
		WS2812B_Buf[i]=WS2812B_Buf[i-1];
	}
	
	if(j==0)
	{
		RandNum=rand()%7;
		if(RandNum==0)WS2812B_Buf[0]=0x0000FF;
		if(RandNum==1)WS2812B_Buf[0]=0x00FF00;
		if(RandNum==2)WS2812B_Buf[0]=0xFF0000;
		if(RandNum==3)WS2812B_Buf[0]=0x00FFFF;
		if(RandNum==4)WS2812B_Buf[0]=0xFF00FF;
		if(RandNum==5)WS2812B_Buf[0]=0xFFFF00;
		if(RandNum==6)WS2812B_Buf[0]=0xFFFFFF;
	}
	else if(j<15)
	{
		G=WS2812B_Buf[1]/0x10000%0x100;
		R=WS2812B_Buf[1]/0x100%0x100;
		B=WS2812B_Buf[1]%0x100;
		if(G>20)G-=20;
		if(R>20)R-=20;
		if(B>20)B-=20;
		WS2812B_Buf[0]=(G<<16)|(R<<8)|B;
	}
	else
	{
		WS2812B_Buf[0]=0;
	}
	
	j++;
	j%=50;
}

void ColorLight_Mode2(void)
{
	uint8_t i;
	static uint8_t j;
	ColorLight_Time=20;
	for(i=31;i>0;i--)
	{
		WS2812B_Buf[i]=WS2812B_Buf[i-1];
	}
	if(j==0)WS2812B_Buf[0]=rand()%0x1000000;
	else WS2812B_Buf[0]=WS2812B_Buf[1];
	j++;
	j%=10;
}

void ColorLight_Mode3(void)
{
	uint8_t i;
	ColorLight_Time=500;
	for(i=0;i<32;i++)
	{
		WS2812B_Buf[i]=rand()%0x1000000;
	}
}

void ColorLight(void)	//MODE=3
{
	if(KeyNum==1)	//ColorLight->Close
	{
		UpdateFlag=1;
		return;
	}
	if(KeyNum==2)	//ColorLight->WhiteLight
	{
		WhiteLight_Brightness=0;
		UpdateFlag=1;
		return;
	}
	if(KeyNum==3)	//ColorLight->ColorLight
	{
//		ColorLight_Mode++;
//		ColorLight_Mode%=4;
		ColorLight_Mode = 2;
		UpdateFlag=1;
		KeyNum = 0;
	}
	if(UpdateFlag)
	{
		UpdateFlag=0;
		WS2812B_SetBuf(0x000000);
		WS2812B_UpdateBuf();
	}
	if(ColorLight_Flag)
	{
		ColorLight_Flag=0;
		if(ColorLight_Mode==0)
		{
			ColorLight_Mode0();
			WS2812B_UpdateBuf();
		}
		if(ColorLight_Mode==1)
		{
			ColorLight_Mode1();
			WS2812B_UpdateBuf();
		}
		if(ColorLight_Mode==2)
		{
			ColorLight_Mode2();
			WS2812B_UpdateBuf();
		}
		if(ColorLight_Mode==3)
		{
			ColorLight_Mode3();
			WS2812B_UpdateBuf();
		}
	}
}

void MainLoop(void)
{
	static uint16_t LoopCount[1];
	LoopCount[0]++;
	if(LoopCount[0]>=ColorLight_Time)
	{
		LoopCount[0]=0;
		ColorLight_Flag=1;
	}
}

