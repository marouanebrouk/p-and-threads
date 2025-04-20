#include "h.h"

void btree_apply_suffix(t_tree *root, void (*applyf)(void *))
{
    if (root = NULL)
        return;
    btree_apply_suffix(root->left,applyf);
    btree_apply_suffix(root->right,applyf);
    applyf(root->item);
}