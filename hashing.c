#include "hashing.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 * this c file is for implementing the functions on which we are going to use for the
 * rest of the project. Imagine that this is where all methods are written after we write the 
 * main method in java. It's just written in another file to keep the runner file clean
 * 
 */ 
hash_table_ptr create_table( int size)
{
 	//creating the record table 
	hash_table_ptr table_ptr = (hash_table_ptr)malloc(sizeof(struct hash_table_strc));

	// creating the entrys for the table, singularly
	struct hash_table_entry_strc my_entry;

	table_ptr->fp = fopen("hashtable.bin", "w+");
	//allocating the memory for the table and it's entry
	for(int i = 0; i < size; i++){
		my_entry.p_id = 0;
		my_entry.blank_fill = 0;
		my_entry.deleted = true;
		fwrite(&my_entry, sizeof(struct hash_table_entry_strc), 1, table_ptr->fp);
	}

	table_ptr->size = size;
	return table_ptr;
 
}
/*
 * Always remember to free your allocated data
 */
void free_table( struct hash_table_strc *table){

	fclose(table->fp);
	free(table);
}

int hashFunction1( struct hash_table_strc *table, int p_id){

	return (p_id % (table->size));

}

int hashFunction2( struct hash_table_strc *table, int p_id){

	return (1 + ((p_id >> 4) % (table->size)));
}


//should take product id run it through the hash fucntion give it its value and input it
bool insert_product(struct hash_table_strc *table, int p_id)
{
	struct hash_table_entry_strc my_entry;
	int hash1 = hashFunction1(table, p_id);
	int hash2 = hashFunction2(table, p_id);
	int position = hash1;
	int count = 0;
	
	// read file contents till end of file 
	//still manipulates postion and count checking for an entry with right size.
	do{
		read(table, position, &my_entry);
		if((count <= table->size) && (my_entry.deleted == false)){
        position = (position + hash2) % table->size;
		count++;
		}
	}while((count <= table->size) && (my_entry.deleted == false));


	// while ((count <= table->size) && (!table->data[position].deleted)){
	// 	position = (position + hash2) % table->size;
	// 	count++;
	// }
	printf("inserting into position %d with count %d and item # %d\n", position, count, p_id);
	if (count <= table->size) {

		my_entry.p_id = p_id;
		my_entry.blank_fill = 0;
		my_entry.deleted = false;
		write(table, position, &my_entry);
		return true;
	}

	return false;
	//should take product id run it through the hash fucntion give it its value and input it
}
bool retrieve_product(struct hash_table_strc *table, int p_id)
{
	struct hash_table_entry_strc my_entry;
	int hash1 = hashFunction1(table, p_id);
	int hash2 = hashFunction2(table, p_id);
	int position = hash1;
	int count = 0;
	do{
		read(table, position, &my_entry);
		if((count <= table->size) && (!my_entry.p_id == p_id)){
        position = (position + hash2) % table->size;
		count++;
		}else{
			break;
		}
	}while((count <= table->size) && (my_entry.deleted == false));

	if (count <= table->size) {
		read(table, position, &my_entry);
		if( my_entry.p_id == p_id){
			printf("product %d is there at %d\n", p_id, position);
			return true;
		}else{
			printf("The product isn't here\n");
		return false;
		}
	}else {
		printf("The product isn't here\n");
		return false;
	}
	
	// is this linked with an option to delete the product or is that a search on it's own
	//print out the id
	// printf("We inserted something at %d\n", table->entry.p_id);
}
bool delete_product(struct hash_table_strc *table, int p_id)
{	
	struct hash_table_entry_strc my_entry;
	int hash1 = hashFunction1(table, p_id);
	int hash2 = hashFunction2(table, p_id);
	int position = hash1;
	int count = 0;
	do{
		read(table, position, &my_entry);
		if((count <= table->size) && (my_entry.p_id != p_id)){
        position = (position + hash2) % table->size;
		count++;
		}else{
			break;
		}
	}while((count <= table->size) && (my_entry.deleted == false));

	if (count <= table->size) {
		read(table, position, &my_entry);
		if( my_entry.p_id == p_id){
			my_entry.deleted = true;
			write(table, position, &my_entry);
			return true;
		}else{
			printf("The product isn't here anyway.\n");
		return true;
		}
	}else {
		printf("The product isn't here\n");
		return false;
	}

}

void read(hash_table_ptr table, int index, struct hash_table_entry_strc *entry_strc )
{
	fseek(table->fp, index*(sizeof (struct hash_table_entry_strc)), SEEK_SET);
	fread(entry_strc, sizeof(struct hash_table_entry_strc), 1, table->fp);
}


void write(hash_table_ptr table, int index, struct hash_table_entry_strc *entry_strc)
{
	fseek(table->fp, index*(sizeof (struct hash_table_entry_strc)), SEEK_SET);
	fwrite(entry_strc, sizeof(struct hash_table_entry_strc), 1, table->fp);

}


//File pointer, and a read or write permission, and error if it can't open the file


//   1  address of data to be written in the disk
//   2  size of data to be written in the disk
//   3  number of such type of data
//   4  pointer to the file where you want to write.

// fwrite(addressData, sizeData, numbersData, pointerToFile);
