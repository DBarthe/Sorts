
#include <string.h>
#include "sort.h"

#ifdef INFOS
# include <stdio.h>
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

static void **dupTab(void **tab, size_t size)
{
  void **dup;

  dup = malloc(size * sizeof(void *));
  if (dup == NULL)
    return NULL;
  memcpy(dup, tab, size * sizeof(void *));
  return dup;
}

static void *getHead(void **tab, size_t n, size_t size, size_t sub, size_t *p_i1, size_t *p_i2,
		     CmpFunction cmpFunction, Order order)
{
  void *head;
  int out1, out2;

  out1 = sub + *p_i1 >= size || *p_i1 >= n;
  out2 = sub+n + *p_i2 >= size || *p_i2 >= n;
  if (out1 && out2)
    head = NULL;
  else if (out1)
    head = tab[sub+n + (*p_i2)++];
  else if (out2)
    head = tab[sub + (*p_i1)++];
  else
    {
      if (isOrdered(tab, sub + *p_i1, sub+n + *p_i2, cmpFunction, order))
	head = tab[sub + (*p_i1)++];
      else
	head = tab[sub+n + (*p_i2)++];
    }
  return head;
}

static void merge(void **srcTab, void **dstTab, size_t n, size_t size,
		  CmpFunction cmpFunction, Order order)
{
  void *tmp;
  size_t sub, i1, i2, j;

  j = 0;
  for (sub = 0; sub < size; sub += n*2)
    {
      i1 = 0;
      i2 = 0;
      while ((tmp = getHead(srcTab, n, size, sub, &i1, &i2, cmpFunction, order)) != NULL)
	{
	  dstTab[j] = tmp;
	  j++;
	}
    }
}

static void migrate(void **srcTab, void **dstTab, size_t size)
{
  size_t i;

  for (i = 0; i < size; i++)
    dstTab[i] = srcTab[i];
}


void mergesort(void **tab, size_t size, CmpFunction cmpFunction, Order order)
{
  void **newTab;
  void **tmpTab;
  void **srcTab;
  void **dstTab;
  size_t n;

  if ((newTab = dupTab(tab, size)) == NULL)
    return ;

  srcTab = tab;
  dstTab = newTab;
  for (n = 1; n < size; n *= 2)
    {
      merge(srcTab, dstTab, n, size, cmpFunction, order);
      tmpTab = srcTab;
      srcTab = dstTab;
      dstTab = tmpTab;
    }
  if (dstTab == tab)
    migrate(srcTab, dstTab, size);

  free(newTab);

#ifdef INFOS
  printf("%lu elements sorted in %lu comparisons with heapsort\n",
	 size, compareCounter);
#endif
}
