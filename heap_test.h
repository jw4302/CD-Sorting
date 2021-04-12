/*
 * Heap Tests
 */
void run_all_heap_tests();
void test_heap_creation();
void test_split_free_spot_once();
void test_split_free_spot_twice();

/*
 * MyMalloc Tests
 */
void test_single_myMalloc();
void test_two_myMalloc();
void test_three_myMallocs();
void test_thing_too_big_insertion();
void test_heap_full_insertion();
void test_memory_almost_full_too_big_insertion();
void test_fill_heap_completely();

/*
 * MyFree Tests
 */
void test_single_myMalloc_and_single_myFree();
void test_three_myMallocs_and_myFree_first();
void test_three_myMallocs_myFree_first_and_myMalloc_in_first();
void test_three_myMallocs_and_myFree_second();
void test_three_myMallocs_myFree_second_and_myMalloc_in_second();
void test_three_myMallocs_and_myFree_third();
void test_three_myMallocs_myFree_second_and_myMalloc_not_fit();
void test_four_myMallocs_and_myFree_middle_two();
void test_myFree_something_myFreed();
void test_myFree_no_myMalloc();
void test_myFree_not_at_beginning();