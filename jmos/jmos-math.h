#ifndef MATH_H
#define MATH_H

#include "../hal/jmos-stm32-periph.h"

/* Set INF to highest possible uint32 value */
#define INF ((uint32)~0)

/* Unsigned int32 floor division with remainder */
uint32 udivr(uint32 num, uint32 denom, uint32* rem);

/* Unsigned int32 floor division */ 
uint32 udiv(uint32 num, uint32 denom);

/* Unsigned int32 modulo */
uint32 umod(uint32 num, uint32 mod);

#endif
