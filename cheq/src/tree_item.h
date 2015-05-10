/*
 * Created by andre on 5/10/15.
 */

#include "client.h"

#ifndef TREE_ITEM_H
#define TREE_ITEM_H

typedef Client TreeItem;
typedef long TreeItemKey;

TreeItem *tree_item_nil();

long tree_item_compare(TreeItemKey, TreeItemKey);

long tree_item_key(TreeItem);

void tree_item_print(TreeItem);

void tree_item_destroy(TreeItem);

#endif
