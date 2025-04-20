#include "h.h"


t_tree *btree_create_node(void *item)
{
    (void)item;
    t_tree *node = malloc(sizeof(t_tree));
    if (!node)
        return (NULL);
    node->item = item;
    node->left = NULL;
    node->right = NULL;
    return(node);
}


void btree_insert_data(t_tree **root, void *item, int (*cmpf)(void *, void *))
{
    if (root = NULL)
        *root = btree_create_node(item);
    else
    {
        if (cmpf(item,(*root)->item) < 0)
            btree_insert_data(&(*root)->left, item, cmpf);
        else
            btree_insert_data(&(*root)->right, item, cmpf);
    }
}