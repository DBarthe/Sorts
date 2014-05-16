Sorts
=====

Some sorting algorithms implemented in C for tables of generics pointers

Usage
-----
To test and compare algorithms :
~~~bash
$ ./test.sh
~~~

To generate an archive :
~~~bash
$ make
~~~

And use it anywhere, see include/sort.h :
~~~c
void heapsort(void **tab, size_t size, CmpFunction cmpFunction, Order order);
void quicksort(void **tab, size_t size, CmpFunction cmpFunction, Order order);
void mergesort(void **tab, size_t size, CmpFunction cmpFunction, Order order); 
~~~


