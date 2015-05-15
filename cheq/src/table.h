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
    unsigned int first, count, size;
    TableRow *data;
} Table;

/* ================================================================== */
/* TableRow methods */
/* ================================================================== */

/*
* Returns a TableRow that has been initialized with specific values.
* @param itemPtr  Pointer to the TableItem this row will store.
* @param next     Number of the next row in queue.
* @param previous Number of the previous row in queue.
* @return         TableRow that contains the values that were given.
*/
TableRow table_row_init(TableItem *itemPtr, unsigned int next, unsigned int previous);

/* ================================================================== */
/* Table methods */
/* ================================================================== */

/*
* Creates a new table.
* @return Returns a pointer to a structure of type Table.
*/
Table *table_init();

/*
* Returns the value to be used as a grave.
* @return Pointer that represents a grave.
*/
TableItem *table_grave();

/*
* Inserts a given TableItem into the table.
* @param table Table into which the item is being inserted.
* @param item  TableItem to insert into the table.
*/
void table_insert(Table *table, TableItem item);

/*
* Inserts a TableItem referenced by a pointer into the table.
* @param table   Table into which the item is being inserted.
* @param itemPtr Pointer for the TableItem we're inserting.
*/
void table_insert_pointer(Table *table, TableItem *itemPtr);

/*
* Removes the oldest element in the table.
* @param table Table from which we're removing the item.
* @return      TableItem that was removed.
*/
TableItem table_unqueue(Table *table);

/*
* Removes the TableItem with the given TableItemKey
* @param table   Table from which we're removing the item.
* @param itemKey TableItemKey of the item we're removing.
* @return        TableItem that was removed, table_item_nil() if non-existent.
*/
TableItem table_remove(Table *table, TableItemKey itemKey);

/*
* Returns the number of elements in a given table.
* @param table Table from which we're counting the elements.
* @return      Number of non-nil elements in the table.
*/
unsigned int table_count(Table *table);

/*
* Finds and returns a pointer to an item represented by a certain TableItemKey.
* @param table   Table in which we're searching for the itemKey.
* @param itemKey TableItemKey of the item we're searching for.
* @return        Pointer to the TableItem that was searched for, NULL if it wasn't found.
*/
TableItem *table_search(Table *table, TableItemKey itemKey);

/*
* Finds and returns the row number in which the item with a certain TableItemKey can be found.
* @param table   Table in which we're searching for the itemKey.
* @param itemKey TableItemKey of the item whose row we're searching for.
* @return        Row number of the item we were searching for, table's size if it wasn't found.
*/
unsigned int table_search_row(Table *table, TableItemKey itemKey);

/*
* Resizes our table, modifying its maximum size.
* @param table  Table that will be redimensioned.
* @param resize Factor by which we multiply our table size.
*/
void table_resize(Table *table, float resize);

/*
* Checks whether a given TableItem pointer is to be assumed as nil.
* @param itemPtr Pointer to the item to check.
* @return        Returns true if nil or grave, false otherwise.
*/
int table_item_ptr_nil(TableItem *itemPtr);

/*
* Deallocates all the resources in use by a certain Table.
* @param table Table which we are deallocating.
*/
void table_destroy(Table *table);
