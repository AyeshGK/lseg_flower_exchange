#ifndef EXCHANGER_H
#define EXCHANGER_H

#include <vector>


#include "dao/Order.h"
#include "service/CSVReader.h"
#include "factory/FlowerBookFactory.h"
#include "common/OrderBuffer.h"

class Exchanger {
public:
    Exchanger(OrderBuffer& readerBuffer, OrderBuffer& writerBuffer);

    // Perform order exchange or any other operations as needed
    void performExchange();

private:
    // std::vector<OrderPtr> orders;
    FlowerBookFactory flowerBookFactory;  
    OrderBuffer& readerBuffer;
    OrderBuffer& writerBuffer;  
};

#endif  // EXCHANGER_H
