/*
 * Oled.h
 * Functions for writing to the OLED screen
 * Basically wraps drawing text and numbers to the OLED
 * Uses font.h -> 12 pixel wide fixed width
 */
#ifndef _OLED_SSD1306_H
#define _OLED_SSD1306_H

#define DEVICEADDR_OLED  0x3c
#include "stm32f10x.h"
#include "Interrupt.h"

extern void Oled_DisplayOn(void);
extern void Oled_DisplayOff(void);

extern const u8* Oled_DrawArea(u8 x0, u8 y0, u8 wide, u8 high,const u8* ptr);
extern void Set_ShowPos(u8 x, u8 y);
extern void Oled_DisplayFlip(void);
extern void GPIO_Init_OLED(void);
extern void Init_Oled(uint8_t leftHanded);
extern const u8* Data_Command(u8 len,const u8* ptr);
extern void Clear_Screen(void);//Clear the screen

/*Functions for writing to the screen*/
extern void OLED_DrawString(const char* string, const uint8_t length);
extern void OLED_DrawChar(char c, uint8_t x);
extern void OLED_DrawExtendedChar(uint8_t id, uint8_t x);
extern void OLED_DrawTwoNumber(uint8_t in, uint8_t x);
extern void OLED_BlankSlot(uint8_t xStart,uint8_t width);
extern void OLED_DrawThreeNumber(uint16_t in, uint8_t x);
extern void OLED_DrawIDLELogo(void);
extern void OLED_DrawSymbol(uint8_t x,uint8_t symbol);
extern void OLED_DrawFourNumber(uint16_t in, uint8_t x);
#endif
/******************************** END OF FILE *********************************/
