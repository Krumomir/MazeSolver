#include "priority_queue.c"
#include <stdlib.h>

void free_list(list_t *list)
{
    node_t *temp = list->head->next;

    while(temp)
    {
        free(temp->prev);
        temp = temp->next;
    }

    free(list->tail);
    free(list);
}

node_t *init_node(int r, int c,  int prev_r, int prev_c, int dir)
{
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->prev_val = NULL;
    new_node->r = r;
    new_node->c = c;
    new_node->prev_r = prev_r;
    new_node->prev_c = prev_c;
    new_node->direction = dir;

    return new_node;
}

list_t *init_list(int x, int y)
{
    list_t *new_list = (list_t *) malloc(sizeof(list_t));
    node_t *new_node = init_node(x, y, -1, -1, 0);
    new_list->head = new_node;
    new_list->tail = new_node;
    new_list->size = 1;

    return new_list;
}

void push_back(list_t *list, int r, int c,  int prev_r, int prev_c, int dir)
{
    node_t *new_node = init_node(r, c, prev_r, prev_c, dir);
    list->tail->next = new_node;
    new_node->next = NULL;
    new_node->prev = list->tail;
    list->tail->next = new_node;
    list->tail = new_node;
    new_node->r = r;
    new_node->c = c;
    new_node->prev_r = prev_r;
    new_node->prev_c = prev_c;
    list->size++;
}

void push_front(list_t *list, int r, int c,  int prev_r, int prev_c, int dir)
{
    node_t *new_node = init_node(r, c, prev_r, prev_c, dir);
    list->head->prev = new_node;
    new_node->next = list->head;
    list->head = new_node;
    new_node->r = r;
    new_node->c = c;
    new_node->prev_r = prev_r;
    new_node->prev_c = prev_c;
    list->size++;
}