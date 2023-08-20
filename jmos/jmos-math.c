#include "jmos-math.h"

uint32 udiv(uint32 num, uint32 denom){
    uint32 cnt = 0;
    if(denom == 0){
        return INF;
    }

    while(num >= denom){
        num -= denom;
        cnt++;
    }

    return cnt;
}

uint32 umod(uint32 num, uint32 mod){
    uint32 quot = udiv(num, mod);
    if(quot == 0){
        return num;
    }
    uint32 remainder = num - (mod * quot);
    return remainder;
}