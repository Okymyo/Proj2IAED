#pragma once
#include "includes.h"
#include "cheque.h"

typedef Cheque TableItem;
typedef unsigned long TableItemKey;

/*
* Hashes a given TableItemKey.
* @param itemKey TableItemKey to be hashed with our hashing function.
* @return        Resulting output from our hashing function.
*/
unsigned int table_item_hash(TableItemKey itemKey);

/*
* Returns the value to be indicator of a nil TableItem.
* @return TableItem we define as nil.
*/
TableItem table_item_nil();

/*
* Deallocate a given TableItem
* @param TableItem to be deallocated
*/
void table_item_destroy(TableItem *item);

/*
* Returns the TableItemKey matching a given TableItem.
* @param item TableItem whose key we're returning.
* @return     TableItemKey referring to the item.
*/
TableItemKey table_item_key(TableItem item);