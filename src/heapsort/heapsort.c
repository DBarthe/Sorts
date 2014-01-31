
#include "sort.h"

//#define INLINE inline
//#define SIFT_UP

#ifdef INFOS
#include <stdio.h>
static size_t swapCounter;
static size_t compareCounter;
#endif

/*
 * Heapsort inverse the comparison.
 * So, ASC => max must be before min
 *    DESC => max must be after min
 */
static INLINE _Bool isOrdered(void **tree,
			      const size_t child1,
			      const size_t child2,
			      const CmpFunction cmpFunct,
			      const Order order)
{
  register int cmp;

#ifdef INFOS
  compareCounter++;
#endif
  cmp = cmpFunct(tree[child1-1], tree[child2-1]);
  if (order == ASC)
    {
      if (cmp >= 0)
	return 1;
    }
  else
    {
      if (cmp <= 0)
	return 1;
    }
  return 0;
}

static INLINE void swap(void **tree, const size_t node, const size_t child)
{
  void *tmp;

#ifdef INFOS
  swapCounter++;
#endif
  tmp = tree[node-1];
  tree[node-1] = tree[child-1];
  tree[child-1] = tmp;
}

static void siftDown(void **tree,  size_t node, size_t size, CmpFunction cmpFunct, Order order)
{
   size_t child;

   child = 2 * node;
   while (child <= size)
     {
       if (child < size && !isOrdered(tree, child, child+1, cmpFunct, order))
	 child++;
       if (!isOrdered(tree, node, child, cmpFunct, order))
	 swap(tree, node, child);
       node = child;
       child = 2 * node;
     }
}

#ifdef SIFT_UP
static void siftUp(void **tree,  size_t node, CmpFunction cmpFunct, Order order)
{
   size_t parent;

   while (node > 1)
     {
       parent = node / 2;
       if (!isOrdered(tree, parent, node, cmpFunct, order))
	 swap(tree, parent, node);
       else
	 return ;
       node = parent;
     }
}
#endif

void heapsort(void **tree, size_t size, CmpFunction cmpFunct, Order order)
{
   size_t i;

   /* initialize infos counters if INFOS is defined */
#ifdef INFOS
  swapCounter = 0;
  compareCounter = 0;
#endif

  /* heapifiy  with siftUp or siftDown*/
#ifdef SIFT_UP
  for (i = 2; i <= size; i++)
    siftUp(tree, i, cmpFunct, order);
  siftDown(tree, 1, size, cmpFunct, order);
#else
  for (i = size / 2; i >= 1; i--)
    siftDown(tree, i, size, cmpFunct, order);
#endif

  /* loop until sort */
  for (i = size; i >= 2; i--)
    {
      swap(tree, 1, i);
      siftDown(tree, 1, i-1, cmpFunct, order);
    }

  /* print infos if INFOS is defined */
#ifdef INFOS
  printf("%lu elements sorted in %lu swaps and %lu comparisons with heapsort\n",
	 size, swapCounter, compareCounter);
#endif
}
