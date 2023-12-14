#include <iostream>

#include "../../include/OldMatchingEngine.h"


OldMatchingEngine::OldMatchingEngine(){
    std::cout<<"OldMatchingEngine constructor\n";
}

void OldMatchingEngine::sellersMatch(const OrderPtr& orderPtr,OrderBuffer& writerBuffer) {
        int quantity = orderPtr->getQuantity();
        double price = orderPtr->getPrice();
    
        while(!buyers.empty()&& quantity >0){
            std::cout<<"buyers not empty\n";
        

            // OrderPtr buyer = std::make_shared<Order>(buyers.top());
            OrderPtr buyer = buyers.top();
            std::cout<<"memory address: "<<&buyer<<"\n";
            std::cout<<"buyer price: "<<buyer->getPrice()<<"\n";
            int orderQuantity = quantity;
            if(buyer->getPrice() >= price){
                
                //execute order 
                int buyerQuantity = buyer->getQuantity();

                if(buyerQuantity == quantity){
                    quantity =0 ;
                    //complete transaction for seller
                    std::cout<<"complete transaction for seller\n";
                    buyer->setStatus(2);
                    // execution.push_back(buyer);
                    // buyer->setOrderId(increamentAndGetOrderCount());
                    buyer->setTransactionTime(std::chrono::system_clock::now());
                    writerBuffer.addOrder(buyer);
                    buyers.pop();

                    //complete transaction for buyer
                    std::cout<<"complete transaction for buyer\n";
                    orderPtr->setStatus(2);
                    orderPtr->setPrice(buyer->getPrice()); // set to the buyer price
                    // execution.push_back(orderPtr);
                    orderPtr->setTransactionTime(std::chrono::system_clock::now());
                    writerBuffer.addOrder(orderPtr);
                }else if(buyerQuantity < quantity){
                    //execute buyer order 
                    quantity -= buyerQuantity;
                    buyer->setStatus(2);
                    // execution.push_back(buyer);
                    buyer->setTransactionTime(std::chrono::system_clock::now());
                    writerBuffer.addOrder(buyer);
                    buyers.pop();
    
                    //partial transaction for seller
                    std::cout<<"partial transaction for seller\n";
                    OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
                    orderCopyPtr->resetQuantity(orderQuantity - buyerQuantity);
                    orderCopyPtr->setPrice(buyer->getPrice()); // set to the buyer price
                    orderCopyPtr->setStatus(3);
                    // execution.push_back(orderCopyPtr);
                    orderCopyPtr->setTransactionTime(std::chrono::system_clock::now());
                    writerBuffer.addOrder(orderCopyPtr);
                }else{
                    //execute seller order 
                    buyer->resetQuantity(buyerQuantity - quantity);
                    buyers.pop();
                    buyers.push(buyer); // pushing copy of buyer order
                    
                    //update the transaction
                    buyer->resetQuantity(quantity);
                    buyer->setStatus(3);
                    // execution.push_back(buyer);
                    buyer->setTransactionTime(std::chrono::system_clock::now());
                    writerBuffer.addOrder(buyer);
                    
                    quantity = 0;
    
                    //complete transaction for seller
                    std::cout<<"complete transaction for seller\n";
                    orderPtr->setStatus(2);
                    orderPtr->setPrice(buyer->getPrice()); // set to the buyer price
                    // execution.push_back(orderPtr);
                    orderPtr->setTransactionTime(std::chrono::system_clock::now());
                    writerBuffer.addOrder(orderPtr);
                }
    
            }else{
                std::cout << "breaking ....."<< std::endl;
                break;
            }
        }

        if(quantity == orderPtr->getQuantity()){
            std::cout << "no change"<< std::endl;
            OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
            sellers.push(std::move(orderPtr)); // pushing original into sellers 
            // execution.push_back(orderCopyPtr); // pushing copy object to execution array
            orderCopyPtr->setTransactionTime(std::chrono::system_clock::now());
            writerBuffer.addOrder(orderCopyPtr);
        }else if(quantity >0){
            std::cout<<"partial transaction for seller finally\n";
            //partial transaction for seller
            std::cout << "quatity :" <<quantity << std::endl;
            orderPtr->resetQuantity(quantity);
            sellers.push(std::move(orderPtr)); // pushing without copy  
        }
    
        // return execution;
    
}

void OldMatchingEngine::buyersMatch(const OrderPtr& orderPtr,OrderBuffer& writerBuffer) {
    int quantity = orderPtr->getQuantity();
    double price = orderPtr->getPrice();

    while(!sellers.empty()&& quantity >0){
        // OrderPtr seller = std::make_shared<Order>(sellers.top());
        OrderPtr seller = sellers.top();
        int orderQuantity = quantity;
        if(seller->getPrice() <= price){
            
            //execute order 
            int sellerQuantity = seller->getQuantity();

            if(sellerQuantity == quantity){
                quantity =0 ;
                //complete transaction for buyer
                seller->setStatus(2);
                // execution.push_back(seller);
                seller->setTransactionTime(std::chrono::system_clock::now());
                writerBuffer.addOrder(seller);
                sellers.pop();

                //complete transaction for seller
                orderPtr->setStatus(2);
                orderPtr->setPrice(seller->getPrice()); // set to the seller price
                // execution.push_back(orderPtr);
                orderPtr->setTransactionTime(std::chrono::system_clock::now());
                writerBuffer.addOrder(orderPtr);
            }else if(sellerQuantity < quantity){
                //execute seller order 
                quantity -= sellerQuantity;
                seller->setStatus(2);
                // execution.push_back(seller);
                seller->setTransactionTime(std::chrono::system_clock::now());
                writerBuffer.addOrder(seller);
                sellers.pop();

                //partial transaction for buyer
                OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
                orderCopyPtr->resetQuantity(orderQuantity - sellerQuantity);
                orderCopyPtr->setPrice(seller->getPrice()); // set to the seller price
                orderCopyPtr->setStatus(3);
                // execution.push_back(orderCopyPtr);
                orderCopyPtr->setTransactionTime(std::chrono::system_clock::now());
                writerBuffer.addOrder(orderCopyPtr);
            }else{
                //execute buyer order 
                seller->resetQuantity(sellerQuantity - quantity);
                sellers.pop();
                sellers.push(seller); // pushing copy of seller order
                
                //update the transaction
                seller->resetQuantity(quantity);
                seller->setStatus(3);
                // execution.push_back(seller);
                seller->setTransactionTime(std::chrono::system_clock::now());
                writerBuffer.addOrder(seller);
                
                quantity = 0;

                //complete transaction for buyer
                orderPtr->setStatus(2);
                orderPtr->setPrice(seller->getPrice()); // set to the seller price
                // execution.push_back(orderPtr);
                orderPtr->setTransactionTime(std::chrono::system_clock::now());
                writerBuffer.addOrder(orderPtr);
            }

        }else{
            break;
        }
    }

    if(quantity == orderPtr->getQuantity()){
        OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
        buyers.push(std::move(orderPtr)); // pushing original into buyers
        orderCopyPtr->setTransactionTime(std::chrono::system_clock::now());
        writerBuffer.addOrder(orderCopyPtr);
    }else if(quantity >0){
        orderPtr->resetQuantity(quantity);
        buyers.push(std::move(orderPtr)); // pushing without copy
    }

    // return execution;
}

void OldMatchingEngine::match(const OrderPtr& orderPtr,OrderBuffer& writerBuffer) {
    int side = orderPtr->getSide();
    if(side == 1){
        //buy side 
        
        if(sellers.empty()){
            OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
            buyers.push(std::move(orderPtr)); // pushing without copy
            orderCopyPtr->setTransactionTime(std::chrono::system_clock::now());
            writerBuffer.addOrder(orderCopyPtr);
        }
        else{
             buyersMatch(orderPtr,writerBuffer);
            }
       
    }else{
        //sell side 
        if(buyers.empty()){
            //no buyers 
            OrderPtr orderCopyPtr = std::make_shared<Order>(*orderPtr);
            sellers.push(std::move(orderPtr)); // pushing without copy
            orderCopyPtr->setTransactionTime(std::chrono::system_clock::now());
            writerBuffer.addOrder(orderCopyPtr);
        }
        else{
            sellersMatch(orderPtr,writerBuffer);
            // writerBuffer.addOrder(orderPtr);
        }
    }
}
