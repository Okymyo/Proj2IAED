#include "table.h"

#define EXPANDTHRESHOLD 0.7	/* If table gets over 70% full, expand it */
#define SHRINKTHRESHOLD 0.2	/* If table is less than 20% full, shrink it */
#define EXPAND 2			/* If we're expanding, we duplicate the size. MUST remain power of two! */
#define SHRINK 0.5			/* If we're shrinking, halve the size. MUST remain power of two! */
							/* We require power of two for our incrementation function to go through
							   every record in the table. */

TableRow table_row_init(TableItem *itemPtr, unsigned int next, unsigned int previous){
	TableRow row;
	row.itemPtr = itemPtr;
	row.next = next;
	row.prev = previous;
	return row;
}

Table *table_init(){
	return (Table*)calloc(1, sizeof(Table));
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
	while (table->data[index].itemPtr != NULL){
		collision++;
		index = (temp + (collision*collision + collision)/2) % table->size;
	}
	
	/* Initialize a row with TableItem item, and with the previously last element */
	if (table->count > 0){
		row = table_row_init(itemPtr, index, table->data[table->first].prev);
		table->data[table->data[table->first].prev].next = index;
		table->data[table->first].prev = index;
	}
	else{
		row = table_row_init(itemPtr, index, index);
		table->first = index;
	}
	
	/* Store row into the table */
	table->data[index] = row;
	
	/* Increment our counter AFTER doing everything else.
	If we don't, we risk getting trapped in permanent expansion. */
	table->count++;
}

TableItem table_unqueue(Table *table){
	if (table->count == 0)
		return table_item_nil();
		
	return table_remove(table, table_item_key(*table->data[table->first].itemPtr));
}

TableItem table_remove(Table *table, TableItemKey itemKey){
	unsigned int index;
	TableItem destroy;

	/* Find the item in the table */
	index = table_search_row(table, itemKey);
	
	/* If table search just returned our error value, stop */
	if (index == table->size)
		return table_item_nil();
	
	/* If the record we just deleted was the first in queue, update what the first in queue is
	Also update the new first in queue so that its "prev" is the last element. */
	if (table->first == index){
		table->first = table->data[index].next;
		table->data[table->data[index].next].prev = table->data[index].prev;
	}
	/* If the record we just deleted was the last in queue, update the new last in queue so that
	its next is itself, and the first so that its previous is the new last */
	else if (table->data[table->first].prev == index) {
		table->data[table->data[index].prev].next = table->data[index].prev;
		table->data[table->first].prev = table->data[index].prev;
	}
	/* If the record we deleted wasn't the first one, and not the last one, update the previous
	and next records so that they point to eachother with "next" and "prev" respectively. */
	else {
		table->data[table->data[index].prev].next = table->data[index].next;
		table->data[table->data[index].next].prev = table->data[index].prev;
	}
	
	destroy = *table->data[index].itemPtr;		
	table_item_destroy(table->data[index].itemPtr);
	free(table->data[index].itemPtr);
	table->data[index].itemPtr = NULL;
	
	/* Decrement our counter BEFORE doing the resize.
	If we don't, we'll report incorrect sizes to table_resize */
	table->count--;
	
	/* If our table is too large, shrink it */
	if (table->count <= table->size*SHRINKTHRESHOLD)
		table_resize(table, SHRINK);
		
	return destroy;
}

void table_resize(Table *table, float resize){
	unsigned int old_size, old_first, i;
	TableRow *old_data;
	
	old_size = table->size;
	old_first = table->first;
	old_data = table->data;
	
	if (old_size >= 2 && resize == EXPAND)
		table->size = (unsigned int)(old_size*resize);
	else if (table->count == 0 && resize == SHRINK)
		table->size = 0;
	else
		table->size = 2;
		
	table->data = malloc(sizeof(TableRow)*table->size);
	
	for (i = 0; i < table->size; i++){
		table->data[i].itemPtr = NULL;
	}
	
	if (old_size > 0 && table->size > 0){
		/* Reset our table count, which will be set correctly when re-adding elements */
		table->count = 0;
		for (i = old_first;; i = old_data[i].next){
			table_insert_pointer(table, old_data[i].itemPtr);			
			/* If we just added our terminator, finish! */
			if (i == old_data[i].next)
				break;
		}
	}
		
	free(old_data);
}

unsigned int table_count(Table *table){
	return table->count;
}

/* DELETE!!!! */
void table_print(Table *table){
	unsigned int i;
	printf("First row:%u  Count:%u\n", table->first, table->count);
	for (i = 0; i < table->size; i++){
		if (table->data[i].itemPtr != NULL){
			printf("Row:%3u  Next:%3u  Previous:%3u\n", i, table->data[i].next, table->data[i].prev);
		}
	}
}

TableItem *table_search(Table *table, TableItemKey itemKey){
	unsigned int index;
	
	/* Find the item in the table */
	index = table_search_row(table, itemKey);
	
	/* If table search just returned our error value, stop */
	if (index == table->size)
		return NULL;
		
	return table->data[index].itemPtr;
}

unsigned int table_search_row(Table *table, TableItemKey itemKey){
	unsigned int index, temp, collision = 0;
		
	/* Calculate the index for this item */
	index = table_item_hash(itemKey) % table->size;
	
	temp = index;
	/* We know we have free space, and our incrementing function (i^2 + i) always succeeds */
	while (collision < table->size && (table->data[index].itemPtr == NULL || table_item_key(*table->data[index].itemPtr) != itemKey)){
		collision++;
		index = (temp + (collision*collision + collision)/2) % table->size;
	}
	
	/* If we stopped searching because we went through every possible position, return our "nothing found" value */
	if (collision >= table->size)
		return table->size;
	
	return index;
}

void table_destroy(Table *table){
	unsigned int i;
	for (i = 0; i < table->size; i++){
		if (table->data[i].itemPtr != NULL){
			table_item_destroy(table->data[i].itemPtr);
			free(table->data[i].itemPtr);
		}
	}
	free(table->data);
	free(table);
}