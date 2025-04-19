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


int main()
{
    t_tree *node;
    node = btree_create_node(0);
    node->left = btree_create_node(1);
    node->right= btree_create_node(2);
    printf("root node is %d\n",node->item);
    printf("left node is %d\n",node->left->item);
    printf("right node is %d\n",node->right->item);
}