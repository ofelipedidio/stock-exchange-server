#include <stdio.h>
#include <inttypes.h>

#include "order_parameters.h"

#ifndef ORDER
#define ORDER

typedef struct {
    int64_t id;
    order_parameters_t parameters;
    int64_t executed;
    int64_t executed_price;
} order_t;

order_t order_new(int64_t id, order_parameters_t parameters);

void order_print(FILE *file, order_t *order);

#endif // ORDER
