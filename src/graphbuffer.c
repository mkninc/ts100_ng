/*
 * graphbuffer.c
 *
 *  Created on: 02.08.2017
 *      Author: Marco
 */
#include <string.h>
#include "Oled.h"

#include "graphbuffer.h"

static u8 gr_buffer[2][96];

void Graphic_Init(void)
{
	Graph_Clear();
}

void Graph_Update(void)
{
Oled_DrawArea(0, 0, 96, 8, &gr_buffer[0][0]);
Oled_DrawArea(0, 8, 96, 8, &gr_buffer[1][0]);
}

void Graph_Clear(void)
{
	memset(gr_buffer, 0, sizeof(gr_buffer));
}

void Graph_DrawHorizontalBar(u32 const x, u32 const y, u32 const length)
{
	for(u32 i = x; i < x + length; i++)
	{
		Graph_DrawPixel(i, y, 0xFF);
	}
}


void Graph_DrawPixel(u32 const x, u32 const y, u32 const value)
{
	u32 row;
	u8 pixel;

	row = (y / 8);
	pixel = 1 << (y % 8);

	gr_buffer[row][x] |= pixel;
}
