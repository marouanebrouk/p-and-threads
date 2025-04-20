#include "h.h"

void btree_apply_prefix(t_tree *root, void (*applyf)(void *))
{
    if (root = NULL)
        return;
    applyf(root->item);
    btree_apply_prefix(root->left,applyf);
    btree_apply_prefix(root->right,applyf);
}

