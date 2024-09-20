#include "order.h"

#ifndef ORDER_LIST
#define ORDER_LIST

#define MAX_ORDERS 1000

typedef struct {
    order_t orders[MAX_ORDERS];
    size_t size;
} order_list_t;

size_t order_list_push(order_list_t *list, order_t order);

#endif // ORDER_LIST
