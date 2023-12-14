#include <iostream>

#include "../../include/NewMatchingEngine.h"

NewMatchingEngine::NewMatchingEngine(){}

void NewMatchingEngine::match(const OrderPtr& orderPtr,OrderBuffer& writerBuffer){
    // check weather the order is buy or sell 
    int side = orderPtr->getSide();

    int quantity = orderPtr->getQuantity();
    // double price = orderPtr->getPrice();

    while(isPossibleOrder(side,quantity)){
        // get available order from opposite side
        OrderPtr availableOrderPtr = side == 1 ? sellers.top() : buyers.top();
        if (isPossiblePrice(side,orderPtr,availableOrderPtr)){
            // int availableOrderQuantity = availableOrderPtr->getQuantity();
            
            if(availableOrderPtr->getQuantity() == quantity) 
                equalQuantityMatch(orderPtr,availableOrderPtr,quantity,writerBuffer);
            else if(availableOrderPtr->getQuantity() < quantity) 
                lessQuantityMatch(orderPtr,availableOrderPtr,quantity,writerBuffer);
            else 
                greaterQuantityMatch(orderPtr,availableOrderPtr,quantity,writerBuffer);
        }else{
            break;
        }
    }

    // complete if the transaction not happens 
    if(quantity == orderPtr->getQuantity()){
        OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
        if(side == 1) {
            buyers.push(std::move(orderPtr)); // pushing order into buyers
        }else {
            sellers.push(std::move(orderPtr)); // pushing order into sellers
        } // pushing order into sellers
        
        //set orderPtr to nullptr 
        const_cast<OrderPtr&>(orderPtr).reset();

        orderCopyPtr->setTransactionTime(std::chrono::system_clock::now());
        writerBuffer.addOrder(orderCopyPtr);
    }else if(quantity >0){ // complet the remaining transactions
        //partial transaction for buyer
        orderPtr->resetQuantity(quantity);
        if(side == 1) buyers.push(std::move(orderPtr)); // pushing order into buyers
        else sellers.push(std::move(orderPtr)); // pushing order into sellers
    }
}

bool NewMatchingEngine:: isPossibleOrder(int side, int quantity){
    if (side ==1){
      return quantity > 0 && !sellers.empty();
    }else{
        return quantity > 0 && !buyers.empty();
    }
}

bool NewMatchingEngine:: isPossiblePrice(int side,const OrderPtr& orderPtr,const OrderPtr& availableOrderPtr){
    if (side ==1)
        return orderPtr->getPrice() >= availableOrderPtr->getPrice();
    else
        return orderPtr->getPrice() <= availableOrderPtr->getPrice();
}

void NewMatchingEngine:: equalQuantityMatch(
    const OrderPtr& orderPtr,
    const OrderPtr& availableOrderPtr,
    int& quantity,
    OrderBuffer& writerBuffer){
    // complete the transaction for the orderPtr
    orderPtr->setStatus(2);
    orderPtr->setPrice(availableOrderPtr->getPrice());
    orderPtr->setTransactionTime(std::chrono::system_clock::now());
    writerBuffer.addOrder(orderPtr);

    quantity = 0;
    // complete the transaction for the availableOrderPtr 
    availableOrderPtr->setStatus(2);
    availableOrderPtr->setTransactionTime(std::chrono::system_clock::now());
    writerBuffer.addOrder(availableOrderPtr);

    if(orderPtr->getSide() == 1) sellers.pop();
    else buyers.pop();
}

void  NewMatchingEngine:: lessQuantityMatch(   
    const OrderPtr& orderPtr,
    const OrderPtr& availableOrderPtr,
    int& quantity,
    OrderBuffer& writerBuffer){
         // partial transaction for orderPtr
        OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
        orderCopyPtr->resetQuantity(quantity - availableOrderPtr->getQuantity());
        orderCopyPtr->setPrice(availableOrderPtr->getPrice());
        orderCopyPtr->setStatus(3);
        orderCopyPtr->setTransactionTime(std::chrono::system_clock::now());
        writerBuffer.addOrder(orderCopyPtr);

        // complete the transaction for the availableOrderPtr
        quantity -=  availableOrderPtr->getQuantity();
        availableOrderPtr->setStatus(2);
        availableOrderPtr->setTransactionTime(std::chrono::system_clock::now());
        writerBuffer.addOrder(availableOrderPtr);

        if(orderPtr->getSide() == 1) sellers.pop();
        else buyers.pop();
}


void NewMatchingEngine:: greaterQuantityMatch(   
    const OrderPtr& orderPtr,
    const OrderPtr& availableOrderPtr,
    int& quantity,
    OrderBuffer& writerBuffer){
        // completed transaction for the orderPtr push that into the execution report
        orderPtr->setStatus(2);
        orderPtr->setPrice(availableOrderPtr->getPrice()); // set to the availableOrderPtr price
        orderPtr->setTransactionTime(std::chrono::system_clock::now());
        writerBuffer.addOrder(orderPtr);

        // partial transaction for availableOrderPtr push that remaining to the priority queue
        availableOrderPtr->resetQuantity(availableOrderPtr->getQuantity() - quantity);
        if(orderPtr->getSide() == 1) {
            sellers.pop();
            sellers.push(availableOrderPtr);
        }else {
            buyers.pop();
            buyers.push(availableOrderPtr);
        }

        // update the trasaction for the availableOrderPtr push that into the execution report
        availableOrderPtr->resetQuantity(quantity);
        availableOrderPtr->setStatus(3);
        availableOrderPtr->setTransactionTime(std::chrono::system_clock::now());
        writerBuffer.addOrder(availableOrderPtr);

        quantity = 0;
}


// path: src/service/Book.cpp