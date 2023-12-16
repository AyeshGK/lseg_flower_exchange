#include <thread>


#include "../include/Exchanger.h"
#include "../include/service/CSVWriter.h"
#include "../include/common/OrderBuffer.h"


int main() {
    OrderBuffer readerBuffer;
    OrderBuffer writerBuffer;
    

    // filename
    std::string reader_file = "data/orders/orders6.csv";
    std::string writer_file = "data/results/results.csv";

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

// path : src/main.cpp