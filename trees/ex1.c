#include "h.h"

t_tree *btree_create_node(int item)
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
