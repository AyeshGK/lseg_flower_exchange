#include "../../include/Book.h"
#include <iostream>

// constructor


void Book::addOrder(const OrderPtr& order) {
    if (order->getSide() == 1) {
        buyers.push(std::move(*order));
    } else {
        sellers.push(std::move(*order));
    }
}

std::vector<OrderPtr> Book::sellersMatch(const OrderPtr& orderPtr) {
        std::cout<<"sellersMatch\n";
        std::vector<OrderPtr> execution;
    
        int quantity = orderPtr->getQuantity();
        double price = orderPtr->getPrice();
    
        while(!buyers.empty()&& quantity >0){
            std::cout<<"buyers not empty\n";
            OrderPtr buyer = std::make_shared<Order>(buyers.top());
            std::cout<<"buyer price: "<<buyer->getPrice()<<"\n";
            int orderQuantity = quantity;
            if(buyer->getPrice() >= price){
                
                //execute order 
                int buyerQuantity = buyer->getQuantity();
                if(buyerQuantity <= quantity){
                    //execute buyer order 
                    quantity -= buyerQuantity;
                    buyer->setStatus(2);
                    execution.push_back(buyer);
                    buyers.pop();
    
                    //partial transaction for seller
                    std::cout<<"partial transaction for seller\n";
                    OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
                    orderCopyPtr->resetQuantity(orderQuantity - buyerQuantity);
                    orderCopyPtr->setPrice(buyer->getPrice()); // set to the buyer price
                    orderCopyPtr->setStatus(3);
                    execution.push_back(orderCopyPtr);
                }else{
                    //execute seller order 
                    buyer->resetQuantity(buyerQuantity - quantity);
                    buyers.pop();
                    buyers.push(*buyer); // pushing copy of buyer order
                    
                    //update the transaction
                    buyer->resetQuantity(quantity);
                    buyer->setStatus(3);
                    execution.push_back(buyer);
                    
                    quantity = 0;
    
                    //complete transaction for seller
                    std::cout<<"complete transaction for seller\n";
                    orderPtr->setStatus(2);
                    orderPtr->setPrice(buyer->getPrice()); // set to the buyer price
                    execution.push_back(orderPtr);
                }
    
            }else{
                break;
            }
        }
    
        if(quantity >0){
            std::cout<<"partial transaction for seller finally\n";
            //partial transaction for seller
            orderPtr->resetQuantity(quantity);
            sellers.push(std::move(*orderPtr)); // pushing without copy
        }
    
        return execution;
    
}


std::vector<OrderPtr> Book::buyersMatch(const OrderPtr& orderPtr) {
    std::cout<<"buyersMatch\n";
    std::vector<OrderPtr> execution;

    int quantity = orderPtr->getQuantity();
    double price = orderPtr->getPrice();

    while(!sellers.empty()&& quantity >0){
        std::cout<<"sellers not empty\n";
        OrderPtr seller = std::make_shared<Order>(sellers.top());
        std::cout<<"seller price: "<<seller->getPrice()<<"\n";
        int orderQuantity = quantity;
        if(seller->getPrice() <= price){
            //execute order 
            std::cout<<"avaialble order\n";
            int sellerQuantity = seller->getQuantity();
            if(sellerQuantity <= quantity){
                //execute seller order 
                quantity -= sellerQuantity;
                seller->setStatus(2);
                execution.push_back(seller);
                sellers.pop();

                //partial transaction for buyer
                std::cout<<"partial transaction for buyer\n";
                OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
                orderCopyPtr->resetQuantity(orderQuantity - sellerQuantity);
                orderCopyPtr->setPrice(seller->getPrice()); // set to the seller price
                orderCopyPtr->setStatus(3);
                execution.push_back(orderCopyPtr);
            }else{
                //execute buyer order 
                seller->resetQuantity(sellerQuantity - quantity);
                sellers.pop();
                sellers.push(*seller); // pushing copy of seller order
                
                //update the transaction
                seller->resetQuantity(quantity);
                seller->setStatus(3);
                execution.push_back(seller);
                
                quantity = 0;

                //complete transaction for buyer
                std::cout<<"complete transaction for buyer\n";
                orderPtr->setStatus(2);
                orderPtr->setPrice(seller->getPrice()); // set to the seller price
                execution.push_back(orderPtr);
            }

        }else{
            break;
        }
    }

    if(quantity >0){
        //partial transaction for buyer
        orderPtr->resetQuantity(quantity);
        buyers.push(std::move(*orderPtr)); // pushing without copy
    }

    return execution;
}


std::vector<OrderPtr> Book::match(const OrderPtr& orderPtr) {
    std::cout << "Matching orders...\n";
    // ...

    // get OrderPtr vector 
    std::vector<OrderPtr> execution;

    int side = orderPtr->getSide();
    if(side == 1){
        //buy side 
        if(sellers.empty()){
            //no sellers 
            std::cout<<"no sellers\n";
            OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
            buyers.push(std::move(*orderPtr)); // pushing without copy
            execution.push_back(orderCopyPtr);
        }else{
             execution = buyersMatch(orderPtr);
        }
       
    }else{
        //sell side 
        if(buyers.empty()){
            //no buyers 
            std::cout<<"no buyers\n";
            OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
            sellers.push(std::move(*orderPtr)); // pushing without copy
            execution.push_back(orderCopyPtr);
        }else{
            execution = sellersMatch(orderPtr);
        }
    }

    return execution;

}

// Path: src/model/Order.cpp