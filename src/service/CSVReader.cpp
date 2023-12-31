#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../../include/service/CSVReader.h"

CSVReader::CSVReader(const std::string& filename, OrderBuffer& readerBuffer) 
: filename(filename) , readerBuffer(readerBuffer)
{}

void CSVReader::readCSV() {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        readerBuffer.addOrder(nullptr);
        return ;
    }

    // skip the first line (header)
    std::string header;
    std::getline(file, header);


    std::string line;
    while (std::getline(file, line)) {
        OrderPtr orderPtr = parseCSVLine(line);
        // orders.push_back(orderPtr);
        readerBuffer.addOrder(orderPtr);
    }

    // push final order to buffer
    // orders.push_back(nullptr);
    readerBuffer.addOrder(nullptr);
    
    file.close();
    // return orders;
}

OrderPtr CSVReader::parseCSVLine(const std::string& line) {
    std::stringstream ss(line);
    std::string clientOrderId, instrument,  quantityStr, priceStr,sideStr;


    // Assuming the CSV format: Client Order ID,Instrument,Side,Quantity,Price,Trader ID
    std::getline(ss, clientOrderId, ',');
    std::getline(ss, instrument, ',');
    std::getline(ss, sideStr, ',');
    std::getline(ss, quantityStr, ',');
    std::getline(ss, priceStr, ',');
    // std::getline(ss, traderId, ',');

    return std::make_shared<Order>(clientOrderId, instrument, sideStr, quantityStr, priceStr);

    // return std::make_shared<Order>(clientOrderId, instrument, side, quantity, price, traderId);
}
