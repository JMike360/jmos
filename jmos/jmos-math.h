#ifndef MATH_H
#define MATH_H

#include "../hal/jmos-stm32-periph.h"

#define INF ((uint32)~0)

uint32 udiv(uint32 num, uint32 denom);

uint32 umod(uint32 num, uint32 mod);

#endif
