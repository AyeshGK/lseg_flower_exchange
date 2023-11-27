#ifndef BOOK_H
#define BOOK_H

#include <vector>
#include "Order.h"

class Book {
public:
    // Add an order to the handler
    void addOrder(const OrderPtr& order);

    // matching 
    void match();

private:
    std::vector<OrderPtr> buyers;
    std::vector<OrderPtr> sellers;
};

#endif  // BOOK_H
