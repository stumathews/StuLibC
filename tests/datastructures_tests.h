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


#endif
