#include "../../include/common/OrderBuffer.h"

void OrderBuffer::addOrder(const OrderPtr& order) {
    std::unique_lock<std::mutex> lock(mutex_);
    buffer_.push(order);
    lock.unlock();
    cv_.notify_one();
}

OrderPtr OrderBuffer::getOrder() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return !buffer_.empty(); });
    OrderPtr order = buffer_.front();
    buffer_.pop();
    return order;
}


int OrderBuffer::getSize(){
    // std::unique_lock<std::mutex> lock(mutex_);
    return buffer_.size();
}