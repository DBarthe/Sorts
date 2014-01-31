#ifndef SORT_H_
# define SORT_H_

# include <stdlib.h>

typedef int (*CmpFunction)(const void *, const void *);
typedef enum Order Order;

enum Order { ASC, DESC };

void heapsort(void **tab, size_t size, CmpFunction cmpFunction, Order order);
void quicksort(void **tab, size_t size, CmpFunction cmpFunction, Order order);
void mergesort(void **tab, size_t size, CmpFunction cmpFunction, Order order);

#endif /* !SORT_H_ */
