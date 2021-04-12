#include "heap_test.h"
#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


void test_heap_creation() {

    heap_ptr h = create_heap(500);
    assert(h->size == 125);
    assert(h->free_head_offset == 0);
    assert(block_size(h, 0) == h->size);
    free_heap(h);
    printf("~~~~~~~Passed Test Heap Creation\n");

}

void test_split_free_spot_once()
{
    
    heap_ptr h = create_heap(500);
    split_free(h, 0, 10);
    size_in_words second_block_size = 500/4 - 10;
    assert(h->free_head_offset == 0);
    assert(block_size(h, 0) == 10);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);
    assert(block_next_offset(h, 0) == 10);
    assert(block_size(h, 10) == second_block_size);
    assert(block_prev_offset(h, 10) == 0);
    assert(block_next_offset(h, 10) == NULL_OFFSET);
    free_heap(h);
    printf("~~~~~~~Passed Split Free Spot Once\n");
}

void test_split_free_spot_twice()
{
    
    heap_ptr h = create_heap(500);
    split_free(h, 0, 10);
    split_free(h, 10, 20);
    assert(h->free_head_offset == 0);
    assert(block_size(h, 0) == 10);
    assert(block_prev_offset(h,0) == NULL_OFFSET);
    assert(block_next_offset(h, 0) == 10);
    assert(block_size(h, 10) == 20);
    assert(block_prev_offset(h, 10) ==0);
    assert(block_next_offset(h, 10) == 30);
    assert(block_size(h, 30) == 500/4-30);
    assert(block_prev_offset(h, 30) == 10);
    assert(block_next_offset(h, 30) == NULL_OFFSET);
    free_heap(h);
    printf("~~~~~~Passed Split Free Spot Twice\n");

}

void test_single_myMalloc(){
    heap_ptr h = create_heap(500);
    myMalloc(h, 50);

    assert(block_size(h, 0) == 16);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);
    assert(block_next_offset(h, 0) == NULL_OFFSET);

    free_heap(h);
    printf("~~~~~Passed Test Single myMalloc\n");

}

void test_two_myMalloc(){
    
    heap_ptr h = create_heap(500);
    myMalloc(h, 50);
  
    assert(block_size(h,0) == 16);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);
     
    myMalloc(h, 70);
    assert(block_next_offset(h, 0) == 16);
    assert(block_size(h, 16) == 21);
    assert(block_prev_offset(h, 16) == 0);
    assert(block_next_offset(h, 16) == NULL_OFFSET);
    free_heap(h);
    printf("~~~~~~~Passed Two myMalloc\n");
}

void test_three_myMallocs(){
    
    heap_ptr h = create_heap(500);
    myMalloc(h, 50);
  
    assert(block_size(h,0) == 16);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);
     
    myMalloc(h, 50);
    assert(block_next_offset(h, 0) == 16);
    assert(block_size(h,16) == 16);
    assert(block_prev_offset(h, 16) == 0);
    assert(block_next_offset(h, 16) == NULL_OFFSET);
    myMalloc(h, 5);
    assert(block_size(h , 32) == 5);
    assert(block_next_offset(h, 32) == NULL_OFFSET);
    free_heap(h);
    printf("~~~~~~~~Passed Three myMalloc\n");
}



void test_single_myMalloc_and_single_myFree(){
    
    heap_ptr h = create_heap(500);
    myMalloc(h, 50);
    assert(block_size(h, 0) == 16);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);
    assert(block_next_offset(h, 0) == NULL_OFFSET);
    myFree(h, 0);
    assert(h->size == 125);
    free_heap(h);

printf("~~~~~~~~~Passed Single myMalloc and Single Free\n");
}

void test_three_myMallocs_and_myFree_first(){
    
    heap_ptr h = create_heap(500);
    myMalloc(h, 10); 
    myMalloc(h, 20);
    myMalloc(h, 50);
    myFree(h, 0);
    assert(h->free_head_offset == 0);
    assert(block_size(h, 0) == 6);
    assert(block_next_offset(h, 0) == 30);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);
    free_heap(h);
    printf("~~~~~~~~Passed Three myMallocs and myFree First\n");

}

void  test_three_myMallocs_myFree_first_and_myMalloc_in_first(){
    
    heap_ptr h = create_heap(500);
    myMalloc(h, 50); 
    myMalloc(h, 10);
    myMalloc(h, 20);
    myFree(h, 0);  
    myMalloc(h, 20);
    assert(h->used_head_offset == 0);
    assert(block_size(h, 0) == 8);
    assert(block_next_offset(h, 0) == 16);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);
    free_heap(h);
    printf("~~~~~~Passed Three myMallocs, myFree  the First and myMalloc in First\n");
}

void test_three_myMallocs_and_myFree_second(){
    
    heap_ptr h = create_heap(500);
    myMalloc(h, 50); 
    myMalloc(h, 10);
    myMalloc(h, 20);
    myFree(h,16);
    assert(h->free_head_offset == 16);
    assert(block_size(h, 16) == 6);
    assert(block_next_offset(h, 0) == 22);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);
    free_heap(h);
    printf("~~~~~Passed Three myMallocs and myFree Second\n");
}

void test_three_myMallocs_myFree_second_and_myMalloc_in_second(){
    
    heap_ptr h = create_heap(500);
    myMalloc(h, 50); 
    myMalloc(h, 10);
    myMalloc(h, 20);
    myFree(h, 16);
    assert(h->free_head_offset == 16);
    assert(block_size(h, 0) == 16);
    assert(block_next_offset(h, 0) == 22);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);
    myMalloc(h, 6);

    //checking the first is there to link to the new second
    assert(h->used_head_offset == 0);
    assert(block_size(h, 0) == 16);
    assert(block_next_offset(h, 0) == 16);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);

    //checking that the new second is there and linking to the third
    assert(block_size(h, 16) == 5);
    assert(block_next_offset(h, 16) == 22);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);
    free_heap(h);
    printf("~~~~~Passed Three myMallocs myFree Second and myMalloc in second");
}

void test_three_myMallocs_and_myFree_third(){
    
    heap_ptr h = create_heap(500);
    myMalloc(h, 50); 
    myMalloc(h, 10);
    myMalloc(h, 20);
    myFree(h,22);
    assert(h->free_head_offset == 22);
    assert(block_size(h, 22) == 8);
    assert(block_next_offset(h, 22) == 30);
    assert(block_prev_offset(h, 22) == NULL_OFFSET);
    assert(block_size(h, 30) == 95);
    assert(block_next_offset(h, 30) == NULL_OFFSET);
    free_heap(h);
    printf("~~~~~Passed Three myMallocs and myFree Third\n");
}

void test_three_myMallocs_myFree_second_and_myMalloc_not_fit(){
    
    heap_ptr h = create_heap(500);
    myMalloc(h, 50); 
    myMalloc(h, 10);
    myMalloc(h, 20);
    myFree(h, 16);
    myMalloc(h, 15);
    assert(h->free_head_offset == 16);
    assert(block_size(h, 16) == 6);
    assert(block_next_offset(h, 16) == 37);
    assert(block_prev_offset(h, 16) == NULL_OFFSET);
    // assert(block_next_offset(h, 37) == NULL_OFFSET);
    //checking the new inserted to used is there
    assert(block_size(h, 30 ) == 7);
    assert(block_next_offset(h, 30) == NULL_OFFSET);

    free_heap(h);
    printf("~~~~~Passed Three myMallocs myFree second and myMalloc not fit\n");
}

void test_four_myMallocs_and_myFree_middle_two(){
    
    heap_ptr h = create_heap(500);
    myMalloc(h, 50); //16
    myMalloc(h, 10); //6
    myMalloc(h, 20); //8
    myMalloc(h, 20); //8
    myFree(h, 16);
    myFree(h, 22);
    assert(h->free_head_offset == 16);                      // freeing the second insert
    assert(block_size(h, 16) == 6);                        //checking its size 
    assert(block_next_offset(h, 16) == 22);                 //checking secondc next
    assert(block_prev_offset(h, 16) == NULL_OFFSET);        //checking seconds prev to null
    assert(block_size(h, 22) == 8);                        //checking the third insert
    assert(block_next_offset(h, 22) == 38);                //checking third's next to after last insert
    assert(block_prev_offset(h, 22) == 16);                 //checking third's prev to second
    assert(block_prev_offset(h, 38) == 22);                //checking last free blocks previous to third
    // assert(block_next_offset(h, 38) == NULL_OFFSET);       //checking this is the last block

    free_heap(h);
    printf("~~~~~Passed Four myMallocs and myFree Middle Two\n");
}

void test_myFree_something_myFreed(){

    heap_ptr h = create_heap(500);
    myMalloc(h, 10); 
    myMalloc(h, 20);
    myMalloc(h, 50);
    myFree(h, 0);
    assert(h->free_head_offset == 0);
    assert(block_size(h, 0) == 6);
    assert(block_next_offset(h, 0) == 30);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);

    assert(myFree(h,0) == false);
    assert(h->free_head_offset == 0);
    assert(block_size(h, 0) == 6);
    free_heap(h);
    printf("~~~~~~~~Passed test myFree something already freed\n");
}

void test_myFree_no_myMalloc(){

    heap_ptr h = create_heap(500);
    assert(myFree(h,0) == false);
    assert(h->free_head_offset == 0);
    assert(block_size(h, 0) == 125);
    free_heap(h);
    printf("~~~~~~~~Passed test myFree No myMalloc\n");
}

void test_myFree_not_at_beginning(){

    heap_ptr h = create_heap(500);
    myMalloc(h, 50); 
    myMalloc(h, 10);
    myMalloc(h, 20);
    myFree(h,8);
    assert(h->free_head_offset == 8);
    assert(block_size(h, 8) == 8);
    assert(block_next_offset(h, 0) == 16);
    assert(block_prev_offset(h, 0) == NULL_OFFSET);
    free_heap(h);
    printf("~~~~~Passed myFree not at the beginning\n");

}

void run_all_heap_tests(){

//     test_heap_creation();

//     test_split_free_spot_once();
//     test_split_free_spot_twice();


//     test_single_myMalloc();
//     test_two_myMalloc();
//     test_three_myMallocs();
// //    test_thing_too_big_insertion();
// //   test_heap_full_insertion();
// //    test_memory_almost_full_too_big_insertion();
// //   test_fill_heap_completely();

//     test_single_myMalloc_and_single_myFree();
//     test_three_myMallocs_and_myFree_first();
//     test_three_myMallocs_myFree_first_and_myMalloc_in_first();
//     test_three_myMallocs_and_myFree_second();
//     test_three_myMallocs_myFree_second_and_myMalloc_in_second();
//     test_three_myMallocs_and_myFree_third();
//     test_three_myMallocs_myFree_second_and_myMalloc_not_fit();
//     test_four_myMallocs_and_myFree_middle_two();

    // Freeing a Free or an Empty
    test_myFree_something_myFreed();
    test_myFree_no_myMalloc();
    test_myFree_not_at_beginning();    
}
