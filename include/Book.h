#ifndef BOOK_H
#define BOOK_H

#include <vector>
#include <queue>
#include "Order.h"

class Book {
public:
    // Add an order to the handler
    void addOrder(const OrderPtr& order);

    // matching 
    // void match(const OrderPtr& order);

    std::vector<OrderPtr> match(const OrderPtr& order) ;

private:
  // Priority queues for buyers and sellers
    std::priority_queue<Order, std::vector<Order>, std::greater<Order>> sellers; // For sell side (ascending)
    std::priority_queue<Order, std::vector<Order>> buyers; // For buy side (descending)

    std::vector<OrderPtr> buyersMatch(const OrderPtr& order);
    std::vector<OrderPtr> sellersMatch(const OrderPtr& order);
};

#endif  // BOOK_H
