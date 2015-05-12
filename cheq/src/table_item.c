#include "table_item.h"

#define MAGICCONSTANT 0x45d9f3b

TableItemKey table_item_hash(TableItem item){
	TableItemKey hash;
	
	/* Explicit data-loss if item.reference > 2^31 - 1
	This is acceptable because this is a hash, we just need a good hash */
	hash = (TableItemKey)item->reference;
	
	/* Shift right by 16 bits, to the power of itself (prior to shift), and multiply by the magic constant. 
	Repeat this step three times, but on the third don't multiply by the magic constant. */
	hash = ((hash >> 16) ^ hash) * MAGICCONSTANT;
    hash = ((hash >> 16) ^ hash) * MAGICCONSTANT;
    hash = ((hash >> 16) ^ hash);
	return hash;
}

TableItem table_item_nil(){
	return NULL;
}