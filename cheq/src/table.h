#pragma once
#include "includes.h"
#include "table_item.h"

typedef struct {
    TableItem *item;
    TableItemKey prev, next;
} TableRow;

typedef struct {
    TableItemKey first;
	TableItemKey count, size;
	TableRow *data;
} Table;

Table *table_init();

void table_resize(Table *table, float resize);

TableRow table_row_init(TableItem *item, TableItemKey next, TableItemKey previous);

void table_print(Table *table);

TableItemKey table_search(Table *table, TableItem *item);

void table_destroy(Table *table);