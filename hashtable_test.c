#include "hashing.h"
#include "hashtable_test.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>



void test_table_creation(){

    hash_table_ptr my_table = create_table(13);
    assert(my_table->size == 13);
    free_table(my_table);
    printf("Test Table Passed\n");
}

void test_simple_insertion()
{

    hash_table_ptr my_table = create_table(13);
    struct hash_table_entry_strc entry;
    assert(insert_product(my_table, 15));   
   
    read(my_table, 2, &entry);
    printf("%x %x\n", entry.p_id, entry.blank_fill);
    assert(entry.p_id == 15);
    assert(entry.deleted == false);
    free_table(my_table);
    printf("Simple Insert Passed\n");
}


void test_two_simple_insertions()
{

    hash_table_ptr my_table = create_table(13);
    struct hash_table_entry_strc entry; 
    
    assert(insert_product(my_table, 15));
    assert(insert_product(my_table, 20));

    read(my_table, 2, &entry);
    assert(entry.p_id == 15);
    assert(entry.deleted == false);

    read(my_table, 7, &entry);
    assert(entry.p_id == 20);
    assert(entry.deleted == false);
    free_table(my_table);
    printf("Two Simple Instructions Passed\n");
}

void test_one_collision()
{

    hash_table_ptr my_table = create_table(13);
    struct hash_table_entry_strc entry;
    assert(insert_product(my_table, 15));

    read(my_table, 2, &entry);
    assert(entry.p_id == 15);
    assert(entry.deleted == false);

    assert(insert_product(my_table, 28));
    read(my_table, 4, &entry);
    assert(entry.p_id == 28);
    assert(entry.deleted == false);
    free_table(my_table);
    printf("Testing One Collisoin passed\n");
}

void test_two_collision()
{

    hash_table_ptr my_table = create_table(13);
    struct hash_table_entry_strc entry;
    assert(insert_product(my_table, 15));
    read(my_table, 2, &entry);
    assert(entry.p_id == 15); //2
    assert(entry.deleted == false);
    assert(insert_product(my_table, 28));

    read(my_table, 4, &entry);
    assert(entry.p_id == 28);
    assert(entry.deleted == false);

    assert(insert_product(my_table, 41));
    read(my_table, 5, &entry);
    assert(entry.p_id == 41);
    assert(entry.deleted == false);
    free_table(my_table);
    printf("Testing Two Collisions passed\n");
}

void test_simple_retrieval(){
    

    hash_table_ptr my_table = create_table(13);
    struct hash_table_entry_strc entry;
    assert(insert_product(my_table, 15));
    assert(retrieve_product(my_table, 15));

    free_table(my_table);
    printf("Passed Simple Retrieval\n");
    
}

void test_retrieve_after_collision(){


    hash_table_ptr my_table = create_table(13);
    struct  hash_table_entry_strc entry;

    assert(insert_product(my_table, 15));
    assert(insert_product(my_table, 28));
    read(my_table, 2, &entry);
    assert(entry.p_id == 15);
    assert(entry.deleted == false);
    read(my_table, 4, &entry);
    assert(entry.p_id == 28);
    assert(entry.deleted == false);
    assert(retrieve_product(my_table, 15));
    free_table(my_table);
    printf("Passsed Retrieve After Collision\n");
}

void test_retrieve_not_there(){

    hash_table_ptr my_table = create_table(13);
    assert(insert_product(my_table, 15));
    assert(retrieve_product(my_table, 20) == false);
    free_table(my_table);
    printf("Passed Retrieve not there\n");
}

void test_retrieve_not_there_with_collision(){


    hash_table_ptr my_table = create_table(13);
    struct hash_table_entry_strc entry;
    assert(insert_product(my_table, 15));
    assert(insert_product(my_table, 28));
    read(my_table, 2, &entry);
    assert(entry.p_id == 15);
    assert(entry.deleted == false);
    
    read(my_table, 4, &entry);
    assert(entry.p_id == 28);
    assert(entry.deleted == false);
    //retrieval not there
    assert(retrieve_product(my_table, 20) == false);
    free_table(my_table);
    printf("Passed Retrieval Not There With Collision\n");
}

void test_table_full_without_collisions(){

    hash_table_ptr my_table = create_table(13);
    assert(insert_product(my_table, 1));
    assert(insert_product(my_table, 2));
    assert(insert_product(my_table, 3));
    assert(insert_product(my_table, 4));
    assert(insert_product(my_table, 5));
    assert(insert_product(my_table, 6));
    assert(insert_product(my_table, 7));
    assert(insert_product(my_table, 8));
    assert(insert_product(my_table, 8));
    assert(insert_product(my_table, 10));
    assert(insert_product(my_table, 11));
    assert(insert_product(my_table, 12));
    assert(insert_product(my_table, 13));
    free_table(my_table);
    printf("Passing Full Table With No Collisions\n");

}

void test_table_full_with_collisions(){

    hash_table_ptr my_table = create_table(13);
    assert(insert_product(my_table, 1));
    assert(insert_product(my_table, 2));
    assert(insert_product(my_table, 3));
    assert(insert_product(my_table, 15));
    assert(insert_product(my_table, 5));
    assert(insert_product(my_table, 6));
    assert(insert_product(my_table, 7));
    assert(insert_product(my_table, 8));
    assert(insert_product(my_table, 8));
    assert(insert_product(my_table, 23));
    assert(insert_product(my_table, 11));
    assert(insert_product(my_table, 12));
    assert(insert_product(my_table, 13));
    free_table(my_table);   
    printf("Passing Testing Full Table With COllision\n");
}

void test_retrieve_table_full(){
	
    hash_table_ptr my_table = create_table(13);
    assert(insert_product(my_table, 1));
    assert(insert_product(my_table, 2));
    assert(insert_product(my_table, 3));
    assert(insert_product(my_table, 4));
    assert(insert_product(my_table, 5));
    assert(insert_product(my_table, 6));
    assert(insert_product(my_table, 7));
    assert(insert_product(my_table, 8));
    assert(insert_product(my_table, 8));
    assert(insert_product(my_table, 10));
    assert(insert_product(my_table, 11));
    assert(insert_product(my_table, 12));
    assert(insert_product(my_table, 13));
    assert(retrieve_product(my_table, 2));
    assert(retrieve_product(my_table, 10));
    free_table(my_table);   
    printf("Passed Retrieve Table Full\n");

}

void test_retrieve_not_there_table_full(){


    hash_table_ptr my_table = create_table(13);
    assert(insert_product(my_table, 1));
    assert(insert_product(my_table, 2));
    assert(insert_product(my_table, 3));
    assert(insert_product(my_table, 4));
    assert(insert_product(my_table, 5));
    assert(insert_product(my_table, 6));
    assert(insert_product(my_table, 7));
    assert(insert_product(my_table, 8));
    assert(insert_product(my_table, 8));
    assert(insert_product(my_table, 10));
    assert(insert_product(my_table, 11));
    assert(insert_product(my_table, 12));
    assert(insert_product(my_table, 13));
    //checking the the piece that's not there.
    assert(retrieve_product(my_table, 20) == false);
    free_table(my_table);   
    printf("Passed Retireve Not There and The Table is Full\n");

}

void test_one_deleted(){

  
    hash_table_ptr my_table = create_table(13);
    struct hash_table_entry_strc entry;
    assert(insert_product(my_table, 15));
    assert(insert_product(my_table, 28));

    read(my_table, 2, &entry);
    assert(entry.p_id == 15);
    assert(entry.deleted == false);

    read(my_table, 4, &entry);
    assert(entry.p_id == 28);
    assert(entry.deleted == false);
    assert(delete_product(my_table, 28));
    read(my_table, 4, &entry);
    assert(entry.p_id == 28);
    assert(entry.deleted == true);
    free_table(my_table);
    printf("PASSED DELETED!\n");
}

void idk_makaylies_tests(){

   
    hash_table_ptr table = create_table(13);
	assert(table->size == 13);
	printf("The Table Size = %d\n", table->size);
	insert_product(table,42);
	insert_product(table,33);
	insert_product(table,34);
	insert_product(table,39);
	insert_product(table,39);
	printf("We did it again!\n");
	printf("Third Times The Charm!\n");
	printf("Did it work?\n");

	retrieve_product(table,42);
	free_table(table);
    printf("!!Finished testing HashTable!! WooHoo!\n");
}




void run_all_hash_table_tests(){

    test_table_creation();

    test_simple_insertion();
    test_two_simple_insertions();
    test_one_collision();
    test_two_collision();
    test_table_full_without_collisions();
    test_table_full_with_collisions();

    test_simple_retrieval();
    test_retrieve_after_collision();
    test_retrieve_not_there();
    test_retrieve_not_there_with_collision();
    test_retrieve_table_full();
    test_retrieve_not_there_table_full();
    
    test_one_deleted();

    idk_makaylies_tests();
}
