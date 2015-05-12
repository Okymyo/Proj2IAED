#include "table.h"

#define EXPANDTHRESHOLD 0.7	/* If table gets over 70% full, expand it */
#define SHRINKTHRESHOLD 0.2	/* If table is less than 20% full, shrink it */
#define EXPAND 2			/* If we're expanding, we duplicate the size. MUST remain power of two! */
#define SHRINK 0.5			/* If we're shrinking, halve the size. MUST remain power of two! */

TableRow table_row_init(TableItem *itemPtr, unsigned int next, unsigned int previous){
	TableRow row;
	row.itemPtr = itemPtr;
	row.next = next;
	row.prev = previous;
	return row;
}

TableRow table_row_nil(){
	TableRow row;
	row.itemPtr = table_item_nil();
	row.next = 0;
	row.prev = 0;
	return row;
}

Table *table_init(){
	Table *table = malloc(sizeof(Table));
	table->first = 0;
	table->count = 0;
	table->size = 0;
	table->data = NULL;
	return table;
}

void table_insert(Table *table, TableItem item){
	TableItem *itemPtr = malloc(sizeof(TableItem));
	*itemPtr = item;
	table_insert_pointer(table, itemPtr);
}

void table_insert_pointer(Table *table, TableItem *itemPtr){
	unsigned int index, temp, collision = 0;
	TableRow row;

	/* If our table is too full, expand it */
	if (table->count >= table->size*EXPANDTHRESHOLD)
		table_resize(table, EXPAND);
		
	/* Calculate the index for this item */
	index = table_item_hash(table_item_key(*itemPtr)) % table->size;
	
	temp = index;
	
	/* We know we have free space, and our incrementing function (i^2 + i) always succeeds */
	while (table->data[index].itemPtr != table_item_nil()){
		collision++;
		index = (temp + (collision*collision + collision)/2) % table->size;
	}
	
	/* Initialize a row with TableItem item, and with the previously last element */
	if (table->count > 0)
		row = table_row_init(itemPtr, index, table->data[table->first].prev);
	else
		row = table_row_init(itemPtr, index, index);
	
	table->data[index] = row;
	if (table->count > 0){
		table->data[table->data[table->first].prev].next = index;
		table->data[table->first].prev = index;
	}
	else{
		table->first = index;
	}
	
	table->count++;
}

void table_unqueue(Table *table){
	table_remove(table, table_item_key(*table->data[table->first].itemPtr));
}

void table_remove(Table *table, TableItemKey item){
	unsigned int index;

	/* Find the item in the table */
	index = table_search(table, item);
	
	/* If table search just returned our error value, stop */
	if (index == table->size)
		return;
	
	/* If the record we just deleted was the first in queue, update what the first in queue is
	Also update the new first in queue so that its "prev" is the last element. */
	if (table->first == index){
		table->first = table->data[index].next;
		table->data[table->data[index].next].prev = table->data[index].prev;
	}
	/* If the record we deleted wasn't the first one, update the previous and next records
	so that they point to eachother with "next" and "prev" respectively. */
	else{
		table->data[table->data[index].prev].next = table->data[index].next;
		table->data[table->data[index].next].prev = table->data[index].prev;
	}
		
	table_item_destroy(table->data[index].itemPtr);
	free(table->data[index].itemPtr);
	table->data[index].itemPtr = table_item_nil();
	table->count--;

	if (table->count <= table->size*SHRINKTHRESHOLD)
		table_resize(table, SHRINK);
}

void table_resize(Table *table, float resize){
	unsigned int old_size, old_first, i;
	TableRow *old_data;
	
	old_size = table->size;
	old_first = table->first;
	old_data = table->data;
	
	if (old_size > 0)
		table->size = (unsigned int)(old_size*resize);
	else
		table->size = 2;
		
	table->data = malloc(sizeof(TableRow)*table->size);
	
	table->count = 0;
	
	for (i = 0; i < table->size; i++){
		table->data[i].itemPtr = table_item_nil();
	}
	
	if (old_size > 0){
		for (i = old_first;; i = old_data[i].next){
			table_insert_pointer(table, old_data[i].itemPtr);			
			/* If we just added our terminator, finish! */
			if (i == old_data[i].next)
				break;
		}
	}
		
	free(old_data);
}

void table_print(Table *table){
	unsigned int i;
	printf("First row:%u\n", table->first);
	for (i = 0; i < table->size; i++){
		if (table->data[i].itemPtr != table_item_nil())
			table_item_print(*table->data[i].itemPtr);
	}
}

unsigned int table_search(Table *table, TableItemKey item){
	unsigned int index, temp, collision = 0;
		
	/* Calculate the index for this item */
	index = table_item_hash(item) % table->size;
	
	temp = index;
	/* We know we have free space, and our incrementing function (i^2 + i) always succeeds */
	while (table->data[index].itemPtr != NULL && table_item_key(*table->data[index].itemPtr) != item){
		collision++;
		index = (temp + (collision*collision + collision)/2) % table->size;
	}
	
	/* This should never happen. So, if it does, we return an impossible value (will Segmentation Fault if unhandled!) */
	if (table->data[index].itemPtr == NULL)
		return table->size;
	
	return index;
}

void table_destroy(Table *table){
	unsigned int i;
	for (i = 0; i < table->size; i++){
		if (table->data[i].itemPtr != table_item_nil()){
			table_item_destroy(table->data[i].itemPtr);
			free(table->data[i].itemPtr);
		}
	}
	free(table->data);
	free(table);
}