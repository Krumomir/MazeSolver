#include "priority_queue.h"
#include <stddef.h>
#include <stdlib.h>

que *init_que(node_t *node, double priority)
{
    que *new_node = (que *)malloc(sizeof(que));

    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->node = node;
    new_node->prio = priority;

    return new_node;
}

void push(que **queue, node_t *node, double priority)
{
    if(*queue)
    {
        que *new_node = init_que(node, priority);

        que *temp = (*queue);

        if ((*queue)->prio < priority)
        {
            new_node->next = *queue;
            (*queue)->prev = new_node;
            (*queue) = new_node;
        }
        else
        {
            while(temp->next && temp->next->prio > priority)
                temp = temp->next;

            new_node->next = temp->next;
            if(temp->next)
                temp->next->prev = new_node;
            temp->next = new_node;
            new_node->prev = temp;
        }
    }
}

void in_push(que **queue, node_t *node, double priority)
{
    if(*queue)
    {
        que *new_node = init_que(node, priority);

        que *temp = (*queue);

        if ((*queue)->prio > priority)
        {
            new_node->next = *queue;
            (*queue)->prev = new_node;
            (*queue) = new_node;
        }
        else
        {
            while(temp->next && temp->next->prio < priority)
                temp = temp->next;

            new_node->next = temp->next;
            if(temp->next)
                temp->next->prev = new_node;
            temp->next = new_node;
            new_node->prev = temp;
        }
    }
}

node_t *pop_que(que **queue)
{
    if((*queue)->next && (*queue)->prio < 0)
    {
        (*queue) = (*queue)->next;
        free((*queue)->prev);
        (*queue)->prev = NULL;
    }
    node_t *temp = (*queue)->node;
    if((*queue)->next)
    {
        (*queue) = (*queue)->next;
        free((*queue)->prev);
        (*queue)->prev = NULL;
    }
    else
    {
        free(*queue);
        *queue = NULL;
    }

    return temp;
}

void destroy(que **queue)
{
    que *temp = *queue;
    while(temp->next)
    {
        temp = temp->next;
        free(temp->prev);
    }
    free(temp);
    *queue = NULL;
}