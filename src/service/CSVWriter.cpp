#include "../../include/CSVWriter.h"

#include <fstream>
#include <sstream>
#include <iostream>

// CSVWriter::CSVWriter(const std::string& filename) : filename(filename) {}


CSVWriter::CSVWriter(const std::string& csvFilePath, OrderBuffer& writerBuffer)
    : filename(csvFilePath) , writerBuffer(writerBuffer)
    {}

// OrderPtr CSVWriter::parseCSVLine(const std::string& line) {
//     std::istringstream iss(line);
//     std::string orderId, clientOrderId, instrument, traderId, reason;
//     int side, quantity, status;
//     double price;

//     if (std::getline(iss, orderId, ',') &&
//         std::getline(iss, clientOrderId, ',') &&
//         std::getline(iss, instrument, ',') &&
//         iss >> side &&
//         iss.ignore() &&
//         iss >> quantity &&
//         iss.ignore() &&
//         iss >> price &&
//         iss.ignore() &&
//         std::getline(iss, traderId, ',') &&
//         std::getline(iss, reason, ',') &&
//         iss >> status) {
//         // Assuming OrderPtr is a typedef for std::shared_ptr<Order>
//         return std::make_shared<Order>(orderId, clientOrderId, instrument, side, quantity, price, traderId, reason, status);
//     }

//     return nullptr; // Return nullptr if parsing fails
// }

void CSVWriter::writeCSV() {
    std::ofstream file(filename);

    if (!file.is_open()) {
        // Handle error opening file
        // throw std::runtime_error("Error opening file");
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return ;
    }

    // Write header
    file << "Order ID,Client Order,Instrument,Side,Exec Status,Quantity,Price,Reason,Status\n";

    // Write data
    // for (const auto& order : orders) {
    //     file << "abs" << ","
    //          << order->getClientOrderId() << ","
    //          << order->getInstrument() << ","
    //          << (order->getSide() == 1 ? "Buy" : "Sell") << ","
    //          << order->getStatus() << ","
    //          << order->getQuantity() << ","
    //          << order->getPrice() << ","
    //          << order->getReason() << "\n";
    // }

    while (true){

        // OrderPtr order = writerBuffer.getOrder();
        OrderPtr order = writerBuffer.getOrder();

        if(order == nullptr){
            std::cout << "Orders writing completed." << std::endl; 
            break;
        }

        file  << order->getClientOrderId() << ","
            << order->getInstrument() << ","
            << (order->getSide() == 1 ? "Buy" : "Sell") << ","
            << order->getStatus() << ","
            << order->getQuantity() << ","
            << order->getPrice() << ","
            << order->getReason() << "\n";
      
    }

    file.close();


}

// std::vector<OrderPtr> CSVWriter::appendCSV(std::vector<OrderPtr>& orders) {
//     std::ofstream file(filename, std::ios_base::app);

//     if (!file.is_open()) {
//         // Handle error opening file
//         return {};
//     }

//     // Write data
//     for (const auto& order : orders) {
//         file << "abs" << ","
//              << order->getClientOrderId() << ","
//              << order->getInstrument() << ","
//              << (order->getSide() == 1 ? "Buy" : "Sell") << ","
//              << order->getStatus() << ","
//              << order->getQuantity() << ","
//              << order->getPrice() << ","
//              << order->getReason() << "\n";
//     }

//     file.close();

//     // Return the appended orders
//     return orders;
// }

    

