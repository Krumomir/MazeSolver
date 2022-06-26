#ifndef C_WORKING_MAZE_H
#define C_WORKING_MAZE_H
#include "linked_list.c"
#include "linked_list.h"
#include <math.h>

void push_in_queue(int r, int c, char grid[r][c], int, int, int , que **);
void find_path(int r, int c, char grid[r][c], int, int, int , que **, int **);
list_t *dfs(int r, int c, char[r][c]);
list_t *astar(int r, int c, char[r][c]);
double find_distance(int, int, int, int);
void skip(list_t *, node_t *);
list_t *invert(list_t *);

double find_distance(int r, int c, int curr_r, int curr_c)
{
    int a = r - curr_r - 1;
    int b = c - curr_c - 1;

    return sqrt((a * a) + (b * b));
}

void find_path(int r, int c, char grid[r][c], int curr_r, int curr_c, int dir,  que **queue, int **visited)
{
    node_t *el = NULL;

    if(curr_c - 1 >= 0 &&
       grid[curr_r][curr_c - 1] != '#' &&
       visited[curr_r][curr_c - 1] != 1) //LEFT
    {
        el = init_node(curr_r, curr_c - 1, curr_r, curr_c, 4);
        in_push(queue, el, find_distance(r, c, curr_r, curr_c - 1));
        visited[curr_r][curr_c - 1] = 1;
    }
    if(curr_r + 1 < r &&
       grid[curr_r + 1][curr_c] != '#' &&
       visited[curr_r + 1][curr_c] != 1) //DOWN
    {
        el = init_node(curr_r + 1, curr_c, curr_r, curr_c, 1);
        in_push(queue, el, find_distance(r, c, curr_r + 1, curr_c));
        visited[curr_r + 1][curr_c] = 1;
    }
    if(curr_c + 1 < c &&
       grid[curr_r][curr_c + 1] != '#' &&
       visited[curr_r][curr_c + 1] != 1) //RIGHT
    {
        el = init_node(curr_r, curr_c + 1, curr_r, curr_c, 2);
        in_push(queue, el, find_distance(r, c, curr_r, curr_c + 1));
        visited[curr_r][curr_c + 1] = 1;
    }
    if(curr_r - 1 >= 0 &&
       grid[curr_r - 1][curr_c] != '#' &&
       visited[curr_r - 1][curr_c] != 1) //UP
    {
        el = init_node(curr_r - 1, curr_c, curr_r, curr_c, 3);
        in_push(queue, el, find_distance(r, c, curr_r - 1, curr_c));
        visited[curr_r - 1][curr_c] = 1;
    }
}
void push_in_queue(int r, int c, char grid[r][c], int curr_r, int curr_c, int dir,  que **queue)
{
    node_t *el = NULL;
    if(dir == 1)
    {
        if(curr_c - 1 >= 0 &&
           grid[curr_r][curr_c - 1] != '#') //LEFT
        {
            el = init_node(curr_r, curr_c - 1, curr_r, curr_c, 4);
            push(queue, el, 5);
        }
        if(curr_r + 1 < r &&
           grid[curr_r + 1][curr_c] != '#') //DOWN
        {
            el = init_node(curr_r + 1, curr_c, curr_r, curr_c, 1);
            push(queue, el, 4);
        }
        if(curr_c + 1 < c &&
           grid[curr_r][curr_c + 1] != '#') //RIGHT
        {
            el = init_node(curr_r, curr_c + 1, curr_r, curr_c, 2);
            push(queue, el, 3);
        }
        if(curr_r - 1 >= 0 &&
           grid[curr_r - 1][curr_c] != '#') //UP
        {
            el = init_node(curr_r - 1, curr_c, curr_r, curr_c, 3);
            push(queue, el, 2);
        }
    }
    else if(dir == 2)
    {
        if(curr_r + 1 < r &&
           grid[curr_r + 1][curr_c] != '#') //DOWN
        {
            el = init_node(curr_r + 1, curr_c, curr_r, curr_c, 1);
            push(queue, el, 5);
        }
        if(curr_c + 1 < c &&
           grid[curr_r][curr_c + 1] != '#') //RIGHT
        {
            el = init_node(curr_r, curr_c + 1, curr_r, curr_c, 2);
            push(queue, el, 4);
        }
        if(curr_r - 1 >= 0 &&
           grid[curr_r - 1][curr_c] != '#') //UP
        {
            el = init_node(curr_r - 1, curr_c, curr_r, curr_c, 3);
            push(queue, el, 3);
        }
        if(curr_c - 1 >= 0 &&
           grid[curr_r][curr_c - 1] != '#') //LEFT
        {
            el = init_node(curr_r, curr_c - 1, curr_r, curr_c, 4);
            push(queue, el, 2);
        }
    }
    else if(dir == 3)
    {
        if(curr_c + 1 < c &&
           grid[curr_r][curr_c + 1] != '#') //RIGHT
        {
            el = init_node(curr_r, curr_c + 1, curr_r, curr_c, 2);
            push(queue, el, 5);
        }
        if(curr_r - 1 >= 0 &&
           grid[curr_r - 1][curr_c] != '#') //UP
        {
            el = init_node(curr_r - 1, curr_c, curr_r, curr_c, 3);
            push(queue, el, 4);
        }
        if(curr_c - 1 >= 0 &&
           grid[curr_r][curr_c - 1] != '#') //LEFT
        {
            el = init_node(curr_r, curr_c - 1, curr_r, curr_c, 4);
            push(queue, el, 3);
        }
        if(curr_r + 1 < r &&
           grid[curr_r + 1][curr_c] != '#') //DOWN
        {
            el = init_node(curr_r + 1, curr_c, curr_r, curr_c, 1);
            push(queue, el, 2);
        }
    }
    else if(dir == 4)
    {
        if(curr_r - 1 >= 0 &&
           grid[curr_r - 1][curr_c] != '#') //UP
        {
            el = init_node(curr_r - 1, curr_c, curr_r, curr_c, 3);
            push(queue, el, 5);
        }
        if(curr_c - 1 >= 0 &&
           grid[curr_r][curr_c - 1] != '#') //LEFT
        {

            el = init_node(curr_r, curr_c - 1, curr_r, curr_c, 4);
            push(queue, el, 4);
        }
        if(curr_r + 1 < r &&
           grid[curr_r + 1][curr_c] != '#') //DOWN
        {
            el = init_node(curr_r + 1, curr_c, curr_r, curr_c, 1);
            push(queue, el, 3);
        }
        if(curr_c + 1 < c &&
           grid[curr_r][curr_c + 1] != '#') //RIGHT
        {
            el = init_node(curr_r, curr_c + 1, curr_r, curr_c, 2);
            push(queue, el, 2);
        }
    }

    free(el);
}

list_t *dfs(int r, int c, char grid[r][c]) {
    node_t *new_el = init_node(0, 0, 0, 0, 1);

    list_t *list = init_list(0, 0);
    que *queue = init_que(new_el, 0);
    int count = 0;

    while(1)
    {
        new_el = pop_que(&queue);

        if (queue)
            destroy(&queue);

        if(new_el->r == 0 && new_el->c == 0)
            count++;

        if(count == 3)
        {
            free(new_el);
            free_list(list);
            return NULL;
        }

        push_back(list, new_el->r, new_el->c, new_el->prev_r, new_el->prev_c, new_el->direction);

        if (new_el->r == r - 1 && new_el->c == c - 1)
        {
            free(new_el);
            break;
        }

        queue = init_que(new_el, 0);
        push_in_queue(r, c, grid, new_el->r, new_el->c, new_el->direction, &queue);
    }

    return list;
}


list_t *astar(int r, int c, char grid[r][c]) {
    node_t *new_el = init_node(0, 0, 0, 0, 1);

    list_t *list = init_list(0, 0);
    que *queue = init_que(new_el, -1);

    int **visited = (int **) calloc(r,sizeof(int *));
    for (int i = 0; i < r; ++i)
        visited[i] = (int *) calloc(c, sizeof(int));

    visited[0][0] = 1;

    while (1)
    {
        new_el = pop_que(&queue);
        push_back(list, new_el->r, new_el->c, new_el->prev_r, new_el->prev_c, new_el->direction);

        if (new_el->r == r - 1 && new_el->c == c - 1)
        {
            free(new_el);
            break;
        }

        if(!queue)
            queue = init_que(new_el, -1);

        find_path(r, c, grid, new_el->r, new_el->c, new_el->direction, &queue, visited);
    }

    list_t *result = invert(list);
    free_list(list);

    return result;
}

void skip(list_t *list, node_t *curr)
{
    node_t *temp = list->head->next;

    while(temp)
    {
        if(temp->r == curr->prev_r
           && temp->c == curr->prev_c)
            break;

        temp = temp->next;
    }
    curr->prev_val = temp;
}

list_t *invert(list_t *list)
{
    list_t *new_list = init_list(0, 0);
    node_t *temp = list->tail;

    while(temp->prev)
    {
        push_front(new_list, temp->r, temp->c, temp->prev_r,temp->prev_c, temp->direction);
        if(temp->prev_c != temp->prev->c ||
           temp->prev_r != temp->prev->r)
            skip(list, temp);

        if(temp->prev_val)
            temp = temp->prev_val;
        else
            temp = temp->prev;
    }

    return new_list;
}
#endif //C_WORKING_MAZE_H
