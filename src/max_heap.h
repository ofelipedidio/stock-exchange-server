#include "order.h"
#include "order_list.h"
#include "heap.h"

#ifndef MAX_HEAP
#define MAX_HEAP

/*
 * Gets the element with maximum heap value
 */
order_t *max_heap_head(order_list_t *orders);

/*
 * Insert an element into the max heap
 */
void max_heap_push(order_list_t *heap, order_t order);

/*
 * Removed the head of the max heap
 */
void max_heap_pop(order_list_t *heap);

/*
 * Transforms the list into a max heap
 */
void max_heap_make(order_list_t *list);

#endif // MAX_HEAP

