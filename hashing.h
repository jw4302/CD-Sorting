#include <stdbool.h>
#include <stdio.h>
/*
 *Header file establishes prototypes for types and functions
 */ 

//hash_table_entry_strc holds product_id which will be put into the hash table;
//also hold deleted which will come back true or false to whether an entry has been marked as 'deleted'
typedef struct hash_table_entry_strc{
	int p_id;
	union {
		bool deleted;
		int blank_fill;
	};

}entry, *entry_ptr;

typedef struct hash_table_strc{
	FILE *fp;
	int size;
}table, *hash_table_ptr;



//prototype that points to hash_table_strc;
//the goal of this prototype is to assign the size of the table
hash_table_ptr create_table( int size);
void free_table(struct hash_table_strc *table);
int hashFunction1(struct hash_table_strc *table, int p_id);
int hashFunction2(struct hash_table_strc *table, int p_id);
//prototype that will come back true or false;
//struct hash_table_strc table and int p_id are the parameters for the function
bool insert_product(struct hash_table_strc *table, int p_id);
bool retrieve_product(struct hash_table_strc *table, int p_id);
bool delete_product(struct hash_table_strc *table, int p_id);
void read(hash_table_ptr table, int index, struct hash_table_entry_strc *entry_strc);
void write(hash_table_ptr table, int index, struct hash_table_entry_strc *entry_strc);

