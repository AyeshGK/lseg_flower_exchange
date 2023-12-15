#ifndef ORDER_BUFFER_H
#define ORDER_BUFFER_H

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "../dao/Order.h"

class OrderBuffer {
public:
    void addOrder(const OrderPtr& order);
    OrderPtr getOrder();
    int getSize();

private:
    std::queue<OrderPtr> buffer_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

#endif  // ORDER_BUFFER_H
