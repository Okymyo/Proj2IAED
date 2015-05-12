#pragma once
#include "includes.h"
#include "cheque.h"

typedef Cheque TableItem;
typedef unsigned long TableItemKey;

/*
* EMPTY
* @param  itemKey
* @param  EMPTY
* @return EMPTY
*/
unsigned int table_item_hash(TableItemKey itemKey);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
TableItem *table_item_nil();

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void table_item_destroy(TableItem *item);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
TableItemKey table_item_key(TableItem item);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void table_item_print(TableItem item);