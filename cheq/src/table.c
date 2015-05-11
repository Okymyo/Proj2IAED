#define EXPANDTHRESHOLD 0.8	/* If table gets over 70% full, expand it */
#define SHRINKTHRESHOLD 0.2	/* If table is less than 20% full, shrink it */
#define EXPAND 2			/* If we're expanding, we duplicate the size */
#define SHRINK 0.5			/* If we're shrinking, halve the size */

Table table_init(Table *table){
	table->first = -1
	table->count = 0;
	table->size = 0;
	table->data = NULL;
}

Table table_insert(Table *table, TableItem item){
	if(table->count > table->size*EXPANDTHRESHOLD)
		table_resize(table, EXPAND);
		
	/* Calculate the key for this item */
	key = table_item_key(item);
	
	/* Initialize a row with TableItem item, and with the previously last element  */
	row = row_init(item, table->data[table->next].prev);
	
	while (table->data[row.key].item != NULL){
		row.key++;
	}
	
	table->data[row.key]
	table->data[table->data[table->next].prev].next = row.key;
	table->data[table->next].prev = row.key;
	table->
}

Table table_remove(Table *table, TableItem item){
	/* Calculate the key for this item */
	key = table_item_key(item);
	
	
	table->data[table->data[key].prev].next = table->data[key].next;
	table->data[table->data[key].next].prev = table->data[key].prev;

	if(table->count < table->size*SHRINKTHRESHOLD)
		table_resize(table, SHRINK);
		
}

Table table_resize(Table *table, char operation){
	
}