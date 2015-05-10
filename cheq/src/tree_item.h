#pragma once
#include "includes.h"
#include "client.h"

typedef Client TreeItem;
typedef long TreeItemKey;

TreeItem *tree_item_nil();

long tree_item_compare(TreeItemKey, TreeItemKey);

long tree_item_key(TreeItem);

void tree_item_print(TreeItem);

void tree_item_destroy(TreeItem);
