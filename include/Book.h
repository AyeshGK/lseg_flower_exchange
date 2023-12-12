#ifndef BOOK_H
#define BOOK_H

#include <vector>
#include <queue>
#include "Order.h"


// comparator 
class Comparator {
public:
    bool operator() (const OrderPtr& lhs, const OrderPtr& rhs) const {
        if (lhs->getSide() == 1 && rhs->getSide() == 1) {  // Buy side
            return lhs->getPrice() > rhs->getPrice();
        } else if (lhs->getSide() == 2 && rhs->getSide() == 2) {  // Sell side
            return lhs->getPrice() < rhs->getPrice();
        } else {
            // Add logic for handling orders on different sides (optional)
            return false;
        }
    }
};


class Book {
public:
    // Add an order to the handler
    void addOrder(const OrderPtr& order);

    // matching 
    // void match(const OrderPtr& order);

    std::vector<OrderPtr> match(const OrderPtr& order) ;

private:
  // // Priority queues for buyers and sellers
  //   std::priority_queue<Order, std::vector<Order>, std::greater<Order>> buyers; // For sell side (ascending)
  //   std::priority_queue<Order, std::vector<Order>> sellers; // For buy side (descending)


    // Priority queues for buyers and sellers
    std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator> buyers; // For sell side (ascending)
    std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator> sellers; // For buy side (descending)


    std::vector<OrderPtr> buyersMatch(const OrderPtr& orderPtr);
    std::vector<OrderPtr> sellersMatch(const OrderPtr& orderPtr);
};

#endif  // BOOK_H
