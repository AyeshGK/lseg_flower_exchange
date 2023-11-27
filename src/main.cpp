#include "../include/Exchanger.h"

int main() {
    // Create an Exchanger instance with CSV file path
    Exchanger exchanger("/Users/ayesh/workspace/c++ workshop/flower_exchange/data/orders/orders.csv");

    // Perform the order exchange
    exchanger.performExchange();

    return 0;
}
