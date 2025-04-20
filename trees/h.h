#ifndef H_H
# define H_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_tree
{
    void *item;
    struct s_tree *left;
    struct s_tree *right;
} t_tree;


#endif