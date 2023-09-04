#include "jmos-string.h"
#include "jmos-heap.h"
#include "jmos-bool.h"

bool stringcmp(string* s1, string* s2){
    return false;
}

void strcpy(string* src, string* dest){
    dest->s = jmalloc(src->size); // Alloc an array of src->size bytes, since dest->s will be an array of src->size char's

    return;
}
