/**
 * @file datastructures.h
 * @brief Data structures function prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This headers contains the various data structure management functions defined in the library.
 * These typically involve interating with in-memory storage structures
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page datastructures data structures functionality
This is a narative on this part of the library
*/

#ifndef STULIBC_DATASTRUCTURES_H
#define STULIBC_DATASTRUCTURES_H

#include <stddef.h>

/** @brief Performs a bubble sort on a list of integers.
 *
 * @param list int[] list of long integers to sort
 * @param n long number of elements in the list
  * @return void
 * @remarks None
 */
void bubble_sort (int *a, int n)
{
    int i, t, s = 1;
    while (s) {
        s = 0;
        for (i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
    }
}


/** @brief Performs a quick sort on a list of integers.
 *
 * @param a long[] list of integers to sort
 * @param n long number of elements in the list
  * @return void
 * @remarks None
 */
void quick_sort (int *a, int n)
{
    if (n < 2)
        return;
    int p = a[n / 2];
    int *l = a;
    int *r = a + n - 1;
    while (l <= r) {
        if (*l < p) {
            l++;
        }
        else if (*r > p) {
            r--;
        }
        else {
            int t = *l;
            *l = *r;
            *r = t;
            l++;
            r--;
        }
    }
    quick_sort(a, r - a + 1);
    quick_sort(l, a + n - l);
}


/** @brief Performs a insertion sort on a list of integers.
 *
 * @param a int[] list of integers to sort
 * @param n long number of elements in the list
  *@return void
 * @remarks None
 */
void insertion_sort(int *a, const size_t n) {
    size_t i, j;
    int value;
    for (i = 1; i < n; i++) {
        value = a[i];
        for (j = i; j > 0 && value < a[j - 1]; j--) {
            a[j] = a[j - 1];
        }
        a[j] = value;
    }
}

void *array_concat(const void *a, size_t an,
                   const void *b, size_t bn, size_t s)
{
  char *p = malloc(s * (an + bn));
  memcpy(p, a, an*s);
  memcpy(p + an*s, b, bn*s);
  return p;
}


#endif
