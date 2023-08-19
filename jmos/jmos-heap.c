#include "jmos-heap.h"
#include "../hal/jmos-stm32-periph.h"
#include "jmos-math.h"

// --- From Linker Script --- //
extern uint32 HEAP_SIZE;
extern unsigned char _sheap;
extern uint32 _eheap;
// -------------------------- //

#define TBL_SIZE 256 
#define ENT_SIZE (udiv(HEAP_SIZE, TBL_SIZE))

static uint16 memtable[TBL_SIZE];

void* allocate_blocks(int startIdx, unsigned int size){
    // Start of heap is stored in the symbol table as the *addr* of the linker script var _sheap
    unsigned char * heap_ptr = &_sheap; 
    
    unsigned char * alloc_start = heap_ptr + (startIdx * ENT_SIZE);

    for(int i = 0; i < size; i++){
        alloc_start[i] = 0;
    }

    return alloc_start; 
}

void mark_memtable(int startIdx, unsigned int numblocks, unsigned int size){
    // Basically the idea is we mark the memory table, which is a condensed representation of the actual heap,
    // with some info about used memory
    // The scheme I decided to use is to mark the first entry in a sequence of blocks (the one the alloc ptr refers to)
    // with the size of the alloc. From there, we can deduce based on that size how many blocks to free.
    // Everything after the first entry just needs to be non-zero, so I mark them as ~0, or 0xFFFF.
    memtable[startIdx] = size;
    for(int i = 1; i < numblocks; i++){
        memtable[startIdx + i] = ~0;
    }
}


void* jmalloc(unsigned int size){

    int remainder = umod(size, ENT_SIZE);
    unsigned int numblocks = udiv(size, ENT_SIZE);
    if(remainder != 0){
        numblocks++;
    }

    if(numblocks > TBL_SIZE){
        return NULL;
    }

    // This is essentially a "given an array of ints, find a sequence of 0s in the array that is at least 'size' long"
    // type of problem. Very leetcode. Much wow.
    for(int i = 0; i < TBL_SIZE - numblocks; i++){
        int j = i;
        while(memtable[j] == 0){
            if((j-i) == numblocks-1){
                // we did it, boys
                void* allocated_ptr = allocate_blocks(i, size);
                mark_memtable(i, numblocks, size);
                return allocated_ptr;
            }
            j++;
        }
        i = j;
    }
    return NULL;
}

void free(void * ptr){
    unsigned char * heap_ptr = &_sheap;
    uint32 blocksize = ptr - (void*)heap_ptr;
    int startIdx = udiv(blocksize, ENT_SIZE); // this should divide perfectly, if not, we done fmessed up
    int size = memtable[startIdx];

    int remainder = umod(size, ENT_SIZE);
    unsigned int numblocks = udiv(size, ENT_SIZE);
    if(remainder != 0){
        numblocks++;
    }

    for(int i = startIdx; i < startIdx + numblocks; i++){
        memtable[i] = 0;
    }
}

// If heap size is 0x400 (1024, or 256 words), a 32-bit word can store free/used flags for 32 blocks of 32 bytes = 8 words
// One option is to put a fixed size table at _sheap to track usage of blocks
//  -- problem is that alloc's beyond single-block size have to be tracked somehow.. ids? kinda slow to do alloc and free
// Other option is to allocate as blocks with headers, not great for small alloc's
//  -- problem is you need to maintain a list of free'd blocks and reference that list during alloc
//  -- kind of a pain to implement
//
// Can use a static table in the .data segment instead of stack or heap, should leave the full 0x400 available
// Ok, so what if fixed size table that records the size of the alloc, maybe along with some id:
// 0  | ushort size | 
// 1  
// 2
// 3
// ...
// 28
// 29
// 30
// 31

