/* =====================
 * Grupo 5, IAED, LEIC-T
 * 81900 - Nuno Anselmo
 * 81943 - Gonçalo Matos
 * 82047 - André Mendes
   ===================== */

#include "table.h"

#define EXPANDTHRESHOLD 0.7    /* If table gets over 70% full, expand it */
#define SHRINKTHRESHOLD 0.1    /* If table is less than 10% full, shrink it */
#define EXPAND 2               /* If we're expanding, we duplicate the size. MUST remain power of two! */
#define SHRINK 0.5             /* If we're shrinking, halve the size. MUST remain power of two! */
                               /* We require power of two for our incrementation function to go through
                               every record in the table. */

/* This is our incrementation function for collisions: (i*i + i)/2, which has perfect iteration
(goes through every row) through any hash table that is power of two in size */
#define increment(i) (i*i + i)/2

/* We dislike global variables as much as everyone else, but we need something to mean "grave".
Find more information about this under "TableItem *table_grave()" */
char grave;

/* ================================================================== */
/* TableRow methods */
/* ================================================================== */

TableRow table_row_init(TableItem *itemPtr, unsigned int next, unsigned int previous) {
    TableRow row;
    row.itemPtr = itemPtr;
    row.next = next;
    row.prev = previous;
    return row;
}

/* ================================================================== */
/* Table methods */
/* ================================================================== */

Table *table_init() {
    return (Table *) calloc(1, sizeof(Table));
}

TableItem *table_grave() {
    /* Initially we were returning a pointer to this own function as our "grave" pointer.
	However, we cannot do that under pedantic (can't convert from function pointer to object pointer).
	So, to get around that issue, we created a global variable, char grave, and we point to it.
	The alternative would be to have an additional field in our TableRow, "is_grave".
	That unfortunately increases our overhead more than this hack does, as it also forces
	us to initialize that field, and not only the pointers, slowing it down.
	return (TableItem *) &table_grave; */
	return (TableItem *) &grave;
}

void table_insert(Table *table, TableItem item) {
    TableItem *itemPtr = malloc(sizeof(TableItem));
    *itemPtr = item;
	
	/* Insert the pointer to this item into our table */
    table_insert_pointer(table, itemPtr);
}

void table_insert_pointer(Table *table, TableItem *itemPtr) {
    unsigned int index, temp, collision = 0;
    TableRow row;

    /* If our table is too full, expand it */
    if (table->count >= table->size * EXPANDTHRESHOLD)
        table_resize(table, EXPAND);

    /* Calculate the index for this item */
    index = table_item_hash(table_item_key(*itemPtr)) % table->size;

	/* Temporarily store our index for the incrementation function */
    temp = index;

    /* We know we have free space, and our incrementing function (i^2 + i) always succeeds.
    Once it finds a NULL or a grave, it stores it there */
    while (!table_item_ptr_nil(table->data[index].itemPtr)) {
        collision++;
        index = (temp + increment(collision)) % table->size;
    }

    /* Initialize a row with TableItem item, and with the previously last element */
    if (table->count > 0) {
        row = table_row_init(itemPtr, index, table->data[table->first].prev);
        table->data[table->data[table->first].prev].next = index;
        table->data[table->first].prev = index;
    }
	/* If we are inserting the first element, update the "first" value as well */
    else {
        row = table_row_init(itemPtr, index, index);
        table->first = index;
    }

    /* Store row into the table */
    table->data[index] = row;

    /* Increment our counter AFTER doing everything else.
    If we don't, we might cause issues as we expand the table. */
    table->count++;
}

TableItem table_unqueue(Table *table) {
    if (table->count == 0)
        return table_item_nil();

	/* If we have a first item, send it to our table_remove to be deleted */
    return table_remove(table, table_item_key(*table->data[table->first].itemPtr));
}

TableItem table_remove(Table *table, TableItemKey itemKey) {
    unsigned int index;
    TableItem destroy;

    /* Find the item in the table */
    index = table_search_row(table, itemKey);

    /* If table search just returned our error value, stop */
    if (index == table->size)
        return table_item_nil();

    /* If the record we just deleted was the first in queue, update what the first in queue is
    Also update the new first in queue so that its "prev" is the last element */
    if (table->first == index) {
        table->first = table->data[index].next;
        table->data[table->data[index].next].prev = table->data[index].prev;
    }
    /* If the record we just deleted was the last in queue, update the new last in queue so that
    its next is itself, and the first so that its previous is the new last */
    else if (table->data[table->first].prev == index) {
        table->data[table->data[index].prev].next = table->data[index].prev;
        table->data[table->first].prev = table->data[index].prev;
    }
    /* If the record we deleted wasn't the first one, and not the last one, update the previous
    and next records so that they point to eachother with "next" and "prev" respectively */
    else {
        table->data[table->data[index].prev].next = table->data[index].next;
        table->data[table->data[index].next].prev = table->data[index].prev;
    }

	/* Store the item we'll remove, for our return */
    destroy = *table->data[index].itemPtr;
	
	/* Remove the item and free all of the memory it uses */
    table_item_destroy(table->data[index].itemPtr);
    free(table->data[index].itemPtr);
	
	/* Place a grave where it used to be */
    table->data[index].itemPtr = table_grave();

    /* Decrement our counter BEFORE doing the resize.
    If we don't, we'll report incorrect sizes to table_resize */
    table->count--;

    /* If our table is too large, shrink it */
    if (table->count <= table->size * SHRINKTHRESHOLD)
        table_resize(table, SHRINK);

    return destroy;
}

unsigned int table_count(Table *table) {
    return table->count;
}

TableItem *table_search(Table *table, TableItemKey itemKey) {
    unsigned int index;

    /* Find the item in the table */
    index = table_search_row(table, itemKey);

    /* If table search just returned our error value, stop */
    if (index == table->size)
        return NULL;

	/* Returns a pointer to our TableItem, stored in the row given by index */
    return table->data[index].itemPtr;
}

unsigned int table_search_row(Table *table, TableItemKey itemKey) {
    unsigned int index, temp, collision = 0;

    if (table->size == 0)
        return table->size;

    /* Calculate the index for this item */
    index = table_item_hash(itemKey) % table->size;

	/* Temporarily store our index for the incrementation function */
    temp = index;
	
    /* We know we have free space, and our incrementing function (i^2 + i) always succeeds */
    while (collision < table->size && (table->data[index].itemPtr == table_grave() ||
                                       (table->data[index].itemPtr != NULL &&
                                        table_item_key(*table->data[index].itemPtr) != itemKey))) {
        collision++;
        index = (temp + increment(collision)) % table->size;
    }

    /* If we stopped searching because we went through every possible position or because
    we found a return our "nothing found" value */
    if (collision >= table->size || table_item_ptr_nil(table->data[index].itemPtr))
        return table->size;

    return index;
}

void table_resize(Table *table, float resize) {
    unsigned int old_size, old_first, i;
    TableRow *old_data;

	/* Store information about our table before expansion, to use when transferring data */
    old_size = table->size;
    old_first = table->first;
    old_data = table->data;

	/* Our multiplication factor can't get out of a size 0, or into size 0.
	To fix that, if we were shrinking to 0, we force size to 0, and if we are
	expanding from 0, we give it a little push to 8. */
    if (old_size >= 2 && table->count != 0)
        table->size = (unsigned int) (old_size * resize);
    else if (table->count == 0 && resize == SHRINK)
        table->size = 0;
    else
        table->size = 8;

	/* Allocate space for our new TableRows */
    table->data = malloc(sizeof(TableRow) * table->size);

	/* Change all the pointers to NULL (everything else will be initialized when used) */
    for (i = 0; i < table->size; i++) {
        table->data[i].itemPtr = NULL;
    }

    if (old_size > 0 && table->size > 0) {
        /* Reset our table count, which will be set correctly when re-adding elements */
        table->count = 0;
        for (i = old_first; ; i = old_data[i].next) {
            table_insert_pointer(table, old_data[i].itemPtr);
            /* If we just added our terminator, finish! */
            if (i == old_data[i].next)
                break;
        }
    }
	
	/* Deallocate the previous rows, since everything has been transferred over */
    free(old_data);
}

int table_item_ptr_nil(TableItem *itemPtr) {
	/* If our pointer is either NULL or a grave, we assume it is nil */
    return itemPtr == NULL || itemPtr == table_grave();
}

void table_destroy(Table *table) {
    unsigned int i;
	/* Go through our table and free every non-nil (NULL or grave) */
    for (i = 0; i < table->size; i++) {
        if (!table_item_ptr_nil(table->data[i].itemPtr)) {
            table_item_destroy(table->data[i].itemPtr);
            free(table->data[i].itemPtr);
        }
    }
	
	/* Free the table itself */
    free(table->data);
    free(table);
}
