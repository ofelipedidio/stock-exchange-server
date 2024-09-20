#include "order.h"

order_t order_new(int64_t id, order_parameters_t parameters) {
    order_t order;
    order.id = id;
    order.parameters = parameters;
    order.executed = 0;
    order.executed_price = 0;
    return order;
}

void order_print(FILE *file, order_t *order) {
    fprintf(file, "(id: %ld, ", order->id);
    order_parameters_print(file, &order->parameters);
    fprintf(file, ", executed: %ld, executed_price: %.2f)", order->executed, ((double) order->executed_price) / 100.0);
}

