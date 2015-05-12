#include "table.h"

#define EXPANDTHRESHOLD 0.7	/* If table gets over 70% full, expand it */
#define SHRINKTHRESHOLD 0.2	/* If table is less than 20% full, shrink it */
#define EXPAND 2			/* If we're expanding, we duplicate the size. MUST remain power of two! */
#define SHRINK 0.5			/* If we're shrinking, halve the size. MUST remain power of two! */

TableRow table_row_init(TableItem *item, TableItemKey next, TableItemKey previous){
	TableRow row;
	row.item = item;
	row.next = next;
	row.prev = previous;
	return row;
}

TableRow table_row_nil(){
	TableRow row;
	row.item = table_item_nil();
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

void table_insert(Table *table, TableItem *item){
	TableItemKey key, temp, collision = 0;
	TableRow row;

	if (table->count >= table->size*EXPANDTHRESHOLD)
		table_resize(table, EXPAND);
		
	/* Calculate the key for this item */
	key = table_item_hash(item) % table->size;
	
	temp = key;
	
	/* We know we have free space, and our incrementing function (i^2 + i) always succeeds */
	while (table->data[key].item != table_item_nil()){
		collision++;
		key = (temp + (collision*collision + collision)/2) % table->size;
	}
	
	/* Initialize a row with TableItem item, and with the previously last element */
	if (table->count > 0)
		row = table_row_init(item, key, table->data[table->first].prev);
	else
		row = table_row_init(item, key, key);
	
	table->data[key] = row;
	if (table->count > 0){
		table->data[table->data[table->first].prev].next = key;
		table->data[table->first].prev = key;
	}
	else{
		table->first = key;
	}
	
	table->count++;
}

void table_remove(Table *table, TableItem *item){
	TableItemKey key;

	/* Find the item in the table */
	key = table_search(table, item);
	
	printf("Removing row %u\n", key);
	
	/* If the record we just deleted was the first in queue, update what the first in queue is
	Also update the new first in queue so that its "prev" is the last element. */
	if (table->first == key){
		table->first = table->data[key].next;
		table->data[table->data[key].next].prev = table->data[key].prev;
	}
	/* If the record we deleted wasn't the first one, update the previous and next records
	so that they point to eachother with "next" and "prev" respectively. */
	else{
		table->data[table->data[key].prev].next = table->data[key].next;
		table->data[table->data[key].next].prev = table->data[key].prev;
	}
		
	table->data[key].item = table_item_nil();

	if (table->count <= table->size*SHRINKTHRESHOLD)
		table_resize(table, SHRINK);
}

void table_resize(Table *table, float resize){
	TableItemKey old_size, old_first, i;
	TableRow *old_data;
	
	old_size = table->size;
	old_first = table->first;
	old_data = table->data;
	
	if (old_size > 0)
		table->size = (TableItemKey)(old_size*resize);
	else
		table->size = 2;
		
	table->data = malloc(sizeof(TableRow)*table->size);
	
	table->count = 0;
	
	for (i = 0; i < table->size; i++){
		table->data[i].item = table_item_nil();
	}
	
	if (old_size > 0){
		for (i = old_first;; i = old_data[i].next){
			table_insert(table, old_data[i].item);			
			/* If we just added our terminator, finish! */
			if (i == old_data[i].next)
				break;
		}
	}
		
	free(old_data);
}

void table_print(Table *table){
	TableItemKey i;
	printf("First row:%u\n", table->first);
	for (i = 0; i < table->size; i++){
		if (table->data[i].item != table_item_nil())
			printf("Row:%u     DATA[!]:%u      Pointer:%p     Next:%u     Prev:%u\n", i, table->data[i].item->reference, (void*)table->data[i].item, table->data[i].next, table->data[i].prev);
	}
}

TableItemKey table_search(Table *table, TableItem *item){
	TableItemKey key, temp, collision = 0;
		
	/* Calculate the key for this item */
	key = table_item_hash(item) % table->size;
	
	temp = key;
	/* We know we have free space, and our incrementing function (i^2 + i) always succeeds */
	while (!table_item_equal(table->data[key].item, item)){
		collision++;
		key = (temp + (collision*collision + collision)/2) % table->size;
	}
	
	/* This should never happen. So, if it does, we return an impossible value (will Segmentation Fault if unhandled!) */
	if (table->data[key].item == table_item_nil())
		return table->size;
	
	return key;
}

void table_destroy(Table *table){
	TableItemKey i;
	for (i = 0; i < table->size; i++){
		if (table->data[i].item != table_item_nil())
			table_item_destroy(table->data[i].item);
	}
	free(table->data);
	free(table);
}