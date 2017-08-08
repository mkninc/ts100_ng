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

//-----------------------------------------------------------------------------
void Graphic_Init(void) {
	Graph_Clear();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Graph_Update(void) {
#ifndef SIMULATION_BOARD
	Oled_DrawArea(0, 0, 96, 8, &gr_buffer[0][0]);
	Oled_DrawArea(0, 8, 96, 8, &gr_buffer[1][0]);
#endif
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Graph_Clear(void) {
	memset(gr_buffer, 0, sizeof(gr_buffer));
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Graph_DrawHorizontalBar(u32 const x, u32 const y, u32 const length) {
	for (u32 i = x; i < x + length; i++) {
		Graph_DrawPixel(i, y, 0xFF);
	}
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Graph_DrawPixel(u32 const x, u32 const y, u32 const value) {
	u32 row;
	u8 pixel;

	row = (y / 8);
	pixel = 1 << (y % 8);

	if (value) {
		gr_buffer[row][x] |= pixel;
	} else {
		gr_buffer[row][x] &= ~pixel;
	}
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Graph_DrawArea(u32 const x0, u32 const y0, u32 const width, u32 const height,
		u8 const * data) {
	u32 row;
	u8 pixel;

for(u32 x = 0; x < width; x++)
{
	for(u32 y = 0; y < height; y++)
	{
		row = (y / 8);
		pixel = 1 << (y % 8);

		Graph_DrawPixel(x + x0, y + y0, data[x + row * width] & pixel);
	}
}

}
//-----------------------------------------------------------------------------
