#ifndef C_WORKING_PRIORITY_QUEUE_H
#define C_WORKING_PRIORITY_QUEUE_H
#include "linked_list.h"

typedef struct queue_t{
    struct queue_t *next;
    struct queue_t *prev;
    double prio;
    node_t *node;
}que;

que *init_que(node_t *node, double priority);
void push(que **queue, node_t *node, double priority);
void in_push(que **queue, node_t *node, double priority);
node_t *pop_que(que **queue);
void destroy(que **queue);

#endif //C_WORKING_PRIORITY_QUEUE_H
