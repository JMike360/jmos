#ifndef STRING_H
#define STRING_H

#include "jmos-bool.h"

typedef struct string {
    char* s;
    int size;
} string;

bool stringcmp(string* s1, string* s2);

void stringcpy(string* src, string* dest);

#endif
