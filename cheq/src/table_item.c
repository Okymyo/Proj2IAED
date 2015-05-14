#include "table_item.h"
#include "cheque.h"

#define MAGICCONSTANT 0x45d9f3b

unsigned int table_item_hash(TableItemKey itemKey){
	unsigned int hash;
	
	/* Explicit data-loss if item.reference > 2^32
	This is acceptable because this is a hash, we just need a good hash */
	hash = (unsigned int)itemKey;
	
	/* Shift right by 16 bits, to the power of itself (prior to shift), and multiply by the magic constant. 
	Repeat this step three times, but on the third don't multiply by the magic constant. */
	hash = ((hash >> 16) ^ hash) * MAGICCONSTANT;
    hash = ((hash >> 16) ^ hash) * MAGICCONSTANT;
    hash = ((hash >> 16) ^ hash);
	return hash;
}

TableItem table_item_nil(){
	return cheque_nil();
}

void table_item_destroy(TableItem *itemPtr){
}

TableItemKey table_item_key(TableItem item){
	return item.reference;
}