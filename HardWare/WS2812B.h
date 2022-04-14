#ifndef __WS2812B_H__
#define __WS2812B_H__

#define WS2812B_LED_QUANTITY	8

extern uint16_t WS2812B_Bit[24*WS2812B_LED_QUANTITY+1];
extern uint32_t WS2812B_Buf[WS2812B_LED_QUANTITY];

void WS2812B_Init(void);
void WS2812B_ClearBuf(void);
void WS2812B_SetBuf(uint32_t Color);
void WS2812B_UpdateBuf(void);
void WS2812B_IRQHandler(void);

#endif
