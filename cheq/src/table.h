#pragma once
#include "includes.h"
#include "table_item.h"

typedef struct {
    TableItem item;
    int prev, next;
} TableRow;

typedef struct {
    int first;
	int count, size;
	TableRow *data;
} Table;