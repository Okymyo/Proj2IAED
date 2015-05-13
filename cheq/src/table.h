#pragma once
#include "includes.h"
#include "table_item.h"

/*
* TableRow type is a structure that has three fields:
*  -> A pointer to the TableItem it's associated with.
*  -> An unsigned int that is the row number of the previous record in queue.
*  -> An unsigned int that is the row number of the next record in queue.
* Size: 16 bytes.
*/
typedef struct {
    TableItem *itemPtr;
    unsigned int prev, next;
} TableRow;

/*
* Table type is a structure that has four fields:
*  -> An unsigned int that is the row number of the first in queue.
*  -> An unsigned int that is the number of records in queue.
*  -> An unsigned int that is the current size of the table.
*  -> A pointer to the TableRows it is storing.
* Size: 20 bytes.
*/
typedef struct {
    unsigned int first;
	unsigned int count, size;
	TableRow *data;
} Table;

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
Table *table_init();

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void table_insert_pointer(Table *table, TableItem *itemPtr);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void table_resize(Table *table, float resize);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
TableRow table_row_init(TableItem *itemPtr, unsigned int next, unsigned int previous);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
unsigned int table_count(Table *table);

/* DELETE!!!!!! */
void table_print(Table *table);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
TableItem *table_search(Table *table, TableItemKey itemKey);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
unsigned int table_search_row(Table *table, TableItemKey itemKey);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void table_destroy(Table *table);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void table_unqueue(Table *table);

/*
* EMPTY
* @param  EMPTY
* @param  EMPTY
* @return EMPTY
*/
void table_remove(Table *table, TableItemKey itemKey);