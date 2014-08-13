/**
 * @file datastructures.h
 * @brief Data structure library function prototypes.
 * @author Stuart Mathews
 * @date 12 July 2013
 *
 * This header defines function prototypes and type declarations for dealing with data and organising
 * it in to structured containers for storage and manipulation.
 * This includes things like creating and maintaining linked-lists, b-tress etc..
 * @see http://devel.stuartmathews.com/stulibc
 */

/** \page datastructures Data structures and algorithms
This is a narative on this part of the library
*/
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// Links lists and common data structures including routines and algorithms for them

#define ARRAY_CONCAT(TYPE, A, An, B, Bn) (TYPE *)array_concat((const void *)(A), (An), (const void *)(B), (Bn), sizeof(TYPE));



void quick_sort (int *a, int n);
void bubble_sort(int *a, int n);
void insertion_sort(int *a, const size_t n);
void *array_concat(const void *a, size_t an, const void *b, size_t bn, size_t s);

#endif
