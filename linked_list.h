#ifndef C_WORKING_LINKED_LIST_H
#define C_WORKING_LINKED_LIST_H
#include <stdio.h>

typedef struct Node_t{
    struct Node_t *next, *prev, *prev_val;
    int r, c;
    int prev_r, prev_c;
    int direction;
}node_t;

typedef struct List_t{
    struct Node_t *head, *tail;
    size_t size;
}list_t;

node_t *init_node(int, int,  int, int, int);
list_t *init_list(int, int);
void push_back(list_t *, int, int,  int, int, int);
void free_list(list_t *);

#endif //C_WORKING_LINKED_LIST_H
