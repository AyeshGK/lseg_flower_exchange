#ifndef CSV_READER_H
#define CSV_READER_H

#include <vector>
#include "Order.h"

class CSVReader {
public:
    CSVReader(const std::string& filename);

    std::vector<Order> readCSV();

private:
    Order parseCSVLine(const std::string& line);

    std::string filename;
};

#endif  // CSV_READER_H
