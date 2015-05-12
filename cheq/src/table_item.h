#pragma once
#include "includes.h"
#include "cheque.h"

typedef Cheque TableItem;
typedef unsigned int TableItemKey;

TableItemKey table_item_hash(TableItem *item);

TableItem *table_item_nil();

void table_item_print(TableItem *item);

void table_item_destroy(TableItem *item);

int table_item_equal(TableItem *item1, TableItem *item2);