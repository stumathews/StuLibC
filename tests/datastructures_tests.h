#ifndef DATA_STRUCTURES_TESTS_H
#define DATA_STRUCTURES_TESTS_H

#include "..\datastructures\binary_tree.h"
#include "..\datastructures\datastructures.h"
#include "..\datastructures\simple_hashtable.h"

void test_bubble_sort()
{
	int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
	int n = sizeof a / sizeof a[0];
	bubble_sort(a, n);
}

void test_quick_sort()
{
	int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
	int n = sizeof a / sizeof a[0];
	quick_sort(a, n);
}

void test_insertion_sort()
{
	int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
	insertion_sort(a, sizeof a / sizeof a[0]);
}

void test_binary_tree()
{
	node n = tree(1,
	                tree(2,
	                     tree(4,
	                          tree(7, 0, 0),
	                          0),
	                     tree(5, 0, 0)),
	                tree(3,
	                     tree(6,
	                          tree(8, 0, 0),
	                          tree(9, 0, 0)),
	                     0));

	  printf("preorder:    ");
	  preorder(n, print);
	  printf("\n");

	  printf("inorder:     ");
	  inorder(n, print);
	  printf("\n");

	  printf("postorder:   ");
	  postorder(n, print);
	  printf("\n");

	  printf("level-order: ");
	  levelorder(n, print);
	  printf("\n");

	  destroy_tree(n);
}

void test_array_concat()
{
	const int a[] = { 1, 2, 3, 4, 5 };
	const int b[] = { 6, 7, 8, 9, 0 };
	unsigned int i;

	  int *c = ARRAY_CONCAT(int, a, 5, b, 5);

	  for(i = 0; i < 10; i++)
	    printf("%d\n", c[i]);

	  free(c);
}

void test_simple_hashtable()
{
	Hash *hash = hash_new(15);
	hash_insert(hash, "hello", "world");
	hash_insert(hash, "a", "b");
	printf("hello => %s\n", hash_lookup(hash, "hello"));
	printf("herp => %s\n", hash_lookup(hash, "herp"));
	printf("a => %s\n", hash_lookup(hash, "a"));
}

void test_queue()
{
	int i, n;
	    queue q = q_new();

	    for (i = 0; i < 100000000; i++) {
	        n = rand();
	        if (n > RAND_MAX / 2) {
	        //  printf("+ %d\n", n);
	            enqueue(q, n);
	        } else {
	            if (!dequeue(q, &n)) {
	            //  printf("empty\n");
	                continue;
	            }
	        //  printf("- %d\n", n);
	        }
	    }
	    while (dequeue(q, &n));// printf("- %d\n", n);
}

void test_priority_queue()
{
	int i, p;
	  const char *c, *tasks[] ={
	    "Clear drains", "Feed cat", "Make tea", "Solve RC tasks", "Tax return" };
	  int pri[] = { 3, 4, 5, 1, 2 };

	  /* make two queues */
	  pri_queue q = priq_new(0), q2 = priq_new(0);

	  /* push all 5 tasks into q */
	  for (i = 0; i < 5; i++)
	    priq_push(q, tasks[i], pri[i]);

	  /* pop them and print one by one */
	  while ((c = priq_pop(q, &p)))
	    printf("%d: %s\n", p, c);

	  /* put a million random tasks in each queue */
	  for (i = 0; i < 1 << 20; i++) {
	    p = rand() / ( RAND_MAX / 5 );
	    priq_push(q, tasks[p], pri[p]);

	    p = rand() / ( RAND_MAX / 5 );
	    priq_push(q2, tasks[p], pri[p]);
	  }

	  printf("\nq has %d items, q2 has %d items\n", priq_size(q), priq_size(q2));

	  /* merge q2 into q; q2 is empty */
	  priq_combine(q, q2);
	  printf("After merge, q has %d items, q2 has %d items\n",
	    priq_size(q), priq_size(q2));

	  /* pop q until it's empty */
	  for (i = 0; (c = priq_pop(q, 0)); i++);
	  printf("Popped %d items out of q\n", i);
}


#endif
