#ifndef EXCHANGER_H
#define EXCHANGER_H

#include <vector>
#include "Order.h"
#include "CSVReader.h"
#include "FlowerBookFactory.h"
#include "OrderBuffer.h"

class Exchanger {
public:
    Exchanger(const std::string& csvFilePath, OrderBuffer& writerBuffer);

    // Perform order exchange or any other operations as needed
    void performExchange();

private:
    std::vector<OrderPtr> orders;
    FlowerBookFactory flowerBookFactory;  

    OrderBuffer& writerBuffer;  
};

#endif  // EXCHANGER_H
