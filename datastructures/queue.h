
/*
Elements are added at one side and popped from the other in the order of insertion.
Operations:
push (aka enqueue) - add element
pop (aka dequeue) - pop first element
empty - return truth value when empty
Errors:
handle the error of trying to pop from an empty queue (behavior depends on the language and platform)
*/


#ifndef STULIBC_QUEUE_H
#define STULIBC_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t node_t, *node, *queue;
struct node_t { int val; node prev, next; };

#define HEAD(q) q->prev
#define TAIL(q) q->next

queue q_new();
int empty(queue q);
void enqueue(queue q, int n);
int dequeue(queue q, int *val);

#endif

