#ifndef STULIBC_LINKED_LIST_H
#define STULIBC_LINKED_LIST_H

/*
A linked list is a data structure which allows a great deal of flexibility in memory allocation and data sorting. Linked lists depend on references for their organization. Information is stored in "nodes" which contain data (integers, strings, etc., sometimes called an "element") and one or more "links" to to other nodes. The number of links determines what type of linked list it is (one link: "singly-linked list", two links: "doubly-linked list", three links: "triply-linked list", etc.), though one or two links are most common. Linked lists have a "head" (the first node in the list) and sometimes a "tail" (the last node).
In most languages, an implementation of a linked list is given and programmers will likely never need to create their own implementation. Most programmer-defined implementations found here should not be used in programs, but rather they are here to demonstrate language features and to help show how a linked list works.

*/

struct link {
  struct link *next;
  int data;
};

void insert_append (link *anchor, link *newlink)
{
  newlink->next = anchor->next;
  anchor->next = newlink;
}

#endif
