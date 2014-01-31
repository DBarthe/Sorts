
#include <time.h>
#include "sort.h"

//#define INLINE inline

#ifdef INFOS
# include <stdio.h>
static size_t swapCounter;
static size_t compareCounter;
#endif

static INLINE _Bool isOrdered(void **tab, const size_t a, const size_t b,
			    const CmpFunction cmpFunct, const Order order)
{
  register int cmp;

#ifdef INFOS
  compareCounter++;
#endif
  cmp = cmpFunct(tab[a], tab[b]);
  if (order == ASC)
    {
      if (cmp <= 0)
        return 1;
    }
  else
    {
      if (cmp >= 0)
        return 1;
    }
  return 0;
}

static INLINE void swap(void **tab, const size_t a, const size_t b)
{
  void *tmp;

#ifdef INFOS
  swapCounter++;
#endif
  tmp = tab[a];
  tab[a] = tab[b];
  tab[b] = tmp;
}

static size_t partition(void **tab, size_t first, size_t last, size_t pivot,
			CmpFunction cmpFunction, Order order)
{
  size_t i, j;

  swap(tab, pivot, last);
  j = first;
  for (i = first; i < last; i++)
    {
      if (isOrdered(tab, i, last, cmpFunction, order))
	{
	  swap(tab, i, j);
	  j++;
	} 
    }
  swap(tab, last, j);
  return j;
  
}

static void recursive(void **tab, size_t first, size_t last,
		      CmpFunction cmpFunction, Order order)
{
  size_t pivot;

  if (first < last)
    {
      pivot = rand() % (last - first + 1) + first;
      pivot = partition(tab, first, last, pivot, cmpFunction, order);
      if (pivot > 0)
	recursive(tab, first, pivot-1, cmpFunction, order);
      recursive(tab, pivot+1, last, cmpFunction, order);
    }
}

void quicksort(void **tab, size_t size, CmpFunction cmpFunction, Order order)
{
  srand(time(NULL));
  recursive(tab, 0, size-1, cmpFunction, order);

#ifdef INFOS
  printf("%lu elements sorted in %lu swaps and %lu comparisons with quicksort\n",
	 size, swapCounter, compareCounter);

#endif
}
