#include "heap.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

size_in_words convert_bytes_to_words(size_in_bytes sb){
    size_in_words sw = sb/4;
    if (sb%4 != 0){
        sw++;
    }
    return sw;
}

 heap_ptr create_heap(size_in_bytes size_b)
 {
     heap_ptr h = (heap_ptr)malloc(sizeof(struct heap_strc));
     h->used_head_offset = NULL_OFFSET;
     h->free_head_offset = 0;
     h->size = convert_bytes_to_words(size_b);
     h->space = (int *)malloc(h->size);
     block_size(h, 0) = h->size;
     block_prev_offset(h, 0) = NULL_OFFSET;
     block_next_offset(h, 0) = NULL_OFFSET;
     return h;
 }

void split_free(heap_ptr h, offset block_to_split, size_in_words split_size)
{
    offset split_point = block_to_split + split_size;
    block_size(h, split_point) = block_size(h, block_to_split) - split_size;
    block_next_offset(h, split_point) = block_next_offset(h, block_to_split);
    block_prev_offset(h, split_point) = block_to_split;
    block_next_offset(h, block_to_split) = split_point;
    block_size(h, block_to_split) = split_size;
}


/*
 *  Find a free block that is big enough for size bytes plus a header
    Split that free block into two parts:  the part you need and the rest
    Delete the part you need from the free list
    Insert the part you need into the used list at the right head_offset
 */
void myMalloc(heap_ptr h, size_in_bytes size){  
    size_in_words size_w = convert_bytes_to_words(size) + 3;
    offset curr = h->free_head_offset;
    printf("this is curr: %d\n", curr);
    printf("this is size: %d\n", size_w);
    //loop walking through heap to find open blocks
    while((curr != NULL_OFFSET) && (block_size(h,curr) < size_w)){
        curr = block_next_offset(h, curr);
    }
    if (curr != NULL_OFFSET)
    {   
        printf("we get this far\n");
        split_free(h, curr, size_w);                    //splits block
        deleteNodeFromList(h, h->free_head_offset, curr);                  //deleteNodeFromList(h, h->head_offset, cur)  
        insertNodeToList(h, h->used_head_offset, curr);  
    }else{
        printf("This is no room left\n");
    }
    printf("This is a completed myMalloc\n");
}




// void insertNodeToList(heap_ptr h, offset head_offset, offset node_offset){
void insertNodeToList(heap_ptr h, offset head_offset, offset node_offset){
    //SuccesorNode->prev->next = insertNode;
    //InsertNode->prev = succesorNode->prev;
    //succesorNode->prev = insertNode;
    //insertNode->next = succesorNode;
    
    // make a loop that makes curr be the offset of the node we want to insert before   
    offset curr = head_offset;
    offset prev = NULL_OFFSET;
    printf("this is curr before while size check: %d\n", curr);
    //While it is not at the beginning and while the current block is less than the new node
    while((curr != NULL_OFFSET) && (curr < node_offset)){
        prev = curr;
        curr = block_next_offset(h, curr);
    }
    printf("this is curr after size is checked: %d\n", curr);

    //checking if this is the first node in the list
    if (prev == NULL_OFFSET)
    {
        // update head pointer
        if (head_offset == h->free_head_offset)
        {
            // update the head of the free list
            h->free_head_offset = node_offset;
            
        } else
        {
            //update the head of the used list
            h->used_head_offset = node_offset;
            
        }
        
        //make size's prev NULL_OFFSET
        block_prev_offset(h, node_offset) = NULL_OFFSET;
    } else
    {
        //connect prev to the "left" list of size
        block_prev_offset(h, node_offset) = prev;
        block_next_offset(h, prev) = node_offset;
    }

    if (curr == NULL_OFFSET)
    {
        //make size's next NULL_OFFSET
 
        block_next_offset(h, node_offset) = NULL_OFFSET;
   
    } else
    {
        //connect curr to the "right" list of size
        block_next_offset(h, node_offset) = curr;
        block_prev_offset(h, curr) = node_offset;
        
    }
    // end of function
    // if (curr == 0)
    // {
    //         //inserting at the front of the list
    //         //make sure you also update h
    //         block_size(h, curr) = size;
    //         block_prev_offset(h, curr) = NULL_OFFSET;
    //         block_next_offset(h, curr) = NULL_OFFSET;

    // } else if (curr == NULL_OFFSET)
    // {
    //         //insert at the end of the list
    //         block_prev_offset(h, curr) = node_offset;
    //         block_next_offset(h, node_offset) = curr;
    //         block_size(h, node_offset) = size;

    // } else
    // {
    //         //insert into the middle of the list
    //         printf("The middle is broken actually\n");
    //         block_prev_offset(h, curr) = node_offset;
    //         block_prev_offset(h, node_offset) = block_prev_offset(h, curr);
    //         block_prev_offset(h, curr) = node_offset;
    //         block_next_offset(h, node_offset) = curr;
    //         block_size(h,curr) = size;

    // }
}


void deleteNodeFromList(heap_ptr h, offset head_offset, offset node_offset){                //deleteNodeFromList(heap_ptr h, offset head_offset, offset node_offset)


    // update head pointer
    //checking to see where the head of the list is    
    if(block_prev_offset(h, node_offset) == NULL_OFFSET){
        if (head_offset == h->free_head_offset)
        {
            // update the head of the free list
            h->free_head_offset = block_next_offset(h, node_offset);

        }else if(head_offset == h->used_head_offset)
        {
            //update the head of the used list
            h->used_head_offset = block_next_offset(h, node_offset);
        }
        //if the node to delete isn't at the front of the list then link the nodes around it to each other
        //starting with the node to the left of our deletion
    }else if(block_prev_offset(h, node_offset) != NULL_OFFSET){

            block_next_offset(h, block_prev_offset(h,node_offset)) = block_next_offset(h, node_offset);
    }

    // and then with the right of our deletion    
    if( block_next_offset(h, node_offset) != NULL_OFFSET)
    {
            //When node_offset is not the last offset
            block_prev_offset(h, block_next_offset(h, node_offset)) = block_prev_offset(h, node_offset);
    }
}
// freeing by the blocks position not size or anything else.
bool myFree(heap_ptr h, offset block_position){
    
    if(block_next_offset(h, block_position) != block_next_offset(h, h->free_head_offset)){
        
        deleteNodeFromList(h, h->used_head_offset, block_position);           
        insertNodeToList(h, h->free_head_offset, block_position);  
    }else{
        printf("Block already freed\n");
        return false;
    }
    return true;
}

void free_heap(heap_ptr h){
    free(h->space);
    free(h);
}