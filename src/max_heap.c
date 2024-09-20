#include "max_heap.h"

#define heap_cmp(x, y) ((x) > (y))

// ######################
// # Local declarations #
// ######################
void max_heap_swap_orders(order_t *first, order_t *second);

void max_heap_push_up(order_list_t *heap, size_t index);

void max_heap_heapify(order_list_t *heap, size_t index);

// ##################
// # Implementation #
// ##################
order_t *max_heap_head(order_list_t *heap) {
    return &heap->orders[0];
}

void max_heap_push(order_list_t *heap, order_t order) {
    size_t index = order_list_push(heap, order);
    max_heap_push_up(heap, index);
}

void max_heap_pop(order_list_t *heap) {
    heap->orders[0] = heap->orders[heap->size-1];
    heap->size--;
    max_heap_heapify(heap, 0);
}

void max_heap_make(order_list_t *heap) {
    for (size_t i = 0; i < heap->size; i++) {
        max_heap_push_up(heap, i);
    }
}

// #############
// # Utilities #
// #############
void max_heap_swap_orders(order_t *first, order_t *second) {
    order_t temp = *first;
    *first = *second;
    *second = temp;
}

void max_heap_push_up(order_list_t *heap, size_t index) {
    while (index > 0) {
        size_t parent = heap_parent(index);
        if (heap_cmp(heap_value(heap->orders[index]), heap_value(heap->orders[parent]))) {
            max_heap_swap_orders(&heap->orders[index], &heap->orders[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void max_heap_heapify(order_list_t *heap, size_t index) {
    while (index < heap->size/2) {
        if (heap_child_2(index) >= heap->size) {
            if (heap_cmp(heap_value(heap->orders[index]), heap_value(heap->orders[heap_child_1(index)]))) {
                break;
            }
            max_heap_swap_orders(&heap->orders[index], &heap->orders[heap_child_1(index)]);
            index = heap_child_1(index);
        } else {
            if (heap_cmp(heap_value(heap->orders[index]), heap_value(heap->orders[heap_child_1(index)])) 
                    && heap_cmp(heap_value(heap->orders[index]), heap_value(heap->orders[heap_child_2(index)]))) {
                return;
            }
            if (heap_cmp(heap_value(heap->orders[heap_child_1(index)]), heap_value(heap->orders[heap_child_2(index)]))) {
                max_heap_swap_orders(&heap->orders[index], &heap->orders[heap_child_1(index)]);
                index = heap_child_1(index);
            } else {
                max_heap_swap_orders(&heap->orders[index], &heap->orders[heap_child_2(index)]);
                index = heap_child_2(index);
            }
        }
    }
}

