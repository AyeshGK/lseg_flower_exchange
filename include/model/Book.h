#ifndef BOOK_H
#define BOOK_H

#include <vector>
#include <queue>
#include <iostream>

#include "../dao/Order.h"
#include "../common/OrderBuffer.h"
#include "../service/MatchingEngineBase.h"
#include "../common/Comparator.h"


class Book {
public:
    Book(std::shared_ptr<MatchingEngineBase> machineEngineBase);
    void orderBook(const OrderPtr & orderPtr, OrderBuffer & writerBuffer);

private:
    std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator> buyers; // For sell side (ascending)
    std::priority_queue<OrderPtr, std::vector<OrderPtr>,Comparator> sellers; // For buy side (descending)

    // change MachineEngineBase attribute to a pointer
    std::shared_ptr<MatchingEngineBase> machineEngineBase;

};

#endif  // BOOK_H
