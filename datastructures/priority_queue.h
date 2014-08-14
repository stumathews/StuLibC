/*
 A priority queue is somewhat similar to a queue, with an important distinction: each item is added to a priority queue with a priority level, and will be later removed from the queue with the highest priority element first.
 That is, the items are (conceptually) stored in the queue in priority order instead of in insertion order.
 */

#ifndef STULIBC_PRIORITY_QUEUE_H
#define STULIBC_PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct { void * data; int pri; } q_elem_t;
typedef struct { q_elem_t *buf; int n, alloc; } pri_queue_t, *pri_queue;

#define priq_purge(q) (q)->n = 1
#define priq_size(q) ((q)->n - 1)
/* first element in array not used to simplify indices */
pri_queue priq_new(int size);

void priq_push(pri_queue q, void *data, int pri);

/* remove top item. returns 0 if empty. *pri can be null. */
void * priq_pop(pri_queue q, int *pri);

/* get the top element without removing it from queue */
void* priq_top(pri_queue q, int *pri);

/* this is O(n log n), but probably not the best */
void priq_combine(pri_queue q, pri_queue q2);

#endif
