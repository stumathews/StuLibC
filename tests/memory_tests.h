#ifndef STULIBC_MEMORY_MANAGMENT_TESTS_H
#define STULIBC_MEMORY_MANAGEMENT_TESTS_H

// Common memory related functions like allocating memory or filling memory and freeing it etc.
void test_MEM_()
{
	  int *ints = MEM_allocate(SIZEOF_MEMB*NMEMB);
	  /* realloc can be used to increase or decrease an already
	     allocated memory (same as malloc if ints is NULL) */
	  ints = MEM_resize(ints, sizeof(int)*(NMEMB+1));
	  /* calloc set the memory to 0s */
	  int *int2 = MEM_zero_allocate(NMEMB, SIZEOF_MEMB);
	  /* all use the same free */
	  free(ints); free(int2);
}

#endif
