#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include "order.h"
#include "max_heap.h"
#include "min_heap.h"

int64_t current_id = 0;

order_list_t buy_orders;
order_list_t sell_orders;
order_list_t completed;

int64_t min64(int64_t a, int64_t b) {
    return (a < b) ? a : b;
}

void execute_order(order_t *waiting, order_t *ordering) {
    int64_t size = min64(waiting->parameters.size, ordering->parameters.size);
    int64_t executed_price = size * waiting->parameters.price;

    waiting->executed += size;
    waiting->executed_price += executed_price;
    ordering->executed += size;
    ordering->executed_price += executed_price;
}

void enqueue_order(order_parameters_t parameters) {
    order_t order;
    order.id = current_id++;
    order.parameters = parameters;
    order.executed = 0;
    order.executed_price = 0;

    fprintf(stdout, "ENQUEUING ");
    order_print(stdout, &order);
    fprintf(stdout, "\n");

    order_t *other;

    while (order.executed < order.parameters.size) {
        switch(order.parameters.type) {
            case order_type_buy:
                if (sell_orders.size == 0) {
                    min_heap_push(&buy_orders, order);
                    break;
                }
                other = min_heap_head(&sell_orders);
                if (order.parameters.price >= other->parameters.price) {
                    execute_order(other, &order);
                    if (other->executed == other->parameters.size) {
                        order_list_push(&completed, *other);
                        min_heap_pop(&sell_orders);
                    }
                    if (order.executed == order.parameters.size) {
                        order_list_push(&completed, order);
                        break;
                    }
                    continue;
                } else {
                    max_heap_push(&buy_orders, order);
                    break;
                }
                break;

            case order_type_sell:
                if (buy_orders.size == 0) {
                    min_heap_push(&sell_orders, order);
                    break;
                }
                other = max_heap_head(&buy_orders);
                if (order.parameters.price <= other->parameters.price) {
                    execute_order(other, &order);
                    if (other->executed == other->parameters.size) {
                        order_list_push(&completed, *other);
                        max_heap_pop(&buy_orders);
                    }
                    if (order.executed == order.parameters.size) {
                        order_list_push(&completed, order);
                        break;
                    }
                    continue;
                } else {
                    min_heap_push(&sell_orders, order);
                    break;
                }
                break;

        }
        break;
    }
}

void print_state(FILE *file) {
    fprintf(file, "== BUY ORDERS ==\n");
    for (size_t i = 0; i < buy_orders.size; i++) {
        order_print(file, &buy_orders.orders[i]);
        fprintf(file, "\n");
    }
    fprintf(file, "== SELL ORDERS ==\n");
    for (size_t i = 0; i < sell_orders.size; i++) {
        order_print(file, &sell_orders.orders[i]);
        fprintf(file, "\n");
    }
    fprintf(file, "== COMPLETED ORDERS ==\n");
    for (size_t i = 0; i < completed.size; i++) {
        order_print(file, &completed.orders[i]);
        fprintf(file, "\n");
    }
}

int main(int argc, char **argv) {
    {
        // Buy 30 shares at $100
        order_parameters_t parameters = order_parameters_new(order_type_buy, 10000, 30);
        enqueue_order(parameters);
    }

    {
        // Sell 15 shares at $150
        order_parameters_t parameters = order_parameters_new(order_type_sell, 15000, 15);
        enqueue_order(parameters);
    }

    {
        // Sell 15 shares at $200
        order_parameters_t parameters = order_parameters_new(order_type_sell, 20000, 15);
        enqueue_order(parameters);
    }

    {
        // Buy 30 shares at $160
        order_parameters_t parameters = order_parameters_new(order_type_buy, 16000, 30);
        enqueue_order(parameters);
    }

    print_state(stdout);

    return 0;
}
