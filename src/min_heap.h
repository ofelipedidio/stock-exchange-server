#include "order.h"
#include "order_list.h"
#include "heap.h"

#ifndef MIN_HEAP
#define MIN_HEAP

/*
 * Gets the element with minimum heap value
 */
order_t *min_heap_head(order_list_t *orders);

/*
 * Insert an element into the min heap
 */
void min_heap_push(order_list_t *heap, order_t order);

/*
 * Removed the head of the min heap
 */
void min_heap_pop(order_list_t *heap);

/*
 * Transforms the list into a min heap
 */
void min_heap_make(order_list_t *list);

#endif // MIN_HEAP


