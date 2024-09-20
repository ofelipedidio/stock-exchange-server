#include "order_parameters.h"

order_parameters_t order_parameters_new(order_type_t type, int64_t price, int64_t size) {
    order_parameters_t parameters;
    parameters.type = type;
    parameters.price = price;
    parameters.size = size;
    return parameters;
}

void order_parameters_print(FILE *file, order_parameters_t *parameters) {
    fprintf(file, "(");
    switch (parameters->type) {
        case order_type_buy:
            fprintf(file, "buy");
            break;
        case order_type_sell:
            fprintf(file, "sell");
            break;
    }
    fprintf(file, ", price: %.2f, size: %ld)", ((double) parameters->price) / 100.0, parameters->size);
}


