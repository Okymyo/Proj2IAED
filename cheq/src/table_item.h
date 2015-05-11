#pragma once
#include "includes.h"
#include "cheque.h"

typedef Cheque *TableItem;
typedef unsigned int TableItemKey;

TableItemKey table_item_key(TableItem);

void table_item_print(TableItem);

void table_item_destroy(TableItem);