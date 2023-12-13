#include <thread>
#include <iostream>


#include "../include/Exchanger.h"
#include "../include/CSVWriter.h"
#include "../include/OrderBuffer.h"



int main() {
    OrderBuffer readerBuffer;
    OrderBuffer writerBuffer;
    

    // filename
    std::string reader_file = "/Users/ayesh/workspace/c++ workshop/flower_exchange/data/orders/orders6.csv";
    std::string writer_file = "/Users/ayesh/workspace/c++ workshop/flower_exchange/data/results/results.csv";

    // Create an Exchanger instance with CSV file path
    Exchanger exchanger(readerBuffer, writerBuffer);
    CSVReader reader(reader_file, readerBuffer);
    CSVWriter writer(writer_file,writerBuffer);

    std::thread readerThread(&CSVReader::readCSV, &reader);
    std::thread writerThread(&CSVWriter::writeCSV, &writer);
   
    exchanger.performExchange(); // perfoming on main thread

   

    readerThread.join();
    writerThread.join();

    return 0;
}
