#include "order_list.h"

size_t order_list_push(order_list_t *list, order_t order) {
    size_t index = list->size++;
    list->orders[index] = order;
    return index;
}
