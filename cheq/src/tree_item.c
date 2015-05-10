#include "tree_item.h"

TreeItem *tree_item_nil() {
    return client_nil();
}

long tree_item_compare(TreeItemKey key, TreeItemKey key2) {
    return client_compare(key, key2);
}

long tree_item_key(TreeItem item) {
    return client_key(item);
}

void tree_item_print(TreeItem item) {
    client_print(item);
}

void tree_item_destroy(TreeItem item) {
}