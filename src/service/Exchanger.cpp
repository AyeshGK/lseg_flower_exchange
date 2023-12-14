#include <iostream>

#include "../../include/Exchanger.h"


Exchanger::Exchanger(OrderBuffer& readerBuffer,OrderBuffer& writerBuffer)
 : readerBuffer(readerBuffer),writerBuffer(writerBuffer) 
{
}

void Exchanger::performExchange() {
    while(true){
        OrderPtr order = readerBuffer.getOrder();
        if (order==nullptr){
            std::cout << "Exchanger Completed.\n";
            writerBuffer.addOrder(order);// null order added to buffer
            break;
        } 

        // rejected object
        if(order->getStatus() == 1){
            writerBuffer.addOrder(order);
            continue;
        }

        // Get or create a flower book for the instrument type
        std::shared_ptr<Book> flowerBook = flowerBookFactory.getFlowerBook(order->getInstrument());
        // flowerBook->match(order,writerBuffer);
        flowerBook->orderBook(order,writerBuffer);

    }
    std::cout << "orders completed";
}
