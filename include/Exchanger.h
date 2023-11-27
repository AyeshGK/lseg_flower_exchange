#ifndef EXCHANGER_H
#define EXCHANGER_H

#include <vector>
#include "Order.h"
#include "CSVReader.h"
#include "FlowerBookFactory.h"

class Exchanger {
public:
    Exchanger(const std::string& csvFilePath);

    // Perform order exchange or any other operations as needed
    void performExchange();

private:
    std::vector<OrderPtr> orders;
    FlowerBookFactory flowerBookFactory;
};

#endif  // EXCHANGER_H
