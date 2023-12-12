#ifndef BOOK_H
#define BOOK_H

#include <vector>
#include <queue>
#include "Order.h"
#include "OrderBuffer.h"
#include <iostream>


// comparator 
class Comparator {
public:
    bool operator() (const OrderPtr& lhs, const OrderPtr& rhs) const {
        std::cout<<"comparator\n";
        std::cout<<"lhs price: "<<lhs->getPrice()<<"\n";
        if (lhs->getSide() == 1 && rhs->getSide() == 1) {  // Buy side
            return lhs->getPrice() < rhs->getPrice();
        } else if (lhs->getSide() == 2 && rhs->getSide() == 2) {  // Sell side
            return lhs->getPrice() > rhs->getPrice();
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

    void match(const OrderPtr& order,OrderBuffer& writerBuffer) ;

private:
  // // Priority queues for buyers and sellers
  //   std::priority_queue<Order, std::vector<Order>, std::greater<Order>> buyers; // For sell side (ascending)
  //   std::priority_queue<Order, std::vector<Order>> sellers; // For buy side (descending)


    // Priority queues for buyers and sellers
    std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator> buyers; // For sell side (ascending)
    std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator> sellers; // For buy side (descending)


    void buyersMatch(const OrderPtr& orderPtr,OrderBuffer& writerBuffer);
    void sellersMatch(const OrderPtr& orderPtr,OrderBuffer& writerBuffer);
};

#endif  // BOOK_H
