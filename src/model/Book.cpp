#include "../../include/Book.h"
#include <iostream>

// constructor


void Book::addOrder(const OrderPtr& order) {
    if (order->getSide() == 1) {
        buyers.push_back(order);
    } else {
        sellers.push_back(order);
    }
}

void Book::match() {
    std::cout << "Matching orders...\n";
    // ...
}

// Path: src/model/Order.cpp