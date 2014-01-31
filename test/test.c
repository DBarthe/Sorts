
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#include "sort.h"

#define DEFAULT_SIZE 10000
#define DEFAULT_GAP -1

static int intCmp(const int *a, const int *b)
{
  return (*a - *b);
}

static int **generateTable(size_t size, size_t gap)
{
  int  **tab;
  size_t i;

  srand(time(NULL));
  tab = malloc(size * sizeof(int *));
  for (i = 0; i < size; i++)
    {
      tab[i] = malloc(sizeof(int));
      if (gap == -1)
	*tab[i] = rand();
      else
	*tab[i] = rand() % gap;
    }
  return tab;
}

static void printTable(int **tab, size_t size)
{
  int i;

  for (i = 0; i < size; i++)
    {
      printf("%d\n", *tab[i]);
    }
}

static size_t getSize(int ac, char **av)
{
  return (ac > 1 ? atoi(av[1]) : DEFAULT_SIZE);
}

static size_t getGap(int ac, char **av)
{
  return (ac > 2 ? atoi(av[2]) : DEFAULT_GAP);
}

int main(int ac, char **av)
{
  int **tab;
  size_t size, gap;

  size = getSize(ac, av);
  gap = getGap(ac, av);

  tab = generateTable(size, gap);
  
#ifdef FUNCTION_NAME
  FUNCTION_NAME((void **)tab, size, (CmpFunction)&intCmp, ASC);
#endif

#ifdef PRINT
  printTable(tab,size);
#endif
  return 0;
}
