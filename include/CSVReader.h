#ifndef CSV_READER_H
#define CSV_READER_H

#include <vector>
#include "Order.h"
#include <memory>
#include "OrderBuffer.h"


class CSVReader {
public:
    CSVReader(const std::string& filename, OrderBuffer& readerBuffer);

    void readCSV();

private:
    OrderPtr parseCSVLine(const std::string& line);

    std::string filename;
    OrderBuffer& readerBuffer;
};

#endif  // CSV_READER_H
