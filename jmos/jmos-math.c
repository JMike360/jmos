#include "jmos-math.h"
#include "jmos-heap.h"

/* Unsigned int32 floor division with remainder
 * Parameters:
 * uint32 num: Numerator, unsigned 32 bit int
 * uint32 denom: Denominator, unsigned 32 bit int
 * uint32* rem: An optional remainder output argument.
 *              If rem != NULL, the remainder will be stored at the addr value of rem
 */
uint32 udivr(uint32 num, uint32 denom, uint32* rem){
    char INT_SIZE = 32;

    if(denom == 0){
        return INF;
    }

    if(num == denom){
        return 1;
    }

    if(num < denom){
        return 0;
    }

    char i = 1;
    uint32 q = 0;

    while(i < INT_SIZE + 1){
        uint32 n = num >> (INT_SIZE - i);

        if(n < denom){
            q <<= 1;
        }
        else{
            uint32 d = denom << (INT_SIZE - i);
            num -= d;
            q |= 1;
            q <<= 1;
        }

        i++;
    }

    if(rem != NULL){
        *rem = num;
    }
    return q;
}

/* Unsigned in32 floor division without remainder */
uint32 udiv(uint32 num, uint32 denom){
    return udivr(num, denom, NULL);
}

/* Unsigned int32 modulo */
uint32 umod(uint32 num, uint32 mod){
    uint32 remainder = 0;
    udivr(num, mod, &remainder);
    return remainder;
}
