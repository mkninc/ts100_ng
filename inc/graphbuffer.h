/*
 * graphbuffer.h
 *
 *  Created on: 02.08.2017
 *      Author: Marco
 */

#ifndef INC_GRAPHBUFFER_H_
#define INC_GRAPHBUFFER_H_

#include <stdint.h>
#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif


extern void Graphic_Init(void);

extern void Graph_Update(void);

extern void Graph_Clear(void);

extern void Graph_DrawPixel(u32 const x, u32 const y, u32 const value);

extern void Graph_DrawHorizontalBar(u32 const x, u32 const y, u32 const length);

extern void Graph_DrawArea(u32 const x0, u32 const y0, u32 const width, u32 const height, u8 const * data);

#ifdef __cplusplus
}
#endif

#endif /* INC_GRAPHBUFFER_H_ */
