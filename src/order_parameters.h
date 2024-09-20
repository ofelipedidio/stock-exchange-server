#include <inttypes.h>
#include <stdio.h>

#include "order_type.h"

#ifndef ORDER_PARAMETERS
#define ORDER_PARAMETERS

typedef struct {
    order_type_t type;
    int64_t price;
    int64_t size;
} order_parameters_t;

order_parameters_t order_parameters_new(order_type_t type, int64_t price, int64_t size);

void order_parameters_print(FILE *file, order_parameters_t *parameters);

#endif // ORDER_PARAMETERS

