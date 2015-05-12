#pragma once
#include "includes.h"
#include "table_item.h"

typedef struct {
    TableItem *itemPtr;
    unsigned int prev, next;
} TableRow;

typedef struct {
    unsigned int first;
	unsigned int count, size;
	TableRow *data;
} Table;

Table *table_init();

void table_insert_pointer(Table *table, TableItem *itemPtr);

void table_resize(Table *table, float resize);

TableRow table_row_init(TableItem *itemPtr, unsigned int next, unsigned int previous);

void table_print(Table *table);

unsigned int table_search(Table *table, TableItemKey item);

void table_destroy(Table *table);

void table_unqueue(Table *table);

void table_remove(Table *table, TableItemKey item);