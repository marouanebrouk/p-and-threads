#include "h.h"

void btree_apply_infix(t_tree *root, void (*applyf)(void *))
{
    if (root = NULL)
        return;
    btree_apply_infix(root->left,applyf);
    applyf(root->item);
    btree_apply_infix(root->right,applyf);
}