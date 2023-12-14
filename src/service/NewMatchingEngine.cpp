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
        OrderPtr availableOrderPtr = side == Side::BUY ? sellers.top() : buyers.top();
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
        
        (side == Side::BUY) ? buyers.push(std::move(orderPtr)) : sellers.push(std::move(orderPtr));


        //set orderPtr to nullptr 
        const_cast<OrderPtr&>(orderPtr).reset();

        orderCopyPtr->setTransactionTime(std::chrono::system_clock::now());
        writerBuffer.addOrder(orderCopyPtr);
    }else if(quantity >0){ // complet the remaining transactions
        //partial transaction for buyer
        orderPtr->resetQuantity(quantity);
        
        (side == Side::BUY) ? buyers.push(std::move(orderPtr)) : sellers.push(std::move(orderPtr));
    }
}


bool NewMatchingEngine:: isPossibleOrder(int side, int quantity){
    if (side == Side::BUY){
      return quantity > 0 && !sellers.empty();
    }else if(side == Side::SELL){
        return quantity > 0 && !buyers.empty();
    }

    std::cout<<"Invalid side"<<std::endl; // "Invalid side
    return false;
}


bool NewMatchingEngine:: isPossiblePrice(int side,const OrderPtr& orderPtr,const OrderPtr& availableOrderPtr){
    if (side == Side::BUY)
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
    orderPtr->setStatus(Status::FILL);
    orderPtr->setPrice(availableOrderPtr->getPrice());
    orderPtr->setTransactionTime(std::chrono::system_clock::now());
    writerBuffer.addOrder(orderPtr);

    quantity = 0;
    // complete the transaction for the availableOrderPtr 
    availableOrderPtr->setStatus(Status::FILL);
    availableOrderPtr->setTransactionTime(std::chrono::system_clock::now());
    writerBuffer.addOrder(availableOrderPtr);

    (orderPtr->getSide() == Side::BUY) ? sellers.pop() : buyers.pop();
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
        orderCopyPtr->setStatus(Status::PFILL);
        orderCopyPtr->setTransactionTime(std::chrono::system_clock::now());
        writerBuffer.addOrder(orderCopyPtr);

        // complete the transaction for the availableOrderPtr
        quantity -=  availableOrderPtr->getQuantity();
        availableOrderPtr->setStatus(Status::FILL);
        availableOrderPtr->setTransactionTime(std::chrono::system_clock::now());
        writerBuffer.addOrder(availableOrderPtr);

        (orderPtr->getSide() == Side::BUY) ? sellers.pop() : buyers.pop();
}


void NewMatchingEngine:: greaterQuantityMatch(   
    const OrderPtr& orderPtr,
    const OrderPtr& availableOrderPtr,
    int& quantity,
    OrderBuffer& writerBuffer){
        // completed transaction for the orderPtr push that into the execution report
        orderPtr->setStatus(Status::FILL);
        orderPtr->setPrice(availableOrderPtr->getPrice()); // set to the availableOrderPtr price
        orderPtr->setTransactionTime(std::chrono::system_clock::now());
        writerBuffer.addOrder(orderPtr);

        // partial transaction for availableOrderPtr push that remaining to the priority queue
        availableOrderPtr->resetQuantity(availableOrderPtr->getQuantity() - quantity);

        (orderPtr->getSide() == Side::BUY) ? 
        (sellers.pop(), sellers.push(availableOrderPtr)) : (buyers.pop(), buyers.push(availableOrderPtr));

        // update the trasaction for the availableOrderPtr push that into the execution report
        availableOrderPtr->resetQuantity(quantity);
        availableOrderPtr->setStatus(Status::PFILL);
        availableOrderPtr->setTransactionTime(std::chrono::system_clock::now());
        writerBuffer.addOrder(availableOrderPtr);

        quantity = 0;
}


// path: src/service/Book.cpp