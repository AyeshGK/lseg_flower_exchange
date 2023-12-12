#include <thread>
#include <iostream>


#include "../include/Exchanger.h"
#include "../include/CSVWriter.h"
#include "../include/OrderBuffer.h"



int main() {

    OrderBuffer writerBuffer;

    // filename
    std::string reader_file = "/Users/ayesh/workspace/c++ workshop/flower_exchange/data/orders/orders3.csv";
    std::string writer_file = "/Users/ayesh/workspace/c++ workshop/flower_exchange/data/results/results.csv";

    // Create an Exchanger instance with CSV file path
    Exchanger exchanger(reader_file, writerBuffer);
    CSVWriter writer(writer_file,writerBuffer);

    //  in the writer thread call writer.writeCSV(std::ref(writerBuffer))
    // Create and start the writer thread
    std::thread writerThread(&CSVWriter::writeCSV, &writer);

    exchanger.performExchange();

    writerThread.join();

    return 0;
}
