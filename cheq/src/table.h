#pragma once
#include "includes.h"
#include "table_item.h"

typedef struct {
    TableItem *itemPtr;
    TableItemKey prev, next;
} TableRow;

typedef struct {
    TableItemKey first;
	TableItemKey count, size;
	TableRow *data;
} Table;

Table *table_init();

void table_insert_pointer(Table *table, TableItem *itemPtr);

void table_resize(Table *table, float resize);

TableRow table_row_init(TableItem *itemPtr, TableItemKey next, TableItemKey previous);

void table_print(Table *table);

TableItemKey table_search(Table *table, TableSearchItem item);

void table_destroy(Table *table);

void table_unqueue(Table *table);

void table_remove(Table *table, TableSearchItem item);