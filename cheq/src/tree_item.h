#pragma once
#include "includes.h"
#include "client.h"

/*
* Our TreeItem is going to be a Client.
*/
typedef Client TreeItem;

/*
* Our TreeItemKey is going to be a ClientKey, defined in client.h.
*/
typedef ClientKey TreeItemKey;

/*
* Compares two item keys.
* @param itemKey1 First key of the first item that we want to compare.
* @param itemKey2 Second key of the second item that we want to compare.
* @return         Returns > 0, if itemKey1 is bigger than itemKey2, < 0 if itemKey1 is less than itemKey2, == 0 if both keys are the same.
*/
int tree_item_compare(TreeItemKey itemKey1, TreeItemKey itemKey2);

/*
* Gives the key of a given item.
* @param treeItem Item that we want to obtain the key.
* @return         The key of the item.
*/
TreeItemKey tree_item_key(TreeItem treeItem);

/*
* Prints a given item.
* @param treeItem Item that we want to print.
*/
void tree_item_print(TreeItem treeItem);

/*
* Destroys/frees a given item.
* @param treeItem Item to destroy/free.
*/
void tree_item_destroy(TreeItem treeItem);
