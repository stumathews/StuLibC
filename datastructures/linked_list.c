#include "linked_list.h"

void insert_append (link *anchor, link *newlink)
{
	  newlink->next = anchor->next;
	  anchor->next = newlink;
}
