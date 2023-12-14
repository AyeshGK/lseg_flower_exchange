#include "../../include/CSVWriter.h"

#include <fstream>
#include <sstream>
#include <iostream>



CSVWriter::CSVWriter(const std::string& csvFilePath, OrderBuffer& writerBuffer)
    : filename(csvFilePath) , writerBuffer(writerBuffer)
    {}


void CSVWriter:: add_row(std::ofstream& file,OrderPtr order)
{
    file  << "ord" << order->getOrderId() << ","
    << order->getClientOrderId() << ","
            << order->getInstrument() << ","
            << (order->getSide() == 1 ? "Buy" : "Sell") << ","
            << order->getStatus() << ","
            << order->getQuantity() << ","
            << order->getPrice() << ","
            << order->getReason() << "\n";
}


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


    while (true){

        OrderPtr order = writerBuffer.getOrder();

        if(order == nullptr){
            std::cout << "Orders writing completed." << std::endl; 
            break;
        }

        // file  << order->getClientOrderId() << ","
        //     << order->getInstrument() << ","
        //     << (order->getSide() == 1 ? "Buy" : "Sell") << ","
        //     << order->getStatus() << ","
        //     << order->getQuantity() << ","
        //     << order->getPrice() << ","
        //     << order->getReason() << "\n";

        add_row(file,order);
      
    }

    file.close();


}

