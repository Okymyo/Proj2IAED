#pragma once
#include "includes.h"
#include "cheque.h"

typedef Cheque TableItem;
typedef unsigned int TableItemKey;
typedef long TableSearchItem;

TableItemKey table_item_hash(TableSearchItem item);

TableItem *table_item_nil();

void table_item_print(TableItem *item);

void table_item_destroy(TableItem *item);

TableSearchItem table_search_item(TableItem item);