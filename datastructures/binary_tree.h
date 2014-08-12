/**
 * @file binary_tree.h
 * @brief Binary tree function prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This headers contains the binry_tree functions defined in the library.
 * This binary tree where each node carries an integer, and implement preoder, inorder, postorder and level-order traversal.
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page BinaryTree Using binary tree functionality
This is a narative on this part of the library
*/

#ifndef STULIBC_BINARY_TREE_H
#define STULIBC_BINARY_TREE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct node_s
{
  int value;
  struct node_s* left;
  struct node_s* right;
} *node;

node tree(int v, node l, node r)
{
  node n = malloc(sizeof(struct node_s));
  n->value = v;
  n->left  = l;
  n->right = r;
  return n;
}

void destroy_tree(node n)
{
  if (n->left)
    destroy_tree(n->left);
  if (n->right)
    destroy_tree(n->right);
  free(n);
}

void preorder(node n, void (*f)(int))
{
  f(n->value);
  if (n->left)
    preorder(n->left, f);
  if (n->right)
    preorder(n->right, f);
}

void inorder(node n, void (*f)(int))
{
  if (n->left)
    inorder(n->left, f);
  f(n->value);
  if (n->right)
    inorder(n->right, f);
}

void postorder(node n, void (*f)(int))
{
  if (n->left)
    postorder(n->left, f);
  if (n->right)
    postorder(n->right, f);
  f(n->value);
}

/* helper queue for levelorder */
typedef struct qnode_s
{
  struct qnode_s* next;
  node value;
} *qnode;

typedef struct { qnode begin, end; } queue;

void enqueue(queue* q, node n)
{
  qnode node = malloc(sizeof(struct qnode_s));
  node->value = n;
  node->next = 0;
  if (q->end)
    q->end->next = node;
  else
    q->begin = node;
  q->end = node;
}

node dequeue(queue* q)
{
  node tmp = q->begin->value;
  qnode second = q->begin->next;
  free(q->begin);
  q->begin = second;
  if (!q->begin)
    q->end = 0;
  return tmp;
}

int queue_empty(queue* q)
{
  return !q->begin;
}

void levelorder(node n, void(*f)(int))
{
  queue nodequeue = {};
  enqueue(&nodequeue, n);
  while (!queue_empty(&nodequeue))
  {
    node next = dequeue(&nodequeue);
    f(next->value);
    if (next->left)
      enqueue(&nodequeue, next->left);
    if (next->right)
      enqueue(&nodequeue, next->right);
  }
}

void print(int n)
{
  printf("%d ", n);
}

#endif
