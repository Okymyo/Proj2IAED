/* =====================
 * Grupo 5, IAED, LEIC-T
 * 81900 - Nuno Anselmo
 * 81943 - Gonçalo Matos
 * 82047 - André Mendes
   ===================== */

#include "tree_item.h"

int tree_item_compare(TreeItemKey itemKey1, TreeItemKey itemKey2) {
    return client_compare(itemKey1, itemKey2);
}

TreeItemKey tree_item_key(TreeItem treeItem) {
    return client_key(&treeItem);
}

void tree_item_print(TreeItem treeItem) {
    client_print(&treeItem, "*");
}

void tree_item_destroy(TreeItem treeItem) {
}