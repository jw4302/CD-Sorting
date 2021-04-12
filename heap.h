#ifndef HEAP_H
#define HEAP_h
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


typedef unsigned int offset;
typedef unsigned int size_in_bytes;
typedef unsigned int size_in_words;

#define NULL_OFFSET INT_MAX
#define block_size(h, offset) h->space[offset]
#define block_prev_offset(h, offset) h->space[offset+1]
#define block_next_offset(h, offset) h->space[offset+2]

typedef struct heap_strc {
    offset used_head_offset;
    offset free_head_offset;
    size_in_words size;
    unsigned int *space;
} *heap_ptr;

size_in_words convert_bytes_to_words(size_in_bytes sb);
heap_ptr create_heap(size_in_bytes size);
void split_free(heap_ptr h, offset block_to_split,size_in_words split_size);
void myMalloc(heap_ptr h, size_in_bytes size);

void insertNodeToList(heap_ptr h, size_in_words size, offset node_offset);
void deleteNodeFromList(heap_ptr h, offset head_offset, offset node_offset);
void free_heap(heap_ptr h);
bool myFree(heap_ptr h, offset node_offset);
#endif


/*
 *  Todo and Questions
 *      Why the seg fault
 *      Why is the insert failing here
 *      Refactoring Size_of_bytes and Size_of_Words
 *      What adjustments are needed to insertNodeToList
 *      
 */