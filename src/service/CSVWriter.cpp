#include "../../include/CSVWriter.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>



CSVWriter::CSVWriter(const std::string& csvFilePath, OrderBuffer& writerBuffer)
    : filename(csvFilePath) , writerBuffer(writerBuffer)
    {}


void CSVWriter:: add_row(std::ofstream& file,OrderPtr order)
{
    file  << "ord" << order->getOrderId() << ","
            << order->getClientOrderId() << ","
            << order->getInstrument() << ","
            << getSide(order->getSide()) << ","
            << getStatus(order->getStatus()) << ","
            << order->getQuantity() << ","
            << order->getPrice() << ","
            << transactionTime(order->getTransactionTime()) << ","
            << order->getReason() << "\n";
}


void CSVWriter::writeCSV() {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return ;
    }

    // Write header
    file << "Order ID,Client Order,Instrument,Side,Exec Status,Quantity,Price,Transaction Time,Reason\n";


    while (true){

        OrderPtr order = writerBuffer.getOrder();

        if(order == nullptr){
            std::cout << "Orders writing completed." << std::endl; 
            break;
        }
        add_row(file,order);
    }

    file.close();
}

std::string CSVWriter:: getSide(int side){
    if(side == Side::BUY){
        return "1 - Buy";
    }else if(side == Side::SELL){
        return "2 - Sell";
    }else{
        return "Invalid Side";
    }
}

std::string CSVWriter:: getStatus(int status){
    if(status == Status::NEW){
        return "New";
    }else if(status == Status::REJECTED){
        return "Rejected";
    }else if(status == Status::FILL){
        return "Fill";
    }else if(status == Status::PFILL){
        return "Pfill";
    }else{
        return "Invalid Status";
    }
}

std::string CSVWriter::transactionTime(std::chrono::system_clock::time_point timePoint)const {

    std::time_t currentTime = std::chrono::system_clock::to_time_t(timePoint);

    // Get the milliseconds part
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
        timePoint.time_since_epoch() % std::chrono::seconds(1)
    );

    // Convert the time to a struct tm in UTC
    struct tm* timeInfo = std::gmtime(&currentTime);

    // Format the time as YYYYMMDD-HHMMSS.sss using strftime
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d-%H%M%S", timeInfo);
    // std::cout << buffer << "." << std::setfill('0') << std::setw(3) << milliseconds.count() << std::endl;

    return std::string(buffer) + "." + std::to_string(milliseconds.count());
}