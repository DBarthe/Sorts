Sorts
=====

Some sorting algorithms implemented in C for tables of generics pointers

Usage
-----

see include/sort.h.

> void heapsort(void **tab, size_t size, CmpFunction cmpFunction, Order order);

> void quicksort(void **tab, size_t size, CmpFunction cmpFunction, Order order);

> void mergesort(void **tab, size_t size, CmpFunction cmpFunction, Order order); 
