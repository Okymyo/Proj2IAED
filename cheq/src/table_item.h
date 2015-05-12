#pragma once
#include "includes.h"
#include "cheque.h"

typedef Cheque TableItem;
typedef long TableItemKey;

unsigned int table_item_hash(TableItemKey item);

TableItem *table_item_nil();

void table_item_destroy(TableItem *item);

TableItemKey table_item_key(TableItem item);

void table_item_print(TableItem item);